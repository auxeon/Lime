#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_common.h"


#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>


using namespace std;

struct Vector3 {
	float x;
	float y;
	float z;
};

typedef struct
{
	float* buffer;
	float volume_linear;
	int   length_samples;
	int   channels;
} mydsp_data_t;


struct Implementation {
	Implementation();
	~Implementation();

	void Update();

	FMOD::Studio::System* mpStudioSystem;
	FMOD::System* mpSystem;

	FMOD::DSP* mpDSP;
	FMOD::ChannelGroup* mpMasterChannelGroup;

	int mnNextChannelId;

	typedef map<string, FMOD::Sound*> SoundMap;
	typedef map<int, FMOD::Channel*> ChannelMap;
	typedef map<string, FMOD::Studio::EventInstance*> EventMap;
	typedef map<string, FMOD::Studio::Bank*> BankMap;
	BankMap mBanks;
	EventMap mEvents;
	SoundMap mSounds;
	ChannelMap mChannels;
};

class AudioManager {
public:
	static bool Init();
	static void Update();
	static void Shutdown();
	static int ErrorCheck(FMOD_RESULT result);

	void LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	void LoadEvent(const std::string& strEventName);
	void LoadSound(const string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
	void UnLoadSound(const string& strSoundName);
	void Set3dListenerAndOrientation(const Vector3& vPosition, const Vector3& vLook, const Vector3& vUp);
	int PlaySounds(const string& strSoundName, const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
	void PlayEvent(const string& strEventName);
	void StopChannel(int nChannelId);
	void StopEvent(const string& strEventName, bool bImmediate = false);
	void GetEventParameter(const string& strEventName, const string& strEventParameter, float* parameter);
	void SetEventParameter(const string& strEventName, const string& strParameterName, float fValue);
	void StopAllChannels();
	void SetChannel3dPosition(int nChannelId, const Vector3& vPosition);
	void SetChannelVolume(int nChannelId, float fVolumedB);
	bool IsPlaying(int nChannelId) const;
	bool IsEventPlaying(const string& strEventName) const;
	float dbToVolume(float dB);
	float VolumeTodB(float volume);
	FMOD_VECTOR VectorToFmod(const Vector3& vPosition);
	FMOD_DSP_PARAMETER_FFT* GetSpectrumData();


	/*FMOD_RESULT F_CALLBACK myDSPCallback(FMOD_DSP_STATE* dsp_state, float* inbuffer, float* outbuffer, unsigned int length, int inchannels, int* outchannels);
	FMOD_RESULT F_CALLBACK myDSPCreateCallback(FMOD_DSP_STATE* dsp_state);
	FMOD_RESULT F_CALLBACK myDSPReleaseCallback(FMOD_DSP_STATE* dsp_state);
	FMOD_RESULT F_CALLBACK myDSPGetParameterDataCallback(FMOD_DSP_STATE* dsp_state, int index, void** data, unsigned int* length, char*);
	FMOD_RESULT F_CALLBACK myDSPSetParameterFloatCallback(FMOD_DSP_STATE* dsp_state, int index, float value);
	FMOD_RESULT F_CALLBACK myDSPGetParameterFloatCallback(FMOD_DSP_STATE* dsp_state, int index, float* value, char* valstr);*/

};

Implementation::Implementation() : mnNextChannelId(0) {
	mpStudioSystem = NULL;
	AudioManager::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
	AudioManager::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

	mpSystem = NULL;
	AudioManager::ErrorCheck(mpStudioSystem->getCoreSystem(&mpSystem));

	mpMasterChannelGroup = NULL;
	AudioManager::ErrorCheck(mpSystem->getMasterChannelGroup(&mpMasterChannelGroup));

	AudioManager::ErrorCheck(mpSystem->createDSPByType(FMOD_DSP_TYPE_FFT, &mpDSP));
	AudioManager::ErrorCheck(mpMasterChannelGroup->addDSP(0, mpDSP));



}

Implementation::~Implementation() {

	AudioManager::ErrorCheck(mpMasterChannelGroup->removeDSP(mpDSP));
	AudioManager::ErrorCheck(mpDSP->release());

	AudioManager::ErrorCheck(mpStudioSystem->unloadAll());
	AudioManager::ErrorCheck(mpStudioSystem->release());
}

void Implementation::Update() {
	vector<ChannelMap::iterator> pStoppedChannels;
	for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
	{
		bool bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		if (!bIsPlaying)
		{
			pStoppedChannels.push_back(it);
		}
	}
	for (auto& it : pStoppedChannels)
	{
		mChannels.erase(it);
	}
	AudioManager::ErrorCheck(mpStudioSystem->update());
}

Implementation* sgpImplementation = nullptr;

bool AudioManager::Init() {
	sgpImplementation = new Implementation();
	if (sgpImplementation) {
		return true;
	}
	return false;
}

void AudioManager::Update() {
	sgpImplementation->Update();
}

void AudioManager::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt != sgpImplementation->mSounds.end())
		return;
	FMOD_MODE eMode = FMOD_DEFAULT;
	eMode |= b3d ? FMOD_3D : FMOD_2D;
	eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
	FMOD::Sound* pSound = nullptr;
	AudioManager::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
	if (pSound) {
		sgpImplementation->mSounds[strSoundName] = pSound;
	}
}

void AudioManager::UnLoadSound(const std::string& strSoundName)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
		return;
	AudioManager::ErrorCheck(tFoundIt->second->release());
	sgpImplementation->mSounds.erase(tFoundIt);
}

