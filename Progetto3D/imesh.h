#ifndef GAME_OBJECT_MESH_INTERFACE_H_
#define GAME_OBJECT_MESH_INTERFACE_H_7

#include "lib.h"
#include "shader.h"

namespace gobj
{
	namespace mesh
	{
		class IMesh {
		public:
			virtual string get_name() = 0;
			virtual void set_name(string name) = 0;

			virtual void select() = 0;
			virtual void deselect() = 0;

			virtual void bind() = 0;
			
			virtual float ray_intersection(vec3 origin, vec3 direction) = 0;
			virtual void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) = 0;
			virtual void render(Shader* sh) = 0;
		};
	}
}


#endif // !GAME_OBJECT_MESH_INTERFACE_H_