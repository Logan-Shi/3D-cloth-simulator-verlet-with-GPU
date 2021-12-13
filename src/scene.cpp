#include "scene.h"
#include <iostream>

Scene* Scene::pscene = nullptr;

Scene* Scene::getInstance(int argc, char** argv)
{
	if (pscene == nullptr)
		pscene = new Scene(argc,argv);

	return pscene;
}

Scene::Scene(int argc, char** argv)
{
}

Scene::~Scene()
{
	delete simulation;
}

void Scene::add_cloth(Mesh& object)
{
	cloth = &object;
}

void Scene::add_body(Mesh& object)
{
	body = &object;
}

void Scene::render()
{
	if (pscene->simulation)
	{
		pscene->simulation->simulate(pscene->cloth);
	}
}

void Scene::init_simulation()
{
	if (cloth && body)
	{
		simulation = new Simulator(*cloth, *body);
	}
	else
	{
		std::cout << "check your cloth and body, make sure both ***not*** null!" << std::endl;
	}
}