#version 330 core
layout(location = 0)out vec4 FragColor;

in vec2 t_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
	FragColor = texture(u_Texture, t_TexCoord * 10.0)* u_Color;
}