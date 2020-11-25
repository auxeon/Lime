#include "Pch.hpp"
#include "SpriteSystem.hpp"
#include "core/Lime.hpp"
#include "systems/CameraSystem.hpp"
#include "components/SpriteComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/ControllerComponent.hpp"
#include "components/CameraComponent.hpp"

using cp = ControllerComponent;
using tf = TransformComponent;
using cm = CameraComponent;
extern Lime gLimeEngine;
extern std::shared_ptr<CameraSystem> camSystem;

void SpriteSystem::init(){

    // setup shaders 

    mShader.init("./Lime/shaders/texture.vert", "./Lime/shaders/texture.frag");
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // setup texture stuff here 
    for (auto& entity : mEntities) {
        auto& spriteComponent = gLimeEngine.getComponent<SpriteComponent>(entity);
        glGenTextures(1, &spriteComponent.texid);
        glBindTexture(GL_TEXTURE_2D, spriteComponent.texid);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        auto& img = gLimeEngine.getOrLoadResource<Image>(spriteComponent.sprite);
        if (img.imagedata) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.w, img.h, 0, GL_RGB, GL_UNSIGNED_BYTE, img.imagedata);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
    }

    mShader.use();
    mShader.setInt("texture", 0);

    // do the event callback registration
    gLimeEngine.addEventListener(EventID::E_GRAPHICS_DEBUG_TOGGLE, [this](Event& e) {this->onEvent(e); });
    gLimeEngine.addEventListener(EventID::E_GRAPHICS_CAMERA_UPDATED, [this](Event& e) {this->onEvent(e); });
}

void SpriteSystem::update(){

    // get camera transform somehow 
    // fire view matrix changes fire event 

    // shader different for minimap 
    // shader differetnt for gamearea

    //TODO 
    // for all entities draw array and send transform 
    for (auto& entity : mEntities) {
        mShader.use();
        auto& spriteComponent = gLimeEngine.getComponent<SpriteComponent>(entity);
        auto& transformComponent = gLimeEngine.getComponent<TransformComponent>(entity);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, spriteComponent.texid);

        int mode = mDebugDraw ? 1 : 0;
        mShader.setInt("mode", mode);

        for (auto&camEntity : camSystem->mEntities) {
            auto& cam = gLimeEngine.getComponent<CameraComponent>(camEntity);
            //glViewport(cam.x, cam.y, cam.width, cam.height);
            glViewport(0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT);
            mShader.setMat4("transform", transformComponent.matrix);
            mShader.setMat4("projection", cam.projmat);
            mShader.setMat4("view", cam.viewmat);
            glBindVertexArray(mVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}

void SpriteSystem::onEvent(Event& e){
    if (e.getType() == EventID::E_GRAPHICS_DEBUG_TOGGLE) {
        mDebugDraw = !mDebugDraw;
        LM_INFO("DebugDraw Toggle");
    }
    //if (e.getType() == EventID::E_GRAPHICS_CAMERA_UPDATED) {
    //    auto camID = e.getParam<EntityID>(EventID::P_GRAPHICS_CAMERA_UPDATED_ENTITYID);
    //}
}