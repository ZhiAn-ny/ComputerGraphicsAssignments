#version 330 core

// Maximum number of lights for each type
#define MAX_N_LIGHTS 20

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 ourColor;

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

struct MaterialMtl {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float     shininess;
}; 
  

//  UNIFORM VARIABLES  /////////////////////////////////////////////////////////

uniform vec3 camPos;

uniform int shadingType;

uniform bool useTexture;
uniform MaterialMtl material;
uniform Material base;

uniform int n_dirLights;
uniform DirectionalLight dirLights[MAX_N_LIGHTS];
uniform int n_pointLights;
uniform PointLight pointLights[MAX_N_LIGHTS];
uniform int n_spotlights;
uniform Spotlight spotlights[MAX_N_LIGHTS];


///  UTILITY FUNCTIONS  ////////////////////////////////////////////////////////

Material getObjectColor()
{
    Material objColor;
    if (useTexture)
    {
        objColor.ambient = vec3(texture(material.diffuse, TexCoord));
        objColor.diffuse = vec3(texture(material.diffuse, TexCoord));
        objColor.specular = vec3(texture(material.specular, TexCoord));
        objColor.shininess = material.shininess;
    } else {
        objColor.ambient = base.ambient;
        objColor.diffuse = base.diffuse;
        objColor.specular = base.specular;
        objColor.shininess = base.shininess;
    }
    return objColor;
}

///  PHONG SHADING  ////////////////////////////////////////////////////////

vec3 DLContributePhong(DirectionalLight dl, vec3 normal, vec3 viewDir, Material objColor)
{
    // Calculate the light's direction
    vec3 lightDir = normalize(-dl.dir);

    // Calculate the ambient light contribution
    vec3 ambient = dl.ambient * objColor.ambient;

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = dl.diffuse * diff * objColor.diffuse;

    // Calculate reflection from specular light
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objColor.shininess);
    vec3 specular = dl.specular * spec * objColor.specular;

    return (ambient + diffuse + specular);
}

vec3 PLContributePhong(PointLight pl, vec3 normal, vec3 viewDir, Material objColor)
{
     // Calculate light's attenuation from distance
    float dist = length(pl.pos - FragPos);
    float attenuation = 1.0 / (pl.constant + pl.linear * dist + 
    		        pl.quadratic * (dist * dist));  

    // Calculate the light's direction
    vec3 lightDir = normalize(pl.pos - FragPos);

    // Calculate the ambient light contribution
    vec3 ambient = pl.ambient * objColor.ambient * attenuation;

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = pl.diffuse * diff * objColor.diffuse * attenuation;

    // Calculate reflection from specular light
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objColor.shininess);
    vec3 specular = pl.specular * spec * objColor.specular * attenuation;

    return (ambient + diffuse + specular);    
}

vec3 SLContributePhong(Spotlight sl, vec3 normal, vec3 viewDir, Material objColor)
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
    vec3 ambient = sl.ambient * objColor.ambient * attenuation;

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = sl.diffuse * diff * objColor.diffuse * attenuation * intensity;

    // Calculate reflection from specular light
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), objColor.shininess);
    vec3 specular = sl.specular * spec * objColor.specular * attenuation * intensity;

    return (ambient + diffuse + specular);
}

vec4 applyPhongLighting(vec3 normal, vec3 viewDir, Material objColor)
{
    vec3 result = vec3(0);

    // Add directional light
    for (int i = 0; i < n_dirLights; i++)
    {
        result += DLContributePhong(dirLights[i], normal, viewDir, objColor);
    }
    // Add point light
    for (int i = 0; i< n_pointLights; i++)
    {
        result += PLContributePhong(pointLights[i], normal, viewDir, objColor);
    }
    // Add spotlight
    for (int i = 0; i < n_spotlights; i++)
    {
        result += SLContributePhong(spotlights[i], normal, viewDir, objColor);
    }

    return vec4(result, 1.0);
}

///  BLINN-PHONG SHADING  //////////////////////////////////////////////////////

vec3 DLContributeBlinnPhong(DirectionalLight dl, vec3 normal, vec3 viewDir, Material objColor)
{
    // Calculate the light's direction
    vec3 lightDir = normalize(-dl.dir);

    // Calculate the ambient light contribution
    vec3 ambient = dl.ambient * objColor.ambient;

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = dl.diffuse * diff * objColor.diffuse;

    // Calculate reflection from specular light
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), objColor.shininess);
    vec3 specular = dl.specular * spec * objColor.specular;

    return (ambient + diffuse + specular);
}

