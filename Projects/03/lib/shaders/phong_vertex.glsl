#version 420

layout (location=0) in vec3 model_coord;
layout (location=1) in vec3 normal_for_coord;

uniform mat4 MV; // modelview matrix in homogenous coordinates
uniform mat4 P; // projection matrix in homogenous coordinates
uniform mat3 NMV;
uniform mat4 TXT; // transform matrix to be applied after MV to convert vertex to texture coords

smooth out vec3 normal;
smooth out vec4 position;
smooth out vec3 texture_coord;

void main() {	
	float flip = -1.0;

	// calculate position 
	position  = MV * vec4(model_coord, 1);

	// calculate texture coord
	texture_coord = TXT * vec4(model_coord,1);

	//calculate the transformed normal
	normal = flip * normalize(NMV * normal_for_coord);

	gl_Position = P * position;

}
