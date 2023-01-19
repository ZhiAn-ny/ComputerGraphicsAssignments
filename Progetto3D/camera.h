#ifndef GAME_VIEW_CAMERA_H_
#define GAME_VIEW_CAMERA_H_

#include "lib.h"
#include "utils.h"

using namespace util;

namespace gview
{
	namespace gcam
	{

		class Camera {
		private:
			vec3 pos_ = {};
			vec3 target_ = {};
			// Points to the reverse direction of what the camera is targeting
			vec3 dir_ = {};

			vec3 up_ = {};
			vec3 front_ = {};

			// Rotation along the y axis
			float yaw = -90.0f;
			// Rotation along the x axis
			float pitch = 0.0f;

			float sensitivity_ = 0.1f;
			float speed_ = 0.5f;
			vec2 last_mouse_pos = {};
			bool is_active_ = false;

		public:
			Camera();
			~Camera();

			mat4 get_view();
			void move(dir::Directions dir);
			void activate_trackball(int x, int y);
			void deactivate_trackball();
			void rotate(int x, int y);
		};

	} // !cam
} // !gview

#endif // !GAME_VIEW_CAMERA_H_
