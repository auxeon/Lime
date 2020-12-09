#include "Pch.hpp"
#include "RenderSystem.hpp"
#include "core/Lime.hpp"
#include "glm/glm.hpp"
#include "systems/CameraSystem.hpp"
#include "components/CameraComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/RenderBoxComponent.hpp"

extern Lime gLimeEngine;
extern std::shared_ptr<CameraSystem> camSystem;

void RenderSystem::init(){
	gLimeEngine.addEventListener(EventID::E_WINDOW_RESIZED, [this](Event& e) {this->onEvent(e); });
	mShader.init("Lime/shaders/renderable.vert", "Lime/shaders/renderable.frag");
	gLimeEngine.mGraphicsManager->gfx.initRenderData(mShader, vertices, sizeof(vertices), mVAO, true);

}

void RenderSystem::update(){
    for (auto& entity : mEntities) {

        auto& renderBoxComponent = gLimeEngine.getComponent<RenderBoxComponent>(entity);
        auto& transformComponent = gLimeEngine.getComponent<TransformComponent>(entity);

        for (auto& camEntity : camSystem->mEntities) {

            auto& cam = gLimeEngine.getComponent<CameraComponent>(camEntity);
            auto& camTx = gLimeEngine.getComponent<TransformComponent>(camEntity);

            if (cam.activated) {
                mShader.use();
                mShader.setMat4("projection", cam.projmat);
                mShader.setMat4("view", cam.viewmat);
                mShader.setVec3("color", renderBoxComponent.color);

                gLimeEngine.mGraphicsManager->gfx.mShader = mShader;
                gLimeEngine.mGraphicsManager->gfx.drawRenderData(mVAO, transformComponent.model, transformComponent.size, 6, true, 0, GL_POLYGON);
            }
        }
    }
}

void RenderSystem::onEvent(Event& e){

}
