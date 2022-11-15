#version 420 core

uniform float time;
uniform vec2 resolution;

// Interpolated values from the vertex shaders
in vec4 ourColor;
out vec4 FragColor;  

void main(){
	// Assign to each fragment the interpolated color
	FragColor = ourColor;

}
