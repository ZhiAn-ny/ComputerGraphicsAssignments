#ifndef GAME_OBJECT_MESH_INTERFACE_H_
#define GAME_OBJECT_MESH_INTERFACE_H_

#include "lib.h"
#include "shader.h"

using namespace res::mat;
using namespace util::dir;

namespace gobj
{
	namespace mesh
	{
		class IMesh {
		public:
			virtual vec3 get_pos() = 0;
			virtual void set_speed(float speed) = 0;
			virtual void set_front(vec3 front) = 0;
			virtual string get_name() = 0;
			virtual void set_name(string name) = 0;
			virtual void set_material(Material mat, bool orig = false) = 0;
			virtual void set_shading(int type) = 0;

			virtual void select() = 0;
			virtual void deselect() = 0;
			virtual bool is_selected() = 0;

			virtual void bind() = 0;
			
			virtual float ray_intersection(vec3 origin, vec3 direction) = 0;
			virtual void transform(vec3 tvec, vec3 svec, vec3 rvec, float angle) = 0;
			virtual void move(Directions dir) = 0;
			virtual void turn(Directions dir) = 0;
			virtual void turn(Directions dir, float angle) = 0;
			virtual void render(Shader* sh) = 0;
		};
	}
}


#endif // !GAME_OBJECT_MESH_INTERFACE_H_