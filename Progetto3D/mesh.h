#ifndef GAME_POLYGONAL_MESH_H_
#define GAME_POLYGONAL_MESH_H_

#include "lib.h"
#include "imesh.h"
#include "res.h"

using namespace res;

namespace gobj
{
	namespace mesh
	{

		class Mesh: public IMesh {
		private:
			string name_ = "";
			vector<Vertex> verts = {};
			vector<unsigned int> indices = {};
			mat4 model = mat4(1);
			bool selected_ = false;
			
			vec3 bb_top_right_ = vec3(0);
			vec3 bb_bottom_left_ = vec3(0);

			unsigned int diffuse_map = 0;
			unsigned int specular_map = 0;
			vector<Texture> textures_ = {};
			res::mat::Material orig_material_ = { vec3(-1), vec3(-1), vec3(-1),0 };
			res::mat::Material material = res::mat::tutorial;
			int shading_ = -3;

			unsigned int VAO, VBO, EBO;

			static unsigned int load_texture(char const* path, int vertical_flip);
			
			void set_bounding_box();
			vec3 bb_top_right();
			vec3 bb_bottom_left();
			vec3 get_anchor();

		public:
			Mesh();
			Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
			~Mesh();

			void add_vertex(Vertex v);
			void set_color(vec4 color);
			void set_indices(vector<unsigned int> indices);

			void add_texture(Texture texture);
			void add_texture(string name, char const* path, bool vflip);
			void set_diffuse_map(string name);
			void set_specular_map(string name);
			void reset_material();
			bool is_colliding(vec4 pos);

			vec3 get_pos() override;
			string get_name() override;
			void set_name(string name) override;
			void set_material(Material mat, bool orig = false) override;
			void set_shading(int type) override;
			void select() override;
			void deselect() override;
			bool is_selected() override;
			void bind() override;
			float ray_intersection(vec3 origin, vec3 direction) override;
			void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) override;
			void move(Directions dir) override;
			void render(Shader* sh) override;
		};

	} // !mesh

} // !gobj

#endif // !GAME_POLYGONAL_MESH_H_