int AudioManager::PlaySounds(const string& strSoundName, const Vector3& vPosition, float fVolumedB)
{
	int nChannelId = sgpImplementation->mnNextChannelId++;
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
	{
		LoadSound(strSoundName);
		tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
		{
			return nChannelId;
		}
	}
	FMOD::Channel* pChannel = nullptr;
	AudioManager::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
	if (pChannel)
	{
		FMOD_MODE currMode;
		tFoundIt->second->getMode(&currMode);
		if (currMode & FMOD_3D) {
			FMOD_VECTOR position = VectorToFmod(vPosition);
			AudioManager::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
		}
		AudioManager::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
		AudioManager::ErrorCheck(pChannel->setPaused(false));
		sgpImplementation->mChannels[nChannelId] = pChannel;
	}
	return nChannelId;
}

void AudioManager::SetChannel3dPosition(int nChannelId, const Vector3& vPosition)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	FMOD_VECTOR position = VectorToFmod(vPosition);
	AudioManager::ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
}

void AudioManager::SetChannelVolume(int nChannelId, float fVolumedB)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	AudioManager::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
}

void AudioManager::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags) {
	auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
	if (tFoundIt != sgpImplementation->mBanks.end())
		return;
	FMOD::Studio::Bank* pBank;
	AudioManager::ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
	if (pBank) {
		sgpImplementation->mBanks[strBankName] = pBank;
	}
}

void AudioManager::LoadEvent(const std::string& strEventName) {
	auto tFoundit = sgpImplementation->mEvents.find(strEventName);
	if (tFoundit != sgpImplementation->mEvents.end())
		return;
	FMOD::Studio::EventDescription* pEventDescription = NULL;
	AudioManager::ErrorCheck(sgpImplementation->mpStudioSystem->getEvent(strEventName.c_str(), &pEventDescription));
	if (pEventDescription) {
		FMOD::Studio::EventInstance* pEventInstance = NULL;
		AudioManager::ErrorCheck(pEventDescription->createInstance(&pEventInstance));
		if (pEventInstance) {
			sgpImplementation->mEvents[strEventName] = pEventInstance;
		}
	}
}

void AudioManager::PlayEvent(const string& strEventName) {
	auto tFoundit = sgpImplementation->mEvents.find(strEventName);
	if (tFoundit == sgpImplementation->mEvents.end()) {
		LoadEvent(strEventName);
		tFoundit = sgpImplementation->mEvents.find(strEventName);
		if (tFoundit == sgpImplementation->mEvents.end())
			return;
	}
	tFoundit->second->start();
}

void AudioManager::StopEvent(const string& strEventName, bool bImmediate) {
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;
	FMOD_STUDIO_STOP_MODE eMode;
	eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
	AudioManager::ErrorCheck(tFoundIt->second->stop(eMode));
}

bool AudioManager::IsEventPlaying(const string& strEventName) const {
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return false;

	FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
	if (tFoundIt->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
		return true;
	}
	return false;
}

void AudioManager::GetEventParameter(const string& strEventName, const string& strParameterName, float* parameter) {
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;
	// FMOD 1.10
	//FMOD::Studio::ParameterInstance* pParameter = NULL;
	//AudioManager::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
	//AudioManager::ErrorCheck(pParameter->getValue(parameter));
	// FMOD 2.1 
	AudioManager::ErrorCheck(tFoundIt->second->getParameterByName(strParameterName.c_str(), NULL, parameter));
}

void AudioManager::SetEventParameter(const string& strEventName, const string& strParameterName, float fValue) {
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;

	// FMOD 1.10
	//FMOD::Studio::ParameterInstance* pParameter = NULL;
	//AudioManager::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
	//AudioManager::ErrorCheck(pParameter->setValue(fValue));
	// FMOD 2.1 
	AudioManager::ErrorCheck(tFoundIt->second->setParameterByName(strParameterName.c_str(), fValue));
}

FMOD_VECTOR AudioManager::VectorToFmod(const Vector3& vPosition) {
	FMOD_VECTOR fVec;
	fVec.x = vPosition.x;
	fVec.y = vPosition.y;
	fVec.z = vPosition.z;
	return fVec;
}

int AudioManager::ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		cout << "FMOD ERROR " << result << endl;
		return 1;
	}
	// cout << "FMOD all good" << endl;
	return 0;
}

float  AudioManager::dbToVolume(float dB)
{
	return powf(10.0f, 0.05f * dB);
}

float  AudioManager::VolumeTodB(float volume)
{
	return 20.0f * log10f(volume);
}

void AudioManager::Shutdown() {
	delete sgpImplementation;
}

bool AudioManager::IsPlaying(int nChannelId) const {
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return false;

	bool isPlaying = false;
	AudioManager::ErrorCheck(tFoundIt->second->isPlaying(&isPlaying));
	return isPlaying;
}


void AudioManager::StopChannel(int nChannelId) {
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	AudioManager::ErrorCheck(tFoundIt->second->stop());
}

void AudioManager::StopAllChannels() {
	for (auto it = sgpImplementation->mChannels.begin(); it != sgpImplementation->mChannels.end(); ++it) {
		AudioManager::ErrorCheck(it->second->stop());
	}
}

void AudioManager::Set3dListenerAndOrientation(const Vector3& vPosition, const Vector3& vLook, const Vector3& vUp) {
	const FMOD_VECTOR pos = VectorToFmod(vPosition);
	const FMOD_VECTOR look = VectorToFmod(vLook);
	const FMOD_VECTOR up = VectorToFmod(vUp);
	AudioManager::ErrorCheck(sgpImplementation->mpSystem->set3DListenerAttributes(0, &pos, NULL, &look, &up));
}


FMOD_DSP_PARAMETER_FFT* AudioManager::GetSpectrumData() {
	FMOD_DSP_PARAMETER_FFT* fft;
	auto mdsp = sgpImplementation->mpDSP;
	mdsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&fft, 0, 0, 0);
	return fft;
}








#endif