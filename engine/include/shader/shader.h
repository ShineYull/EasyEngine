#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Shine {
    class Shader
    {
    public:
        // Program ID
        unsigned int ID;

        // The constructor reads and builds the shader
        Shader(const char* vertexPath, const char* fragmentPath);
        // Use/activate the program
        void use();
        // uniform tool functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
    };
}


#endif