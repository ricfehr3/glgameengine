#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float bigSmile;

uniform sampler2D woodTexture;
uniform sampler2D awesomeTexture;

void main()
{
	FragColor = mix(texture(woodTexture, TexCoord), texture(awesomeTexture, vec2(-TexCoord.x, TexCoord.y)), bigSmile);
}
