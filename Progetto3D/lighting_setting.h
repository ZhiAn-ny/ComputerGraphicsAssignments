#ifndef GAME_LIGHT_SETTINGS_H_
#define GAME_LIGHT_SETTINGS_H_

#include "lib.h"
#include "res.h"
#include "utils.h"
#include "light.h"
#include "shader.h"


namespace lgh {

	class LightingSettings {
	private:
		Light ambient_light_;

	public:
		LightingSettings();
		~LightingSettings();

		void render(Shader* sh);
	};

} // !lgh

#endif // !GAME_LIGHT_SETTINGS_H_
