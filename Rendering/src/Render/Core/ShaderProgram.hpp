#pragma once

#include <glad\glad.h>
#include <string>
#include <glm/glm.hpp>

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
	ShaderProgram(const std::string& debugIdentifier = "SHADERPROGRAM");
	~ShaderProgram();

	void Create(const std::string& vertexSource, const std::string& fragmentSource);

	int GetAttribLocation(const std::string& attribName);
	int GetUniformLocation(const std::string& uniformName);

	void SetUniformMatrix4(const std::string& uniformName, const glm::mat4& mat, bool transpose = false);
	void SetUniformVector3(const std::string& uniformName, const glm::vec3& mat);
	void SetUniformVector4(const std::string& uniformName, const glm::vec4& mat);

	void Use() const;
	void Unuse() const;
};