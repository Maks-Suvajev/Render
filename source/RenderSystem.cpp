#include "RenderSystem.h"

namespace gfx
{

glm::mat4& RenderSystem::updateAndGetModelMatrix(std::vector<gfx::Transform>::iterator& transformIter)
{
    transformIter->modelMatrix = glm::mat4(1.0f);

    // Translate
    transformIter->modelMatrix = glm::translate(transformIter->modelMatrix, transformIter->position);

    // Rotate in the order X -> Y -> Z every time
    transformIter->modelMatrix = glm::rotate(transformIter->modelMatrix, glm::radians(transformIter->rotation.x), glm::vec3{1.0f, 0.0f, 0.0f}); // x rotation
    transformIter->modelMatrix = glm::rotate(transformIter->modelMatrix, glm::radians(transformIter->rotation.y), glm::vec3{0.0f, 1.0f, 0.0f}); // y rotation
    transformIter->modelMatrix = glm::rotate(transformIter->modelMatrix, glm::radians(transformIter->rotation.z), glm::vec3{0.0f, 0.0f, 1.0f}) ; // z rotation

    // Scale
    transformIter->modelMatrix = glm::scale(transformIter->modelMatrix, transformIter->scaleFactors);

    return transformIter->modelMatrix;
}

void RenderSystem::runRender(Camera* camera, Renderer* renderer, EntityManager* entityManager, LightingSystem* lightingSystem, ShaderManager* shaderManager)
{
    auto transformPool = entityManager->getComponentPool<gfx::Transform>();

    if(transformPool == nullptr)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::RenderSystem::runRender::Transform pool doesn't exist. Nothing to render." << std::endl;
        #endif
        return;
    }

    std::vector<gfx::Transform>::iterator poolBegin = transformPool->begin();
    std::vector<gfx::Transform>::iterator poolEnd = transformPool->end();

    for (auto transformIter = poolBegin; transformIter != poolEnd; ++transformIter)
    {
        size_t index = std::distance(poolBegin, transformIter);
        Entity entity = transformPool->getEntityID(index);

        auto mesh = entityManager->getPoolElement<gfx::GpuHandles>(entity);

        if (mesh == nullptr)
        {
            // Set default mesh
            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "DEBUG::RenderSystem::runRender::mesh is a nullptr" << std::endl;
            #endif
        }

        auto material = entityManager->getPoolElement<gfx::MaterialProperties>(entity);

        if (material == nullptr)
        {
            // Set default material
            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "DEBUG::RenderSystem::runRender::material is a nullptr" << std::endl;
            #endif
        }

        Shader* shader = shaderManager->getShaderPtr(material->shader);

        if (shader == nullptr)
        {
            // Set default shader
            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "DEBUG::RenderSystem::runRender::shader is a nullptr" << std::endl;
            #endif
        }

        shader->useProgram();
        shader->updateViewMatrixValue(camera->calculateViewMatrix());
		shader->updateProjectionMatrixValue(camera->calculateProjectionMatrix());

        lightingSystem->refreshUniforms(shader, entityManager); 

        renderer->render(updateAndGetModelMatrix(transformIter), mesh, material, shader);
    }
}

}
