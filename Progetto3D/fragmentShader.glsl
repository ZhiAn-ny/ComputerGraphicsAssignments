#version 330 core

in vec4 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

// Lighting
uniform vec3 ambientLight;
uniform float ambientLight_pwr;

uniform sampler2D ourTexture;

void main()
{
    vec3 ambient = ambientLight * ambientLight_pwr;
    vec4 resultingColor = vec4( ourColor.r * ambient.r,
                                ourColor.g * ambient.g,
                                ourColor.b * ambient.b,
                                ourColor.a
                               );
    
    FragColor = texture(ourTexture, TexCoord) * resultingColor;
} 
