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
			unsigned int manta_number = 0;
			unsigned int whale_number = 0;
			unsigned int fish_number = 0;
			unsigned int jelly_number = 0;

		public:
			MeshFactory();
			~MeshFactory();

			Mesh create_cube();

			Model create_dolphin();
			Model create_manta();
			Model create_whale();
			Model create_fish();
			Model create_jellyfish();
		};

	};
};

#endif // !GAME_OBJECT_MESH_FACTORY_H_
