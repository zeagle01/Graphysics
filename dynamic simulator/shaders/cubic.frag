#version 330 core
in vec3 vbo_color;
in vec2 vbo_texCoord;

out vec4 frag_color;
uniform sampler2D our_tex0;
uniform sampler2D our_tex1;

uniform vec4 my_color;
void main(){

	//frag_color=texture(our_tex1,vbo_texCoord);
	frag_color=mix(texture(our_tex0,vbo_texCoord),texture(our_tex1,vbo_texCoord),0.2);
}