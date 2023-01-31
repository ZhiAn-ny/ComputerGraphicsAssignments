#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

//  DATA STRUCTURES  ///////////////////////////////////////////////////////////

struct PointLight {
    vec3 pos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
	float linear;
	float quadratic;
};
struct DirectionalLight {
    vec3 dir;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct Spotlight {
    vec3 pos;
    vec3 dir;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
	float linear;
	float quadratic;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
}; 
  

//  UNIFORM VARIABLES  /////////////////////////////////////////////////////////

uniform vec3 camPos;
uniform Spotlight light;
uniform Material material;


///  UTILITY FUNCTIONS  ////////////////////////////////////////////////////////

vec4 applyPhongLighting()
{
    // Calculate light's attenuation from distance
    float dist = length(light.pos - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + 
    		        light.quadratic * (dist * dist));  

    //// Calculate the light's direction
    vec3 lightDir = normalize(light.pos - FragPos); // for point light (frag->light)
    // vec3 lightDir = normalize(-light.dir); // for dir light (light->target)


    // Calculate the ambient light contribution
    vec3 ambient = light.ambient 
                    * vec3(texture(material.diffuse, TexCoord)) * attenuation;


    // Calculate the diffuse light contribution
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff 
                    * vec3(texture(material.diffuse, TexCoord)) * attenuation;

    // Calculate reflection from specular light
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec 
                    * vec3(texture(material.specular, TexCoord)) * attenuation;

    vec4 result = vec4( (ambient.r + diffuse.r + specular.r), 
                        (ambient.g + diffuse.g + specular.g),
                        (ambient.b + diffuse.b + specular.b), 
                        1.0 ); // We always set the opacity to its maximum
    return result;
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
    vec3 lightDir = normalize(light.pos - FragPos);
    float theta = dot(lightDir, normalize(-light.dir));


    vec4 resColor = vec4(light.ambient * texture(material.diffuse, TexCoord).rgb, 1.0);

    if (theta > light.cutOff)
    {
        resColor = applyPhongLighting();
    }

    
    FragColor = resColor;
} 
