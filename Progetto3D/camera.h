#ifndef GAME_VIEW_CAMERA_H_
#define GAME_VIEW_CAMERA_H_

#include "lib.h"
#include "utils.h"

using namespace util;

namespace gview
{
	namespace gcam
	{

		const float near_plane = 0.1f;
		const float far_plane = 100.0f;

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

			// Field Of View
			float fov_ = 45.0f;

		public:
			Camera();
			~Camera();

			mat4 get_view();
			// Return the field of view of the camera
			float get_fov();
			vec3 get_position();
			vec3 get_front_direction();

			void move(dir::Directions dir);
			void activate_trackball(int x, int y);
			void deactivate_trackball();
			void rotate(int x, int y);
			void zoom_in();
			void zoom_out();
		};

	} // !cam
} // !gview

#endif // !GAME_VIEW_CAMERA_H_
