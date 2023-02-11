#ifndef GAME_MESH_MODEL_H_
#define GAME_MESH_MODEL_H_

#include "mesh.h"
#include "shader.h"

namespace gobj {

	namespace mesh {

		class Model: public IMesh {
		private:
			string name_ = "";
			vector<Mesh> meshes_ = {};
			vector<Texture> textures_loaded = {};
			string file_directory_ = "";

			bool gammaCorrection;

			void load_model(string path);
			void process_node(aiNode* node, const aiScene* scene);
			Mesh process_mesh(aiMesh* mesh, const aiScene* scene);

			vector<Texture> load_material(
				aiMaterial* mat, aiTextureType type, TexType typeName);

			unsigned int load_texture(const char* path, const string& dir, bool gamma);

		public:
			Model();
			Model(string const& path);
			~Model();

			vec3 get_pos() override;
			void set_speed(float speed) override;
			void set_ref_sys(vec3 front, vec3 up) override;
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
			void move(Directions dir, float speed) override;
			void turn(EulerAngle dir) override;
			void turn(EulerAngle dir, float angle) override;
			void render(Shader* sh) override;

		};

	} // !mesh

} // !gobj

#endif // !GAME_MESH_MODEL_H_
