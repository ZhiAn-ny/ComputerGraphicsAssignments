#version 330 core

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
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
}; 
  

//  UNIFORM VARIABLES  /////////////////////////////////////////////////////////

uniform vec3 camPos;
uniform Light light;
uniform Material material;


///  UTILITY FUNCTIONS  ////////////////////////////////////////////////////////

vec4 applyPhongLighting()
{
    // Calculate the ambient light contribution
    vec3 a = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // Calculate the diffuse light contribution
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 d = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    // Calculate reflection from specular light
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    //32 is the shininess
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 s = light.specular * spec * vec3(texture(material.specular, TexCoord));

    vec4 result = vec4( (a.r + d.r + s.r), 
                        (a.g + d.g + s.g),
                        (a.b + d.b + s.b), 
                        1.0 ); // We always set the opacity to its maximum
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
    vec4 resColor = applyPhongLighting();
    
    FragColor = resColor;
} 
