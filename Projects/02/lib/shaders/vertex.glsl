#version 420

layout (location=0) in vec3 model_coord;

uniform mat4 MV;  // modelview matrix in homogenous coordinates
uniform mat4 P;  // projection matrix in homogenous coordinates

void main() {	
	gl_Position  = P * MV * vec4(model_coord, 1);
}
