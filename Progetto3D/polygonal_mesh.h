#ifndef GAME_POLYGONAL_MESH_H_
#define GAME_POLYGONAL_MESH_H_

#include "lib.h"

namespace gobj
{
	namespace mesh
	{

		class PolygonalMesh {
		private:
			vector<vec3> vertices_ = {};
			vector<unsigned int> indices_ = {};

			unsigned int VAO, VBO, EBO;

		public:
			PolygonalMesh();
			~PolygonalMesh();

			void add_vertex(vec3 pos);
			void add_index(unsigned int index);
			void set_indices(vector<unsigned int> indices);
			void bind();
			void render();
		};

	} // !mesh

} // !gobj

#endif // !GAME_POLYGONAL_MESH_H_
