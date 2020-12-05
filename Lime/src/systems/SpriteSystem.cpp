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

    mShader.init("./Lime/shaders/texture.vert", "./Lime/shaders/texture.frag");


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    for (auto const& entity : mEntities) {
        auto& spriteComponent = gLimeEngine.getComponent<SpriteComponent>(entity);
        glGenTextures(1, &spriteComponent.texid);
        glBindTexture(GL_TEXTURE_2D, spriteComponent.texid);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        auto& img = gLimeEngine.getOrLoadResource<Image>(spriteComponent.sprite);
        if (img.imagedata)
        {
            if (img.ch == 4) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.imagedata);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else if (img.ch == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.w, img.h, 0, GL_RGB, GL_UNSIGNED_BYTE, img.imagedata);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    }
    mShader.use();
    mShader.setInt("texture1", 0);

    camSystem = gLimeEngine.mSystemManager->getSystem<CameraSystem>();

    // do the event callback registration
    gLimeEngine.addEventListener(EventID::E_GRAPHICS_DEBUG_TOGGLE, [this](Event& e) {this->onEvent(e); });
    gLimeEngine.addEventListener(EventID::E_GRAPHICS_CAMERA_UPDATED, [this](Event& e) {this->onEvent(e); });
}

void SpriteSystem::update(){

    //TODO 
    // for all entities draw array and send transform 
    for (auto& entity : mEntities) {


        auto& spriteComponent = gLimeEngine.getComponent<SpriteComponent>(entity);
        auto& transformComponent = gLimeEngine.getComponent<TransformComponent>(entity);

        
        for (auto& camEntity : camSystem->mEntities) {

            auto& cam = gLimeEngine.getComponent<CameraComponent>(camEntity);
            auto& camTx = gLimeEngine.getComponent<TransformComponent>(camEntity);


            if (cam.activated) {
                mShader.use();
                mShader.setMat4("transform", glm::scale(transformComponent.matrix, transformComponent.size));
                //mShader.setMat4("projection", glm::perspective(glm::radians(90.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, -100.0f, 100.0f));
                //glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
                mShader.setMat4("projection", glm::ortho((float)0, (float)SCREEN_WIDTH, (float)0, (float)SCREEN_HEIGHT, -1.0f, 1.0f));
                //mShader.setMat4("projection", cam.projmat);
                //mShader.setMat4("view", glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
                mShader.setMat4("view",cam.viewmat);
                glViewport(cam.x, cam.y, cam.width, cam.height);
                glScissor(cam.x, cam.y, cam.width, cam.height);
                glEnable(GL_SCISSOR_TEST);

                glm::vec4 color = rgba255((unsigned int)cam.clearcolor.r, (unsigned int)cam.clearcolor.g, (unsigned int)cam.clearcolor.b, (unsigned int)cam.clearcolor.a);
                glClearColor(color.x, color.y, color.z, color.w);

                // bind textures on corresponding texture units
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, spriteComponent.texid);

                int mode = 0;
                mShader.setInt("mode", mode);
                // render container
                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                mode = mDebugDraw ? 1 : 0;
                mShader.setInt("mode", mode);


                if (mode) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    // render container
                    glBindVertexArray(VAO);
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                // render container
                //glBindVertexArray(VAO);
                //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            }
        }
    }
}

void SpriteSystem::onEvent(Event& e){
    if (e.getType() == EventID::E_GRAPHICS_DEBUG_TOGGLE) {
        mDebugDraw = !mDebugDraw;
    }
}