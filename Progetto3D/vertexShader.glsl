#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 TexCoord;

uniform mat4 Model, View, Projection;

// phong calcolato pre-fragment shading
// modelli di shading calcolati qui.

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    ourColor = aColor; //vec4(1.0f, 0.5f, 0.2f, 1.0f)
    TexCoord = aTexCoord;
}