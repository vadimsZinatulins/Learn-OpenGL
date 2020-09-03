#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__

#include <vector>
#include <glad/glad.h>

namespace Engine
{

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void init();
	void clean();

	void addAttribute(std::vector<float> &data, int size);

	void bind();
	void unbind();
private:
	GLuint m_vbo;

	std::vector<GLuint> m_buffers;
};

}

#endif // !__VERTEX_BUFFER_H__
