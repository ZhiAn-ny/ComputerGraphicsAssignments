#ifndef GAME_LIGHT_SETTINGS_H_
#define GAME_LIGHT_SETTINGS_H_

#include "res.h"
#include "utils.h"
#include "point_light.h"
#include "directional_light.h"
#include "spot_light.h"

namespace lgh {

	class LightingSettings {
	private:
		vector<PointLight> point = {};
		vector<DirectionalLight> direct = {};
		vector<Spotlight> spot = {};

	public:
		LightingSettings();
		~LightingSettings();

		vector<PointLight> get_point_lights();

		void add_point_light(PointLight light);
		void add_spotlight(Spotlight light);
		void add_directional_light(DirectionalLight light);

		void render(Shader* sh);
	};

} // !lgh

#endif // !GAME_LIGHT_SETTINGS_H_
