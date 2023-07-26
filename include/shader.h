#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

// Declare LoadShaders function
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif // SHADER_H