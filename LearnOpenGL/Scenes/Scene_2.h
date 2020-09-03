#ifndef __SCENE_2_H__
#define __SCENE_2_H__

#include "../Engine/IScene.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/VertexBuffer.h"

class Scene_2 : public Engine::IScene
{
public:
	virtual void update(float deltaTime) override final;

	virtual void onEnter() override final;
	virtual void onExit() override final;
private:
	Engine::ShaderProgram m_shader;
	Engine::VertexBuffer m_vao;
};

#endif // !__SCENE_2_H__
