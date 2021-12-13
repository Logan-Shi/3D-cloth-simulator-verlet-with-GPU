#pragma once

#include <glm/glm.hpp>

#include "Mesh.h"
#include "simulator.h"
#include "./bvh/bvh.h"

// Singleton
class Scene
{
public:
	static Scene* getInstance(int argc, char** argv);
	~Scene(); 
	
	void add_cloth(Mesh& object);   // mesh(cloth) to be simulated
	void add_body(Mesh& object);    // mesh(body) to be collided
	void init_simulation();               // construct simualtion
	void render();

private:
	Scene(int argc, char** argv);  //initial

private:

	static Scene* pscene;       //pscene points to the Scene(singleton)
	enum attributes { position, texture, normal };

	Mesh* cloth;
	Mesh* body;
	Simulator* simulation;

private:

    // OPENGL场景的各种函数
	static void RenderGPU_CUDA();
	static void onRender();

private:
	vector<glm::vec4> output_vertices;
};



