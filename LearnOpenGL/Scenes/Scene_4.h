#ifndef __SCENE_4_H__
#define __SCENE_4_H__

#include "../Engine/IScene.h"
#include "../Engine/ShaderProgram.h"
#include "../Engine/VertexBuffer.h"
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"

#define NUM_QUADS 8

class Scene_4 : public Engine::IScene
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

	Engine::Camera m_camera;

	Engine::Transform m_quads[NUM_QUADS];
};

#endif // !__SCENE_4_H__
