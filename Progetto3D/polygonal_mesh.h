#ifndef GAME_POLYGONAL_MESH_H_
#define GAME_POLYGONAL_MESH_H_

#include "lib.h"
#include "imesh.h"
#include "res.h"
#include "utils.h"

using namespace res;

namespace gobj
{
	namespace mesh
	{

		class PolygonalMesh: public Mesh {
		private:
			vector<Vertex> verts = {};
			vector<unsigned int> indices = {};

			unsigned int texture;

			unsigned int VAO, VBO, EBO;

		public:

			PolygonalMesh();
			~PolygonalMesh();

			void set_indices(vector<unsigned int> indices);
			void load_texture(char const* path, int vertical_flip);

			void add_vertex(Vertex v) override;
			void add_index(unsigned int i) override;
			void bind() override;
			void render() override;
		};

	} // !mesh

} // !gobj

#endif // !GAME_POLYGONAL_MESH_H_
