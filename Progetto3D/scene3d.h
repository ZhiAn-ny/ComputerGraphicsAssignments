#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "mesh.h"
#include "model.h"
#include "shader.h"

namespace gobj
{
	class Scene {
	private:
		vector<mesh::Mesh> meshes_ = {};
		vector<mesh::Model> models_ = {};

		mesh::AMesh* get_object(string name);

	public:
		Scene();
		~Scene();

		void add_object(mesh::Mesh mesh);
		void add_object(mesh::Model model);
		void transform_mesh(string name, vec3 tvec, vec3 svec, vec3 rvec, float angle);
		void transform_model(string name, vec3 tvec, vec3 svec, vec3 rvec, float angle);
		void render(Shader* shader);

	};

} // !gobj

#endif // !GAME_SCENE_H_
