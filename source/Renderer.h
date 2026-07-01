#ifndef RENDERER_H
#define RENDERER_H

// STL
#include <memory>

#include "SceneModelTypes.h"
#include "MaterialTypes.h"
#include "Shader.h"

#include <QOpenGLExtraFunctions>

namespace gfx
{

class Renderer
{

    public:
        Renderer(QOpenGLExtraFunctions* openGLFunctions);

        void render(glm::mat4& modelMatrix, GpuHandles* gpuHandle, gfx::Material* material, Shader* shader);

    private:
        void applyMaterial(gfx::Material* material, Shader* Shader);
        void draw(uint32_t numVertices, bool EBO);
        void bindVAO(GLuint VAO);

        QOpenGLExtraFunctions* m_openGLFunctions;
};


}

#endif