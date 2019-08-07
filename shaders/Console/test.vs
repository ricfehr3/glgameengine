#version 330 core
//layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aTexCoords;

in vec4 vertex;

out vec2 TexCoord;

uniform mat4 projection;

void main()
{
   //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   //TexCoord = vec2(aTexCoords.x, aTexCoords.y); 
   gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
   TexCoord = vertex.zw;
}
