#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "platform/opengl.hpp"
#include "core/log.hpp"
#include "platform/compiler.hpp"

static void glClearErrors(){
    while(glGetError() != GL_NO_ERROR);
}

static void glGetErrors(int line){
    GLenum error;
    while((error = glGetError())){
        LogError("OpenGL: %: at line %",error, line);
    }
}

#define GL(x) do{glClearErrors(); x; glGetErrors(SX_THIS_LINE);}while(0)

#endif//DEBUG_HPP