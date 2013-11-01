#version 420

layout (location=0) in vec3 model_coord;
layout (location=1) in vec3 normal_for_coord;
layout (location=2) in vec2 texture_coord_xy;

uniform mat4 MV; // modelview matrix in homogenous coordinates
uniform mat4 P; // projection matrix in homogenous coordinates
uniform mat3 NMV;

smooth out vec3 normal;
smooth out vec4 position;
smooth out vec2 texture_coord;

void main() {	
	texture_coord = texture_coord_xy;
	float flip = 1.0;

	// calculate position 
	position  = MV * vec4(model_coord, 1);

	//calculate the transformed normal
	normal = flip * normalize(NMV * normal_for_coord);

	gl_Position = P * position;

}
