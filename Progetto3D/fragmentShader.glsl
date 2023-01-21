#version 330 core

in vec4 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//  DATA STRUCTURES  ///////////////////////////////////////////////////////////

struct PointLight {
    vec3 pos;
    vec3 color;
    float pwr;
};

//  UNIFORM VARIABLES  /////////////////////////////////////////////////////////

uniform PointLight ambient;
uniform PointLight diffuse;

// Texture
uniform sampler2D ourTexture;


///  UTILITY FUNCTIONS  ////////////////////////////////////////////////////////

vec4 applyLighting(vec4 startColor)
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(diffuse.pos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 d = diff * diffuse.color * diffuse.pwr;
    vec3 a = ambient.color * ambient.pwr;

    vec4 result = vec4( startColor.r * (a.r + d.r), 
                        startColor.g * (a.g + d.g),
                        startColor.b * (a.b + d.b), 
                        startColor.a );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
    vec4 resColor = applyLighting(ourColor);
    
    FragColor = texture(ourTexture, TexCoord) * resColor;
} 
