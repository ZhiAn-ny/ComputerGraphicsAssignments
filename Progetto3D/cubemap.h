#ifndef GAME_CUBEMAP_H_
#define GAME_CUBEMAP_H_

#include "lib.h"
#include "mesh_factory.h"
#include "scene3d.h"
#include "camera.h"

using namespace gview::gcam;

namespace gview
{
	namespace sky
	{
		class Cubemap : public gobj::Scene {
		private:
			map<res::sky::SkyBoxThemes, int> themes_ = {};
			unsigned int texture_ID_ = 0;

			unsigned int load_skybox(vector<string> faces_path);

		public:
			Cubemap();
			~Cubemap();

			void init();
			void set_theme(res::sky::SkyBoxThemes theme);
			void render(Shader* sh, Camera* cam);
		};

	} // !sky

} // !gview

#endif // !GAME_CUBEMAP_H_
