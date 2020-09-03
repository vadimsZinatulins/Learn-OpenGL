#include "VertexBuffer.h"

namespace Engine
{

VertexBuffer::VertexBuffer() :
	m_vbo(0)
{
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::init()
{
	glGenVertexArrays(1, &m_vbo);
}

void VertexBuffer::clean()
{
	glDeleteVertexArrays(1, &m_vbo);

	glDeleteBuffers(m_buffers.size(), m_buffers.data());
}

void VertexBuffer::addAttribute(std::vector<float> &data, int size)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(m_buffers.size(), size, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(m_buffers.size());

	m_buffers.push_back(buffer);
}

void VertexBuffer::bind()
{
	glBindVertexArray(m_vbo);
}

void VertexBuffer::unbind()
{
	glBindVertexArray(0);
}

}
