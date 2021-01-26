#version 440 core

layout(location = 0)in vec3 in_Position;
layout(location = 1)in vec3 in_Color;
layout(location = 2)in vec2 in_TexCoords;

layout (std140, binding = 0) uniform Matrices{
    mat4 in_Projection;  
    mat4 in_View;
    float u_FOV;
};

out vec3 v_Color;
out vec2 v_TexCoords;

void main(void){
    gl_Position = in_Projection * in_View * vec4(in_Position, 1.0);
    if(gl_Position.z < 0)
        gl_Position.z = 10;
    gl_Position.x /=u_FOV;
    gl_Position.y /=u_FOV;
    gl_Position.x /= gl_Position.z;
    gl_Position.y /= gl_Position.z;


    v_Color = in_Color;
    v_TexCoords = in_TexCoords;
}