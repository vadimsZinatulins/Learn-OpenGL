#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glad/glad.h>

class Texture
{
public:
	void load(const char *path);
	void free();

	operator GLuint() const;
private:
	GLuint m_texture;
};

#endif // !__TEXTURE_H__
