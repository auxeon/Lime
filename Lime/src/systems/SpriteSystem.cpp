#include "Pch.hpp"
#include "SpriteSystem.hpp"
#include "core/Lime.hpp"
#include "systems/CameraSystem.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/CameraComponent.hpp"
#include "glm/gtx/transform.hpp"



using cp = ControllerComponent;
using tf = TransformComponent;
using cm = CameraComponent;
extern Lime gLimeEngine;

std::shared_ptr<CameraSystem> camSystem;


void SpriteSystem::init(){

    mShader.init("./Lime/shaders/sprite_texture.vert", "./Lime/shaders/sprite_texture.frag");
    gLimeEngine.mGraphicsManager->gfx.initRenderData(mShader, vertices, sizeof(vertices), mVAO, false);

    for (auto const& entity : mEntities) {
        auto& spriteComponent = gLimeEngine.getComponent<SpriteComponent>(entity);
        gLimeEngine.mGraphicsManager->gfx.initTextureData(spriteComponent.texid, spriteComponent.sprite);
    }
    mShader.use();
    mShader.setInt("texture1", 0);

    camSystem = gLimeEngine.mSystemManager->getSystem<CameraSystem>();

    // do the event callback registration
    gLimeEngine.addEventListener(EventID::E_GRAPHICS_DEBUG_TOGGLE, [this](Event& e) {this->onEvent(e); });
    gLimeEngine.addEventListener(EventID::E_GRAPHICS_CAMERA_UPDATED, [this](Event& e) {this->onEvent(e); });
}

void SpriteSystem::update(){
    for (auto& entity : mEntities) {

        auto& spriteComponent = gLimeEngine.getComponent<SpriteComponent>(entity);
        auto& transformComponent = gLimeEngine.getComponent<TransformComponent>(entity);
        
        for (auto& camEntity : camSystem->mEntities) {

            auto& cam = gLimeEngine.getComponent<CameraComponent>(camEntity);
            auto& camTx = gLimeEngine.getComponent<TransformComponent>(camEntity);

            if (cam.activated) {
                mShader.use();
                mShader.setMat4("projection", cam.projmat);
                mShader.setMat4("view",cam.viewmat);

                gLimeEngine.mGraphicsManager->gfx.mShader = mShader;
                gLimeEngine.mGraphicsManager->gfx.drawRenderData(mVAO, transformComponent.model, transformComponent.size, 6, false, spriteComponent.texid, GL_TRIANGLES);
                if (mDebugDraw) {
                    gLimeEngine.mGraphicsManager->gfx.drawRenderData(mVAO, transformComponent.model, transformComponent.size, 6, true, spriteComponent.texid, GL_TRIANGLES);
                }
            }
        }
    }
}

void SpriteSystem::onEvent(Event& e){
    if (e.getType() == EventID::E_GRAPHICS_DEBUG_TOGGLE) {
        mDebugDraw = !mDebugDraw;
    }
}