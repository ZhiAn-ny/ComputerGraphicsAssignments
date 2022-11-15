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

	public:
		Scene();
		~Scene();

		unsigned int get_id();

		void set_shaders(char * vertsh, char * fragsh);

		/** 
		 * @return The new object's index.
		 */
		int add_object(gso::SceneObject* fig);

		void add_object_at(gso::SceneObject* fig, int index);

		void remove_first();

		gso::SceneObject* get_object(std::string name);

		std::vector<gso::SceneObject*> get_starts_with(std::string name);

		void draw_scene(unsigned int* MatMod, unsigned int* MatProj, glm::mat4* Projection);

	};

}

#endif // !GAME_SCENE_H_
