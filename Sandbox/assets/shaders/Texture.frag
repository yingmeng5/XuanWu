#version 330 core
layout(location = 0) out vec4 FragColor;

uniform vec3 m_SquareColor;	
uniform sampler2D u_Texture;

in vec2 t_Texture;		

void main()
{
	FragColor = texture(u_Texture, t_Texture);
}