#ifndef GAME_POLYGONAL_MESH_H_
#define GAME_POLYGONAL_MESH_H_

#include "lib.h"
#include "amesh.h"
#include "res.h"
#include "utils.h"

using namespace res;

namespace gobj
{
	namespace mesh
	{

		class PolygonalMesh: public AMesh {
		private:
			vector<Vertex> verts = {};
			vector<unsigned int> indices = {};
			mat4 model = mat4(1);

			unsigned int texture = 0;
			map<string, unsigned int> textures_ = {};

			unsigned int VAO, VBO, EBO;

			unsigned int load_texture(char const* path, int vertical_flip);

		public:

			PolygonalMesh();
			~PolygonalMesh();

			void set_indices(vector<unsigned int> indices);
			void add_texture(string name, char const* path, bool vflip);
			void set_texture(string name);

			void add_vertex(Vertex v) override;
			void add_index(unsigned int i) override;
			void bind() override;
			void render(Shader* sh) override;
			void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) override;
		};

	} // !mesh

} // !gobj

#endif // !GAME_POLYGONAL_MESH_H_
