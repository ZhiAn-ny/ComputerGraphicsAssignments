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
			vector<tex::Texture> textures_loaded = {};
			string file_directory_ = "";

			bool gammaCorrection;

			void load_model(string path);
			void process_node(aiNode* node, const aiScene* scene);
			Mesh process_mesh(aiMesh* mesh, const aiScene* scene);

			vector<tex::Texture> load_material(
				aiMaterial* mat, aiTextureType type, tex::TexType typeName);

			unsigned int load_texture(const char* path, const string& dir, bool gamma);

		public:
			Model();
			Model(string const& path);
			~Model();

			bool is_colliding(vec3 pos);

			void set_name(string name) override;
			string get_name() override;
			void select() override;
			void deselect() override;
			void bind() override;
			void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) override;
			void render(Shader* sh) override;

		};

	} // !mesh

} // !gobj

#endif // !GAME_MESH_MODEL_H_
