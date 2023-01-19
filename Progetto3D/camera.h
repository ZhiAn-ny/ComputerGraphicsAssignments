#ifndef GAME_VIEW_CAMERA_H_
#define GAME_VIEW_CAMERA_H_

#include "lib.h"

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

		public:
			Camera();
			~Camera();

			mat4 get_view();
		};

	} // !cam
} // !gview

#endif // !GAME_VIEW_CAMERA_H_
