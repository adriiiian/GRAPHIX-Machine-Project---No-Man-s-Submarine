#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 transform;

uniform mat4 view;

uniform mat4 projection;

void main(){
	//Converts it to vec4
	//gl_Position
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
}