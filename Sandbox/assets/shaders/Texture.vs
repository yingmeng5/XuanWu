#version 330 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_Texture;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Model;

out vec2 t_Texture;
void main()
{
	t_Texture = a_Texture;
	gl_Position = u_ViewProjectionMatrix * u_Model * vec4(a_Pos, 1.0);
}