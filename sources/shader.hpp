#ifndef SHADER_HPP 
#define SHADER_HPP 

#include "platform/opengl.hpp"
#include "platform/types.hpp"
#include "platform/file.hpp"
#include "core/log.hpp"
#include "core/assert.hpp"

using namespace StraitX;

class GraphicsPipeline;

class Shader{
private:
    u32 Id = 0;

    friend class GraphicsPipeline;
public:
    void Create(const char *filename, GLenum type){
        LogTrace("Shaders start");
        Assert(glCreateShader);
        Id = glCreateShader(type);
        if(!File::Exist(filename)){
            LogWarn("OpenGL: Shader: '%' does not exist",filename);
            return;
        }
        File src_file;
        Assert(src_file.Open(filename, File::Mode::Read) == Result::Success);

        int src_file_size = src_file.Size();

        char *sources = (char*)alloca(src_file_size + 1);
        src_file.Read(sources, src_file_size);
        sources[src_file_size] = 0;

        glShaderSource(Id, 1, &sources, &src_file_size);
        glCompileShader(Id);
        CheckErrors();
    }

    void Destroy(){
        glDeleteShader(Id);
    }
private:
    void CheckErrors(){
        int status;
        glGetShaderiv(Id, GL_COMPILE_STATUS, &status);

        if(status != GL_TRUE){
            int log_length;
            glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &log_length);
            char *log = (char*)alloca(log_length);
            glGetShaderInfoLog(Id, log_length, &log_length, log);
            LogError("OpenGL: Shader: %", log);
        }
    }
};



#endif//SHADER_HPP 