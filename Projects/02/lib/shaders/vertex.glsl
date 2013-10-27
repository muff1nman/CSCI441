#version 420

layout (location=0) in vec3 model_coord;
layout (location=1) in vec3 normal_for_coord;

uniform mat4 MV;  // modelview matrix in homogenous coordinates
uniform mat4 P;  // projection matrix in homogenous coordinates
uniform mat4 NMV;
uniform vec3 LV;
uniform vec3 KDIFF;

flat out vec3 color;

void main() {	
	// calculate position 
	gl_Position  = MV * vec4(model_coord, 1);

	//calculate the transformed normal
	vec4 normal = NMV * vec4(normal_for_coord,0.0f);

	// calculate triangle color
	vec3 location_to_light_vector = LV - gl_Position.xyz;

	float diffuse_dot = dot(normalize(normal.xyz), normalize(location_to_light_vector));
	if(diffuse_dot < 0.0f) {
		color = vec3(0.2,0.0,0.0);
	} else {
		color = KDIFF * diffuse_dot + vec3(0.1,0.1,0.1);
	}

	gl_Position = P * gl_Position;

}
