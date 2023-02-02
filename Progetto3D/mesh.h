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

		class Mesh: public AMesh {
		private:
			vector<Vertex> verts = {};
			vector<unsigned int> indices = {};
			mat4 model = mat4(1);
			bool selected_ = false;
			
			vec3 bb_top_right_ = vec3(0);
			vec3 bb_bottom_left_ = vec3(0);

			unsigned int diffuse_map = 0;
			unsigned int specular_map = 0;
			vector<tex::Texture> textures_ = {};
			res::mat::Material material = res::mat::tutorial;

			unsigned int VAO, VBO, EBO;

			static unsigned int load_texture(char const* path, int vertical_flip);
			
			void set_bounding_box();
			vec3 bb_top_right();
			vec3 bb_bottom_left();
			vec3 get_anchor();

			bool is_colliding_vector(vec3 origin, vec3 direction);

		public:

			Mesh();
			Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<tex::Texture> textures);
			~Mesh();

			void set_indices(vector<unsigned int> indices);
			void add_texture(tex::Texture texture);
			void add_texture(string name, char const* path, bool vflip);
			void set_diffuse_map(string name);
			void set_specular_map(string name);
			void set_material(res::mat::Material mat);
			bool is_colliding(vec4 pos);

			void add_vertex(Vertex v) override;
			void add_index(unsigned int i) override;
			void set_color(vec4 color) override;
			void select() override;
			void deselect() override;
			void bind() override;
			void render(Shader* sh) override;
			void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) override;
		};

	} // !mesh

} // !gobj

#endif // !GAME_POLYGONAL_MESH_H_
