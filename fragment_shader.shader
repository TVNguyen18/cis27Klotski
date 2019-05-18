/**
* Program Name: KlotSki Game
* Discussion  : Fragment Shader
* Written by  : Anh Tran
* Date        : 2019/05/17
*/

#version 410

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;

out vec4 pixelColor;

uniform vec4 my_Color;
uniform sampler2D my_Texture;

void main() {	
	//pixelColor = my_Color;
	pixelColor = texture2D(my_Texture, vs_texcoord);
}