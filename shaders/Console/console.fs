#version 330
in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D text;
uniform vec3 textColor;
void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(text, TexCoords).r);
	FragColor = vec4(textColor, 1.0) * sampled;
}
