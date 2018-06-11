#version 400

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;
uniform mat4 MVP;
out vec3 colorToFragmentShader;

void main(void) 
{
	gl_Position = MVP * vec4(position,1.0);
	colorToFragmentShader = color;
}
