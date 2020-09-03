#ifndef __SCENE_3_H__
#define __SCENE_3_H__

#include "../Engine/IScene.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/VertexBuffer.h"
#include "../Engine/Texture.h"

class Scene_3 : public Engine::IScene
{
public:
	virtual void update(float deltaTime) override final;

	virtual void onEnter() override final;
	virtual void onExit() override final;
private:
	Engine::ShaderProgram m_shader;
	Engine::VertexBuffer m_vao;

	Engine::Texture m_texture1;
	Engine::Texture m_texture2;
};

#endif // !__SCENE_3_H__
