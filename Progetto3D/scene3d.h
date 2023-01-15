#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "polygonal_mesh.h"
#include "shader.h"

namespace gobj
{
	class Scene {
	private:
		vector<mesh::PolygonalMesh> objs_ = {};

	public:
		Scene();
		~Scene();

		void add_object(mesh::PolygonalMesh mesh);
		void render(Shader* shader);

	};

} // !gobj

#endif // !GAME_SCENE_H_
