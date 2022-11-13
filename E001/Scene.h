#ifndef GAME_SCENE_H_
#define GMAE_SCENE_H_

#include "Lib.h"
#include "ShaderMaker.h"
#include "scene_object.h"

namespace gscene {


	class Scene {
	private:
		unsigned int program_id_ = 0;
		std::vector<gso::SceneObject> scene_objs_ = {};
		bool wf_mode_ = false;

		void createVertexArray(gso::SceneObject* fig);
		void bindVerticesGeometry(gso::SceneObject* fig);
		void bindVerticesColor(gso::SceneObject* fig);

	public:
		Scene();
		~Scene();

		unsigned int get_id();

		void set_shaders(char * vertsh, char * fragsh);

		/** 
		 * @return The new object's index.
		 */
		int add_object(gso::SceneObject* fig);

		gso::SceneObject* get_object(std::string name);

		void draw_scene(unsigned int* MatMod, unsigned int* MatProj, glm::mat4* Projection);

	};

}

#endif // !GAME_SCENE_H_
