#version 420

layout (location=0) in vec3 model_coord;
layout (location=1) in vec3 normal_for_coord;

uniform mat4 MV;  // modelview matrix in homogenous coordinates
uniform mat4 P;  // projection matrix in homogenous coordinates
uniform mat3 NMV;
uniform vec3 LV;
uniform vec3 KDIFF;
uniform vec3 KAMBIENT;

flat out vec3 color;

void main() {	
	// calculate position 
	gl_Position  = MV * vec4(model_coord, 1);

	//calculate the transformed normal
	vec3 normal = normalize(NMV * normal_for_coord);

	// calculate triangle color
	vec3 location_to_light_vector = normalize(-LV + gl_Position.xyz);

	float diffuse_dot = dot(normal, location_to_light_vector);
	if(diffuse_dot < 0.0f) {
		diffuse_dot = 0;
	} 
	
	color = KDIFF * diffuse_dot + KAMBIENT;
	gl_Position = P * gl_Position;

}
