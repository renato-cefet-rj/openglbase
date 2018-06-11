#version 400

in vec3 colorToFragmentShader;
out vec4 color;

void main(void) 
{
	color = vec4(colorToFragmentShader, 1.0f);
}
