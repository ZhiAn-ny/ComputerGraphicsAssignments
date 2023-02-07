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

namespace shd 
{
    const int Phong_Phong = -1;
    const int BlinnPhong_Phong = -2;
    const int Phong_interp = -3;
    const int BlinnPhong_interp = -4;
    const int cartoon = -5;
} // !shd

#endif // !SHADER_H
