#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "polygonal_mesh.h"
#include "shader.h"

namespace gobj
{
	class Scene {
	private:
		vector<mesh::PolygonalMesh> objs_ = {};

		mesh::AMesh* get_object(string name);

	public:
		Scene();
		~Scene();

		void add_object(mesh::PolygonalMesh mesh);
		void transform_object(string name, vec3 tvec, vec3 svec, vec3 rvec, float angle);
		void render(Shader* shader);

	};

} // !gobj

#endif // !GAME_SCENE_H_
