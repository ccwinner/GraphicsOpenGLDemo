#version 330

in vec4 vCol;
in vec2 vTex;

uniform sampler2D theTexture;
out vec4 colour;

void main()
{
    colour = texture(theTexture, vTex) * vCol;
}
