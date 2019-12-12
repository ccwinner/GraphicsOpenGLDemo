#version 330

in vec4 vCol;
in vec2 vTex;

out vec4 colour;

struct DirectionLight {
    vec3 colour;
    float ambientIntensity;
};

uniform sampler2D theTexture;
uniform DirectionLight directionLight;

void main()
{
    vec4 ambientColour = vec4(directionLight.colour, 1.0f) * directionLight.ambientIntensity;
    colour = texture(theTexture, vTex) * ambientColour * vCol;
}
