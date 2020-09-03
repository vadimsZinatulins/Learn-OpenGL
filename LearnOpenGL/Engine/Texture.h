#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glad/glad.h>

namespace Engine
{

class Texture
{
public:
	void load(const char *path);
	void free();

	operator GLuint() const;

	void bind(unsigned char index);
private:
	GLuint m_texture;
};

}

#endif // !__TEXTURE_H__
