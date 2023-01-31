#version 330 core

// Maximum number of lights for each type
#define MAX_N_LIGHTS 10

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
    float innerCutOff;
    float outerCutOff;

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
uniform Material material;

uniform int n_dirLights;
uniform DirectionalLight dirLights[MAX_N_LIGHTS];
uniform int n_pointLights;
uniform PointLight pointLights[MAX_N_LIGHTS];
uniform int n_spotlights;
uniform Spotlight spotlights[MAX_N_LIGHTS];


///  UTILITY FUNCTIONS  ////////////////////////////////////////////////////////

vec3 directionalLightContribute(DirectionalLight dl, vec3 normal, vec3 viewDir)
{
    // Calculate the light's direction
    vec3 lightDir = normalize(-dl.dir);

    // Calculate the ambient light contribution
    vec3 ambient = dl.ambient * vec3(texture(material.diffuse, TexCoord));

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = dl.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    // Calculate reflection from specular light
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = dl.specular * spec * vec3(texture(material.specular, TexCoord));

    return (ambient + diffuse + specular);
}

vec3 pointLightContribute(PointLight pl, vec3 normal, vec3 viewDir)
{
     // Calculate light's attenuation from distance
    float dist = length(pl.pos - FragPos);
    float attenuation = 1.0 / (pl.constant + pl.linear * dist + 
    		        pl.quadratic * (dist * dist));  

    // Calculate the light's direction
    vec3 lightDir = normalize(pl.pos - FragPos);

    // Calculate the ambient light contribution
    vec3 ambient = pl.ambient 
                    * vec3(texture(material.diffuse, TexCoord)) 
                    * attenuation;

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = pl.diffuse * diff 
                    * vec3(texture(material.diffuse, TexCoord)) 
                    * attenuation;

    // Calculate reflection from specular light
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pl.specular * spec 
                    * vec3(texture(material.specular, TexCoord))
                    * attenuation;

    return (ambient + diffuse + specular);    
}

vec3 spotlightContribution(Spotlight sl, vec3 normal, vec3 viewDir)
{
    // Calculate light's attenuation from distance
    float dist = length(sl.pos - FragPos);
    float attenuation = 1.0 / (sl.constant + sl.linear * dist + 
    		        sl.quadratic * (dist * dist));  

    // Calculate the light's direction
    vec3 lightDir = normalize(sl.pos - FragPos);

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-sl.dir)); 
    float epsilon = (sl.innerCutOff - sl.outerCutOff);
    float intensity = clamp((theta - sl.outerCutOff) / epsilon, 0.0, 1.0);

    // Calculate the ambient light contribution
    vec3 ambient = sl.ambient 
                    * vec3(texture(material.diffuse, TexCoord)) 
                    * attenuation;

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = sl.diffuse * diff 
                    * vec3(texture(material.diffuse, TexCoord)) 
                    * attenuation * intensity;

    // Calculate reflection from specular light
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = sl.specular * spec 
                    * vec3(texture(material.specular, TexCoord))
                    * attenuation * intensity;

    return (ambient + diffuse + specular);
}

vec4 applyPhongLighting(vec3 normal, vec3 viewDir)
{
    vec3 result = vec3(0);

    // Add directional light
    for (int i = 0; i < n_dirLights; i++)
    {
        result += directionalLightContribute(dirLights[i], normal, viewDir);
    }
    // Add point light
    for (int i = 0; i< n_pointLights; i++)
    {
        result += pointLightContribute(pointLights[i], normal, viewDir);
    }
    // Add spotlight
    for (int i = 0; i < n_spotlights; i++)
    {
        result += spotlightContribution(spotlights[i], normal, viewDir);
    }

    return vec4(result, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - FragPos);


    vec4 resColor = applyPhongLighting(norm, viewDir);
    
    FragColor = resColor;
} 
