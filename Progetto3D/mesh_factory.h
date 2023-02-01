#ifndef GAME_OBJECT_MESH_FACTORY_H_
#define GAME_OBJECT_MESH_FACTORY_H_

#include "mesh.h"
#include "model.h"

namespace gobj
{
	namespace mesh {

		class MeshFactory {
		private:
			unsigned int cube_number = 0;
			unsigned int dolphin_number = 0;

		public:
			MeshFactory();
			~MeshFactory();

			Mesh create_cube();

			Model create_dolphin();
		};

	};
};

#endif // !GAME_OBJECT_MESH_FACTORY_H_