vec3 PLContributeBlinnPhong(PointLight pl, vec3 normal, vec3 viewDir, Material objColor)
{
     // Calculate light's attenuation from distance
    float dist = length(pl.pos - FragPos);
    float attenuation = 1.0 / (pl.constant + pl.linear * dist + 
    		        pl.quadratic * (dist * dist));  

    // Calculate the light's direction
    vec3 lightDir = normalize(pl.pos - FragPos);

    // Calculate the ambient light contribution
    vec3 ambient = pl.ambient * objColor.ambient * attenuation;

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = pl.diffuse * diff * objColor.diffuse * attenuation;

    // Calculate reflection from specular light
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), objColor.shininess);
    vec3 specular = pl.specular * spec * objColor.specular * attenuation;

    return (ambient + diffuse + specular);    
}

vec3 SLContributeBlinnPhong(Spotlight sl, vec3 normal, vec3 viewDir, Material objColor)
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
    vec3 ambient = sl.ambient * objColor.ambient * attenuation;

    // Calculate the diffuse light contribution
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = sl.diffuse * diff * objColor.diffuse * attenuation * intensity;

    // Calculate reflection from specular light
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), objColor.shininess);
    vec3 specular = sl.specular * spec * objColor.specular * attenuation * intensity;

    return (ambient + diffuse + specular);
}

vec4 applyBlinnPhongLighting(vec3 normal, vec3 viewDir, Material objColor)
{
    vec3 result = vec3(0);

    // Add directional light
    for (int i = 0; i < n_dirLights; i++)
    {
        result += DLContributeBlinnPhong(dirLights[i], normal, viewDir, objColor);
    }
    // Add point light
    for (int i = 0; i< n_pointLights; i++)
    {
        result += PLContributeBlinnPhong(pointLights[i], normal, viewDir, objColor);
    }
    // Add spotlight
    for (int i = 0; i < n_spotlights; i++)
    {
        result += SLContributeBlinnPhong(spotlights[i], normal, viewDir, objColor);
    }

    return vec4(result, 1.0);
}

///  CARTOON SHADING  //////////////////////////////////////////////////////////

vec3 DLContributeCartoon(DirectionalLight dl, vec3 normal, vec3 viewDir, Material objColor)
{
    // Calculate the light's direction
    vec3 lightDir = normalize(-dl.dir);
    float intensity = normalize(dot(lightDir, normal));

    if (intensity > 0.95)
        return vec3(1.0, 0.5, 0.5);

    else if (intensity > 0.5)
        return vec3(0.8, 0.4, 0.4);

    else if (intensity > 0.25)
        return vec3(0.7, 0.3, 0.3);

    else
        return vec3(0.6, 0.3, 0.3);
}

vec3 PLContributeCartoon(PointLight pl, vec3 normal, vec3 viewDir, Material objColor)
{
    vec3 lightDir = normalize(pl.pos - FragPos);
    float intensity = normalize(dot(lightDir, normal));

    if (intensity > 0.95)
        return vec3(1.0, 0.5, 0.5);

    else if (intensity > 0.5)
        return vec3(0.8, 0.4, 0.4);

    else if (intensity > 0.25)
        return vec3(0.7, 0.3, 0.3);

    else
        return vec3(0.6, 0.3, 0.3);  
}

vec3 SLContributeCartoon(Spotlight sl, vec3 normal, vec3 viewDir, Material objColor)
{
    vec3 lightDir = normalize(sl.pos - FragPos);
    float intensity = normalize(dot(lightDir, normal));

     if (intensity > 0.95)
        return vec3(1.0, 0.5, 0.5);

    else if (intensity > 0.5)
        return vec3(0.8, 0.4, 0.4);

    else if (intensity > 0.25)
        return vec3(0.7, 0.3, 0.3);

    else
        return vec3(0.6, 0.3, 0.3); 
}

vec4 applyCartoonShading(vec3 normal, vec3 viewDir, Material objColor)
{
    vec3 result = vec3(0);

    // Add directional light
    for (int i = 0; i < n_dirLights; i++)
    {
        result += DLContributeCartoon(dirLights[i], normal, viewDir, objColor);
    }
//    // Add point light
//    for (int i = 0; i< n_pointLights; i++)
//    {
//        result += PLContributeCartoon(pointLights[i], normal, viewDir, objColor);
//    }
//    // Add spotlight
//    for (int i = 0; i < n_spotlights; i++)
//    {
//        result += SLContributeCartoon(spotlights[i], normal, viewDir, objColor);
//    }

    return vec4(result, 1.0);
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - FragPos);

    Material objColor = getObjectColor();

    vec4 resColor = vec4(1);

    switch (shadingType)
    {
        case -1: // Phong lighting model with Phong shading
        case -3: // Phong lighting model with interpolative shading
            FragColor = applyPhongLighting(norm, viewDir, objColor);
            break;
        case -2: // Blinn-Phong lighting model with Phong shading
        case -4: // Blinn-Phong lighting model with interpolative shading
            FragColor = applyBlinnPhongLighting(norm, viewDir, objColor);
            break;
        case -5: // Cartoon shading
            FragColor = applyCartoonShading(norm, viewDir, objColor);
            break;
        default:
            break;
    }
    
} 
