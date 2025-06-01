#pragma once

#include <glad\glad.h>
#include <glm/glm.hpp>
#include <string>

namespace Render
{
    class ShaderProgram
    {
    private:
        std::string m_debugIdentifier;
        unsigned int m_programId;

    private:
        unsigned int LoadFromSource(const GLenum shaderType, const std::string& source) const;
        bool CheckShaderCompileStatus(const unsigned int shaderId) const;
        bool CheckShaderProgramLinkStatus(const unsigned int shaderProgramId) const;

    public:
        explicit ShaderProgram(const std::string& debugIdentifier = "SHADERPROGRAM");
        ~ShaderProgram();

        void Create(const std::string& vertexSource, const std::string& fragmentSource);

        int GetAttribLocation(const std::string& attribName) const;
        int GetUniformLocation(const std::string& uniformName) const;

        void SetUniformMatrix4(const std::string& uniformName, const glm::mat4& mat, bool transpose = false) const;
        void SetUniformVector3(const std::string& uniformName, const glm::vec3& vec) const;
        void SetUniformVector4(const std::string& uniformName, const glm::vec4& vec) const;

        void Use() const;
        void Unuse() const;
    };
}