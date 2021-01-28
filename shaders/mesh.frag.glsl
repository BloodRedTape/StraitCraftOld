#version 440 core

in vec2 v_TexCoords;

uniform sampler2D u_Texture;

out vec4 f_Color;

void main(void){
    f_Color = texture(u_Texture, v_TexCoords);
}