#include "ShaderProgram.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Engine
{

ShaderProgram::ShaderProgram() : 
    m_program(0)
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::loadShaders(const char *vertexShaderFilePath, const char *fragmentShaderFilePath)
{
    m_program = glCreateProgram();

    GLuint vertexShader = createShader(vertexShaderFilePath, GL_VERTEX_SHADER);
    GLuint fragmentShader = createShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);

    linkProgram(vertexShader, fragmentShader);

    detachAndCleanShaders(vertexShader, fragmentShader);
}

void ShaderProgram::free()
{
    if(m_program)
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

void ShaderProgram::use()
{
    glUseProgram(m_program);
}

void ShaderProgram::unuse()
{
    glUseProgram(0);
}

void ShaderProgram::set(const char *var, bool value)
{
    glUniform1i(getLocation(var), value ? 1 : 0);
}

void ShaderProgram::set(const char *var, int value)
{
    glUniform1i(getLocation(var), value);
}

void ShaderProgram::set(const char *var, float value)
{
    glUniform1f(getLocation(var), value);
}

void ShaderProgram::set(const char *var, glm::vec2 &value)
{
    glUniform2fv(getLocation(var), 1, &value[0]);
}

void ShaderProgram::set(const char *var, glm::vec3 &value)
{
    glUniform3fv(getLocation(var), 1, &value[0]);
}

void ShaderProgram::set(const char *var, glm::vec4 &value)
{
    glUniform4fv(getLocation(var), 1, &value[0]);
}

void ShaderProgram::set(const char *var, glm::mat4 &value)
{
    glUniformMatrix4fv(getLocation(var), 1, GL_FALSE, &value[0][0]);
}

GLuint ShaderProgram::createShader(const char *filePath, GLenum type)
{
	std::ifstream file(filePath);
	if(file.fail())
	{
		std::cout << "Failed to open file at: " << filePath << std::endl;
		return 0;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string fileContent = buffer.str();
	GLchar *sourceCode = (GLchar *)fileContent.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &sourceCode, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE)
	{
		GLint size;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
		std::vector<GLchar> log(size);
		glGetShaderInfoLog(shader, size, &size, log.data());
		glDeleteShader(shader);

		std::cout << "Failed to compile shader: " << filePath << std::endl;
		std::cout << (char *)log.data() << std::endl;

		return 0;
	}

	return shader;
}

void ShaderProgram::linkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);

    glLinkProgram(m_program);

    GLint success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(success == GL_FALSE)
    {
        GLint size;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &size);
        std::vector<GLchar> log(size);
        glGetProgramInfoLog(m_program, size, &size, log.data());

        std::cout << "Failed to link program" << std::endl;
        std::cout << (char *)log.data() << std::endl;
    }
}

void ShaderProgram::detachAndCleanShaders(GLuint vertexShader, GLuint fragmentShader)
{
    glDetachShader(m_program, vertexShader);
    glDetachShader(m_program, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLint ShaderProgram::getLocation(const char *variable)
{
    auto ptr = m_locations.find(variable);
    if(ptr == m_locations.end())
    {
        GLint location = glGetUniformLocation(m_program, variable);
        m_locations[variable] = location;
        return location;
    }

    return ptr->second;
}

}
