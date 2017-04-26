#version 330 core
layout (location=0) in vec3 _vbo_position;
layout (location=1) in vec3 _vbo_normal;
layout (location=2) in vec2 _vbo_tex_cood;

out vec3 normal;
out vec2 tex_cood;
out vec3 frag_position;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	//gl_Position=vec4(_vbo_position,1.0);
	gl_Position=projection*view*model*vec4(_vbo_position,1.0);

	normal=_vbo_normal;
	tex_cood=_vbo_tex_cood;
	frag_position=vec3(model*vec4(_vbo_position,1.0));
}