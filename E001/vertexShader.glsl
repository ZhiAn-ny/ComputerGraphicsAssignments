#version 330 core


// the position variable has attribute position 0
layout (location = 0) in vec3 aPos;   

// the color variable has attribute position 1
layout (location = 1) in vec4 aColor; 

// matrix which normalize world coordinates to screen coordinates
uniform mat4 Projection; 

// define object's transformations
uniform mat4 Model;	     

// output a color to the fragment shader
out vec4 ourColor; 

void main()
{
	gl_Position = Projection * Model * vec4(aPos.x,aPos.y,aPos.z,1.0);
	ourColor = aColor;
}
