#version 330 core

// Maximum number of lights for each type
#define MAX_N_LIGHTS 20

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 ourColor;

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

uniform mat4 Model, View, Projection;
uniform mat3 NormalMatrix;

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
    // Transform the coordinate of the vertex to elaborate (aPos) into view coordinates
    vec3 eyePosition = vec3(View * Model * vec4(aPos,1.0));
    // Transform the posizione of the light into view coordinates
    vec3 eyeLightPos = vec3(View * vec4(pl.pos, 1.0));

    // Calculate the light's direction
    vec3 lightDir = normalize(vec3(eyeLightPos - eyePosition));

    // Calculate light's attenuation from distance
    float dist = length(eyeLightPos - eyePosition);
    float attenuation = 1.0 / (pl.constant + pl.linear * dist + 
    		        pl.quadratic * (dist * dist));  

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
     // Transform the coordinate of the vertex to elaborate (aPos) into view coordinates
    vec3 eyePosition = vec3(View * Model * vec4(aPos,1.0));
    // Transform the posizione of the light into view coordinates
    vec3 eyeLightPos = vec3(View * vec4(sl.pos, 1.0));

    // Calculate light's attenuation from distance
    float dist = length(sl.pos - eyePosition);
    float attenuation = 1.0 / (sl.constant + sl.linear * dist + 
    		        sl.quadratic * (dist * dist));  

    // Calculate the light's direction
    vec3 lightDir = normalize(eyeLightPos - eyePosition);

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
    // Transform the coordinate of the vertex to elaborate (aPos) into view coordinates
    vec3 eyePosition = vec3(View * Model * vec4(aPos,1.0));
    // Transform the posizione of the light into view coordinates
    vec3 eyeLightPos = vec3(View * vec4(pl.pos, 1.0));

    // Calculate the light's direction
    vec3 lightDir = normalize(vec3(eyeLightPos - eyePosition));

     // Calculate light's attenuation from distance
    float dist = length(eyeLightPos - eyePosition);
    float attenuation = 1.0 / (pl.constant + pl.linear * dist + 
    		        pl.quadratic * (dist * dist));  

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
    // Transform the coordinate of the vertex to elaborate (aPos) into view coordinates
    vec3 eyePosition = vec3(View * Model * vec4(aPos,1.0));
    // Transform the posizione of the light into view coordinates
    vec3 eyeLightPos = vec3(View * vec4(sl.pos, 1.0));

    // Calculate light's attenuation from distance
    float dist = length(eyeLightPos - eyePosition);
    float attenuation = 1.0 / (sl.constant + sl.linear * dist + 
    		        sl.quadratic * (dist * dist));  

    // Calculate the light's direction
    vec3 lightDir = normalize(eyeLightPos - eyePosition);

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

////////////////////////////////////////////////////////////////////////////////

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;

    FragPos = vec3(Model * vec4(aPos, 1.0));

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - vec3(View * Model * vec4(aPos,1.0)));

    Material objColor = getObjectColor();
    ourColor = aColor;

    if (shadingType == -1 || shadingType == -2)
    {
        // Phong lighting model with Phong shading
        // Blinn-Phong lighting model with Phong shading
            // Per usare lo shading di Phong
            /* Applicheremo alla normale di ogni vertice in coordinate 
            dell’oggetto la trasposta dell’ inversa della matrice model view (M−1)T 
            (dove M=View Model). La normale trasformata sarà data in output e 
            rappresenterà quindi l’input del fragment shader. Quindi le normali 
            saranno interpolate sui lati della primitiva prima di arrivare nel 
            fragment shader e sarà nel fragment shader che si calcolerà 
            l’equazione dell’illuminazione e quindi il colore per ogni frammento
            della scena.*/
        mat3 VMmatrix = mat3(transpose(inverse(View * Model)));
        Normal = VMmatrix * aNormal;
    }
    else Normal = NormalMatrix * aNormal;

        // To apply the interpolated shading, we must first calculate the
    // illumination equation on each vertex of the mesh, then interpolate the
    // colors along the edges.
    switch (shadingType)
    {
        case -3: // Phong lighting model with interpolative shading
            ourColor= applyPhongLighting(norm, viewDir, objColor);
            break;
        case -4: // Blinn-Phong lighting model with interpolative shading
            ourColor = applyBlinnPhongLighting(norm, viewDir, objColor);
            break;
        default:
            break;
    }

}