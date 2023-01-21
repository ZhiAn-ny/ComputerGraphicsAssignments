#version 330 core

in vec4 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//  DATA STRUCTURES  ///////////////////////////////////////////////////////////

struct Light {
    vec3 pos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  

//  UNIFORM VARIABLES  /////////////////////////////////////////////////////////

uniform Light light;

// Texture
uniform sampler2D ourTexture;
uniform vec3 camPos;

uniform Material material;


///  UTILITY FUNCTIONS  ////////////////////////////////////////////////////////

vec4 applyPhongLighting(vec4 startColor)
{
    // Calculate the ambient light contribution
    vec3 a = light.ambient * material.ambient;

    // Calculate the diffuse light contribution
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 d = light.diffuse * diff * material.diffuse;;

    // Calculate reflection from specular light
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    //32 is the shininess
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 s = light.specular * spec * material.specular;

    vec4 result = vec4( (a.r + d.r + s.r), 
                        (a.g + d.g + s.g),
                        (a.b + d.b + s.b), 
                        1.0 );
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
    vec4 resColor = applyPhongLighting(ourColor);
    
    FragColor = texture(ourTexture, TexCoord) * resColor;
} 
