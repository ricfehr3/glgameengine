#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 textColor;


void main()
{
   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   //vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(texture1, TexCoord).r);
   vec4 sampled = vec4(1.0, 1.0, 1.0, 0.75);
   FragColor = vec4(textColor, 1.0) * sampled;
   //FragColor = vec4(0.0, 0.0, 0.0, 0.5);
   //FragColor = texture(texture1, TexCoord);
}
