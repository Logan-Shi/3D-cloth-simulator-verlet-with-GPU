#include "scene.h"

using namespace std;

int main(int argc, char** argv)
{
	Scene* main_scene = Scene::getInstance(argc, argv); //initialize opengl 

	Mesh cloth("../../resources/cloth/dress-victor/dress-victor.obj", SINGLE_LAYER_NOB);
	Mesh body("../../resources/pose/Male.obj");

	main_scene->add_cloth(cloth);
	main_scene->add_body(body);

	main_scene->init_simulation();
	for (int i = 0; i < 10; i++)
	{
		main_scene->render();
	}

	getchar();
	return 0;
}

