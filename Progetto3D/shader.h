#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Lib.h"

class Shader
{
public:
    // the program ID
    unsigned int ID;

    Shader();
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // use/activate the shader
    void use();
    unsigned int get_ID();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, vec3 value) const;
    void setVec4(const std::string& name, vec4 value) const;
    void setMatrix3f(const std::string& name, mat3 value) const;
    void setMatrix4f(const std::string& name, mat4 value) const;
};

/** Contains the name of the uniform variables used in the main shaders. */
namespace umain 
{
    const string model = "Model";
    const string view = "View";
    const string projection = "Projection";

    const string sceltaVS = "sceltaVS";
    const string sceltaFS = "sceltaFS";
    
    const string time = "time";
    const string resolution = "resolution";
    const string texture = "id_tex";
    const string cam_position = "viewPos";
    
    const string light_position = "light.position";
    const string light_color = "light.color";
    const string light_power = "light.power";

    const string material_ambient = "material.ambient";
    const string material_diffuse = "material.diffuse";
    const string material_specular = "material.specular";
    const string material_shininess = "material.shininess";
}

#endif // !SHADER_H
