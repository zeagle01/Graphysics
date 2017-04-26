#version 330 core
layout (location=0) in vec3 _vbo_position;
layout (location=1) in vec3 _vbo_color;
layout (location=2) in vec2 _vbo_texCoord;

out vec3 vbo_color;
out vec2 vbo_texCoord; 

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position=projection*view*model*vec4(_vbo_position,1.0);
	//gl_Position=vec4(_vbo_position,1.0);
	//gl_Position=vec4(_vbo_texCoord.x,_vbo_texCoord.y,0.0,1.0);
	vbo_color=_vbo_color;
	vbo_texCoord=_vbo_texCoord;

}
