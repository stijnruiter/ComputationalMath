#pragma once

#include <glad\glad.h>
#include <string>
#include <glm/glm.hpp>


const std::string FRAGMENT_SHADER_VCOLOR_AND_TEXTURE = R"(
#version 330 core

in vec2 TexCoord;
in vec3 vertex_color;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(vertex_color, 1.0);
}
)";

const std::string FRAGMENT_SHADER_UNIFORM_COLOR = R"(
#version 330 core

uniform vec4 color;
out vec4 FragColor;

void main()
{
    FragColor = color;
}
)";

const std::string FRAGMENT_SHADER_VARIABLE_COLOR = R"(
#version 330 core

in vec3 faceNormal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform vec4 objectColor;
uniform vec4 lightColor;
out vec4 FragColor;

void main()
{
	// Ambient light
	float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * lightColor;
	
	// Diffuse light
	vec3 norm = normalize(faceNormal);
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * lightColor;
	
	// Specular light
	float specularStrength = 0.5;
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec4 specular = specularStrength * spec * lightColor;  

    FragColor = vec4( ((ambient + diffuse + specular) * objectColor).xyz, 1.0);
}
)";


const std::string VERTEX_SHADER_POS_MVP = R"(
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
}
)";
const std::string VERTEX_SHADER_POS_NORMAL_MVP = R"(
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 faceNormal;
out vec3 FragPos;

uniform mat4 invTransModel;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	faceNormal = mat3(invTransModel) * normal; 
    FragPos = vec3(model * vec4(position, 1.0));
    gl_Position = projection * view * model * vec4(position, 1.0);
}
)";


const std::string VERTEX_SHADER_POS_VC_TEX_MVP = R"(
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertex_color;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vertex_color = color;
    TexCoord = texureCoordinates;
}
)";

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