#version 330 core
in vec3 normal;
in vec2 tex_cood;
in vec3 frag_position;
out vec4 frag_color;

uniform sampler2D texture_diffuse1;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;

void main(){
	vec4 tex_color=vec4(texture(texture_diffuse1,tex_cood));
	//frag_color=tex_color;




	vec3 obj_color=vec3(0,1,0);

	//ambient
	float Ca=0.1;
	vec3 ambient_color=Ca*light_color*vec3(tex_color);
	//diffuse
	vec3 norm=normalize(normal);
	vec3 light_dir= normalize(light_position-frag_position);
	float diff=max(dot(light_dir,norm),0);
	//vec3 diffuse_color=diff*light_color*vec3(tex_color);
	vec3 diffuse_color=diff*light_color*obj_color;
	//specular
	vec3 reflect_dir=reflect(light_dir,norm);
	vec3 view_dir=view_position-frag_position;
	float steep=32;
	float spec=pow(max(dot(view_dir,reflect_dir),0),steep);
	float Cs=0.5;
	vec3 specular_color=Cs*spec*light_color*obj_color;


	//output color
	//vec3 result_color=(diffuse_color+ambient_color+specular_color)*obj_color;
	//vec3 result_color=diffuse_color+ambient_color+specular_color;
	vec3 result_color=diffuse_color+ambient_color;
	//vec3 result_color=(diffuse_color+ambient_color)*obj_color;
	//vec3 result_color=(specular_color)*obj_color;
	//vec3 result_color=diffuse_color;
	//vec3 result_color=vec3(diff,0,0);
	frag_color=vec4(result_color,1);
	
	//frag_color=tex_color*vec4(light_color,1);
	//frag_color=vec4(diffuse_color*obj_color,1);
	//frag_color=vec4(norm*obj_color,1);

}