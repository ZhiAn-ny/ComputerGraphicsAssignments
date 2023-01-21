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
uniform vec3 camPos;

// tmp
float specularStrength = 0.5;


///  UTILITY FUNCTIONS  ////////////////////////////////////////////////////////

vec4 applyPhongLighting(vec4 startColor)
{
    // Calculate the ambient light contribution
    vec3 a = ambient.color * ambient.pwr;

    // Calculate the diffuse light contribution
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(diffuse.pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 d = diff * diffuse.color * diffuse.pwr;

    // Calculate reflection from specular light
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    //32 is the shininess
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 s = specularStrength * spec * diffuse.color;

    vec4 result = vec4( startColor.r * (a.r + d.r + s.r), 
                        startColor.g * (a.g + d.g + s.g),
                        startColor.b * (a.b + d.b + s.b), 
                        startColor.a );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
    vec4 resColor = applyPhongLighting(ourColor);
    
    FragColor = texture(ourTexture, TexCoord) * resColor;
} 
