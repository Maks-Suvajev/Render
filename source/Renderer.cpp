#include "Renderer.h"

namespace gfx
{
    Renderer::Renderer(QOpenGLExtraFunctions* openGLFunctions)
        : m_openGLFunctions(openGLFunctions)
    {
    }

    void Renderer::bindVAO(GLuint VAO)
    {
        m_openGLFunctions->glBindVertexArray(VAO);
    }

    void Renderer::draw(uint32_t numVertices, bool EBO)
    {
        if (EBO)
        { 
            m_openGLFunctions->glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
        }
        else
        {
            m_openGLFunctions->glDrawArrays(GL_TRIANGLES, 0, numVertices);
        }
    }

    void Renderer::applyMaterial(gfx::MaterialProperties* material, Shader* shader)
    {
        //TODO: uniform names shouldnt be hardcoded here.
        shader->updateUniformValue("material.shininess", material->shininess);

        shader->updateUniformValue("material.diffuse", 0);
        m_openGLFunctions->glActiveTexture(GL_TEXTURE0);
        m_openGLFunctions->glBindTexture(GL_TEXTURE_2D, material->lightingTextures.diffuse);

        shader->updateUniformValue("material.specular", 1);
        m_openGLFunctions->glActiveTexture(GL_TEXTURE1);
        m_openGLFunctions->glBindTexture(GL_TEXTURE_2D, material->lightingTextures.specular);
    }

    void Renderer::render(glm::mat4& modelMatrix, GpuHandles* gpuHandle, gfx::MaterialProperties* material, Shader* shader)
    {
        shader->useProgram();
        shader->updateModelMatrixValue(modelMatrix);

        applyMaterial(material, shader);

        bindVAO(gpuHandle->VAO);
        draw(gpuHandle->numVertices, gpuHandle->useEBO);
    }
}