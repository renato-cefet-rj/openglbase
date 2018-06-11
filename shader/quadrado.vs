#version 150

void main(void) 
{
	const vec4 vertices[4] = vec4[4]
	(	 
		vec4( -0.5,  0.5, 0.5, 1.0),
		vec4(  0.5,  0.5, 0.5, 1.0),
		vec4(  0.5, -0.5, 0.5, 1.0),
		vec4( -0.5, -0.5, 0.5, 1.0)
	);

    gl_Position = vertices[gl_VertexID];
    //gl_Position = vec4(0.0,0.0,0.5,1.0);
}

