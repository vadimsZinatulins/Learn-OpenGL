#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__

#include <glm/glm.hpp>
#include <unordered_map>
#include <glad/glad.h>
#include <string>

namespace Engine
{

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void loadShaders(const char *vertexShaderFilePath, const char *fragmentShaderFilePath);
	void free();

	void use();
	void unuse();

	void set(const char *var, bool value);
	void set(const char *var, int value);
	void set(const char *var, float value);
	void set(const char *var, glm::vec2 &value);
	void set(const char *var, glm::vec3 &value);
	void set(const char *var, glm::vec4 &value);
	void set(const char *var, glm::mat4 &value);

	static void setRes(int width, int height);
	static glm::mat4 genProjection(float angle);
private:
	GLuint createShader(const char *filePath, GLenum type);
	void linkProgram(GLuint vertexShader, GLuint fragmentShader);
	void detachAndCleanShaders(GLuint vertexShader, GLuint fragmentShader);
	GLint getLocation(const char *variable);

	static int m_width;
	static int m_height;

	GLuint m_program;
	std::unordered_map<std::string, GLint> m_locations;
};

}

#endif // !__SHADER_PROGRAM_H__
