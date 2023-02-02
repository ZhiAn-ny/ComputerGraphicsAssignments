#ifndef GAME_OBJECT_MESH_INTERFACE_H_
#define GAME_OBJECT_MESH_INTERFACE_H_

#include "lib.h"
#include "shader.h"

namespace gobj
{
	namespace mesh
	{
		class Vertex {
		public:
			vec3 pos = vec3(0);
			vec4 color = vec4(1);
			vec2 tex = vec2(0);
			vec3 normal = vec3(0);

			Vertex() {};
			Vertex(vec3 pos_, vec4 col_, vec2 tex_, vec3 normal_)
			{
				this->pos = pos_;
				this->color = col_;
				this->tex = tex_;
				this->normal = normal_;
			}
		};

		class IMesh {
		public:
			virtual string get_name() = 0;
			virtual void set_name(string name) = 0;
			virtual void select() = 0;
			virtual void deselect() = 0;
			virtual float ray_intersection(vec3 origin, vec3 direction) = 0;
			virtual void bind() = 0;
			virtual void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) = 0;
			virtual void render(Shader* sh) = 0;
		};

		class AMesh : public IMesh {
		private:
			string name_ = "";

		public:
			string get_name() { return this->name_; }
			void set_name(string name) { this->name_ = name; }

			virtual void add_vertex(Vertex v) = 0;
			virtual void add_index(unsigned int v) = 0;
			virtual void set_color(vec4 color) = 0;

			virtual void select() override = 0;
			virtual void deselect() override = 0;
			virtual float ray_intersection(vec3 origin, vec3 direction) override = 0;
			virtual void bind() override = 0;
			virtual void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) override = 0;
			virtual void render(Shader* sh) override = 0;
		};

	} // !mesh

	namespace tex {

		enum class TexType {
			diffuse,
			specular,
			undefined
		};

		class Texture {
		public:
			unsigned int id = 0;
			TexType type = TexType::undefined;
			string path = "";  // we store the path of the texture to compare with other textures
			string name = "";

			Texture() {}

			static Texture* find_first(TexType type, vector<Texture>& list)
			{
				for (int i = 0; i < list.size(); i++) 
					if (list[i].type == type) return &list[i];
				return nullptr;
			}
		
		};

	} // !tex

} // !gobj

#endif // !GAME_OBJECT_MESH_INTERFACE_H_
