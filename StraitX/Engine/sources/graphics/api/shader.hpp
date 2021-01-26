#ifndef STRAITX_SHADER_HPP
#define STRAITX_SHADER_HPP

#include "platform/types.hpp"

namespace StraitX{

class Shader{
public:
    enum Language: u8{
        Unknown = 0,
        SPIRV,
        GLSL,    
    };
private:

public:

};

}//namesapce StraitX::

#endif //STRAITX_SHADER_HPP