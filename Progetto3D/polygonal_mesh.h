#ifndef GAME_POLYGONAL_MESH_H_
#define GAME_POLYGONAL_MESH_H_

#include "lib.h"
#include "res.h"
#include "utils.h"

using namespace res;

namespace gobj
{
	namespace mesh
	{

		class PolygonalMesh {
		private:
			vector<vec3> vertices_ = {};
			vector<unsigned int> indices_ = {};
			vector<vec2> tex_coords_ = {};

			unsigned int texture;

			unsigned int VAO, VBO_G, VBO_C, VBO_T, EBO;

		public:
			vector<vec4> colors_ = {};
			PolygonalMesh();
			~PolygonalMesh();

			void add_vertex(vec3 pos, vec2 tex);
			void add_index(unsigned int index);
			void set_indices(vector<unsigned int> indices);
			void load_texture(char const* path, int vertical_flip);
			void bind();
			void render();
		};

	} // !mesh

} // !gobj

#endif // !GAME_POLYGONAL_MESH_H_
