#version 330 core

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColor;
layout(location = 2) in vec3 VertexNormal;
layout(location = 3) in vec2 VertexTexCoord;



uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 MNormal;


out vec3 color;
out vec3 Normal;
out vec3 FragPos;
out vec2 vs_tex_coord;

void main()
{
	color = VertexColor;

	vs_tex_coord = VertexTexCoord;

	Normal = MNormal * VertexNormal;
	

	FragPos = vec3(model *vec4(VertexPosition, 1.0));

	gl_Position = projection * view * vec4(FragPos, 1.0);
}
