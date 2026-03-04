#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Renderer.h"

// system
#include "Camera.h"

// Resource managers
#include "EntityManager.h"
#include "ShaderManager.h"

// Component Types
#include "PhysicsTypes.h"
#include "MaterialTypes.h"

// Lighting manager access
#include "LightingSystem.h"

// Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace gfx
{

class RenderSystem
{
    public:
        RenderSystem() = default;
        void runRender(Camera* camera, Renderer* renderer, EntityManager* entityManager, LightingSystem* lightingSystem, ShaderManager* shaderManager);

    private:
        glm::mat4& updateAndGetModelMatrix(std::vector<gfx::Transform>::iterator& transformIter);

};



}

#endif