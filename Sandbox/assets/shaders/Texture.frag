#version 330 core
layout(location = 0)out vec4 FragColor;

uniform sampler2D u_Texture;

in vec2 t_TexCoord;

void main()
{
	FragColor = texture(u_Texture, t_TexCoord * 10);
}