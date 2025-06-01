#include "ShaderProgram.hpp"
#include "../Debug/Logger.hpp"
#include "../Debug/gl_debug.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Render
{
    unsigned int ShaderProgram::LoadFromSource(const GLenum shaderType, const std::string& source) const
    {
        const unsigned int shaderId = glCreateShader(shaderType);
        if (shaderId == 0)
        {
            Debug::Logger::LogError("Unable to create shader {0}, type {1}.", m_debugIdentifier, shaderType);
            Debug::GLCheckErrors();
            return 0;
        }

        const char* charSource = source.c_str();
        GLCHECK(glShaderSource(shaderId, 1, &charSource, NULL));
        GLCHECK(glCompileShader(shaderId));

        if (!CheckShaderCompileStatus(shaderId))
        {
            GLCHECK(glDeleteShader(shaderId));
            return 0;
        }

        return shaderId;
    }

    bool ShaderProgram::CheckShaderCompileStatus(const unsigned int shaderId) const
    {
        GLint status;
        GLCHECK(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status));
        if (status == GL_FALSE)
        {
            GLint length;
            GLCHECK(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));
            auto infoLog = new GLchar[length];
            GLCHECK(glGetShaderInfoLog(shaderId, length, NULL, infoLog));

            Debug::Logger::LogError("Shader compilation of {0} failed.\n{1}", m_debugIdentifier, infoLog);
            DEBUG_BREAK();

            delete[] infoLog;
            return false;
        }
        return true;
    }

    bool ShaderProgram::CheckShaderProgramLinkStatus(const unsigned int shaderProgramId) const
    {
        GLint status;
        GLCHECK(glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &status));
        if (status == GL_FALSE)
        {
            GLint length;
            GLCHECK(glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &length));
            auto infoLog = new GLchar[length];
            GLCHECK(glGetProgramInfoLog(shaderProgramId, length, NULL, infoLog));
            Debug::Logger::LogError("Linking of shader {0} failed.\n{1}", m_debugIdentifier, infoLog);

            DEBUG_BREAK();
            delete[] infoLog;
            return false;
        }
        return true;
    }

    ShaderProgram::ShaderProgram(const std::string& debugIdentifier)
    {
        m_programId = 0;
        this->m_debugIdentifier = debugIdentifier;
    }

    ShaderProgram::~ShaderProgram()
    {
        GLCHECK(glDeleteProgram(this->m_programId));
        m_programId = 0;
    }

    void ShaderProgram::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
        const unsigned int vertexShader = LoadFromSource(GL_VERTEX_SHADER, vertexSource);
        const unsigned int fragmentShader = LoadFromSource(GL_FRAGMENT_SHADER, fragmentSource);
        if (vertexShader == 0 || fragmentShader == 0)
        {
            GLCHECK(glDeleteShader(vertexShader));
            GLCHECK(glDeleteShader(fragmentShader));
            return;
        }

        const unsigned int shaderProgramId = glCreateProgram();
        if (shaderProgramId == 0)
        {
            Debug::Logger::LogError("Unable to create shader program {0}.", m_debugIdentifier);
            Debug::GLCheckErrors();
            return;
        }

        GLCHECK(glAttachShader(shaderProgramId, vertexShader));
        GLCHECK(glAttachShader(shaderProgramId, fragmentShader));
        GLCHECK(glLinkProgram(shaderProgramId));

        GLCHECK(glDeleteShader(vertexShader));
        GLCHECK(glDeleteShader(fragmentShader));

        if (!CheckShaderProgramLinkStatus(shaderProgramId))
        {
            GLCHECK(glDeleteProgram(shaderProgramId));
            return;
        }

        m_programId = shaderProgramId;
    }

    int ShaderProgram::GetAttribLocation(const std::string& attribName) const
    {
        const int location = glGetAttribLocation(m_programId, attribName.c_str());
        if (location < 0)
        {
            Debug::Logger::LogError("Unable to retrieve attribute location for '{0}'.", attribName);
            DEBUG_BREAK();
            return -1;
        }
        return location;
    }

    int ShaderProgram::GetUniformLocation(const std::string& uniformName) const
    {
        const int location = glGetUniformLocation(m_programId, uniformName.c_str());
        if (location < 0)
        {
            Debug::Logger::LogError("Unable to retrieve attribute location for '{0}'.", uniformName);
            DEBUG_BREAK();
            return -1;
        }
        return location;
    }

    void ShaderProgram::SetUniformMatrix4(const std::string& uniformName, const glm::mat4& mat, const bool transpose) const
    {
        const int uniformLocation = GetUniformLocation(uniformName);
        if (uniformLocation < 0)
            return;

        Use();
        GLCHECK(glUniformMatrix4fv(uniformLocation, 1, transpose, glm::value_ptr(mat)));
    }

    void ShaderProgram::SetUniformVector3(const std::string& uniformName, const glm::vec3& vec) const
    {
        const int uniformLocation = GetUniformLocation(uniformName);
        if (uniformLocation < 0)
            return;

        Use();
        GLCHECK(glUniform3fv(uniformLocation, 1, glm::value_ptr(vec)));
    }

    void ShaderProgram::SetUniformVector4(const std::string& uniformName, const glm::vec4& vec) const
    {
        const int uniformLocation = GetUniformLocation(uniformName);
        if (uniformLocation < 0)
            return;

        Use();
        GLCHECK(glUniform4fv(uniformLocation, 1, glm::value_ptr(vec)));
    }

    void ShaderProgram::Use() const
    {
        GLCHECK(glUseProgram(m_programId));
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void ShaderProgram::Unuse() const
    {
        GLCHECK(glUseProgram(0));
    }
}