#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec4 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 Model, View, Projection;

// phong calcolato pre-fragment shading
// modelli di shading calcolati qui.

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;

    FragPos = vec3(Model * vec4(aPos, 1.0));
    Normal = aNormal;
}