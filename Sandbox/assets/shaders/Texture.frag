#version 330 core
layout(location = 0)out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform float u_TilingFactor;
uniform vec4 u_Color;

void main()
{
	//FragColor = texture(u_Texture, v_TexCoord * u_TilingFactor)* u_Color;
	FragColor = v_Color;
}