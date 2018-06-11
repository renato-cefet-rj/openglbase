#version 400

uniform vec4 defaultColor;
out vec4 color;

void main(void) 
{
	if(gl_FragCoord.x > 400)
	{
		color = vec4(0.0f,1.0f,1.0f,0.5f);
	}
	else
	{
		color = vec4(1.0f,0.0f,0.0f,0.5f);
	}

}
