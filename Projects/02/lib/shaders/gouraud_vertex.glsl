#version 420

layout (location=0) in vec3 model_coord;
layout (location=1) in vec3 normal_for_coord;

uniform mat4 MV;  // modelview matrix in homogenous coordinates
uniform mat4 P;  // projection matrix in homogenous coordinates
uniform mat3 NMV;
uniform vec3 LV;
uniform vec3 KDIFF;
uniform vec3 KAMBIENT;
uniform vec3 KSPEC;
uniform float NSPEC;

smooth out vec3 color;

void main() {	
	float flip = -1.0;

	// calculate position 
	gl_Position  = MV * vec4(model_coord, 1);

	//calculate the transformed normal
	vec3 normal = flip * normalize(NMV * normal_for_coord);

	// vector from object to light
	vec3 location_to_light_vector = normalize(LV - gl_Position.xyz);

	// view ray
	vec3 location_to_view_ray = normalize( -gl_Position.xyz );

	// halfway vector between light vector and view ray
	vec3 halfway_vec = (location_to_light_vector + location_to_view_ray) / 2.0;

	// calculate the diffused as dot between normal and direction of light
	float diffuse_dot = dot(normal, location_to_light_vector);
	if(diffuse_dot < 0.0f) {
		diffuse_dot = 0;
	} 

	// calculate the specular component
	float specular_base = dot(halfway_vec, normal);

	if( specular_base < 0 ) {
		specular_base = 0;
	}

	// calculate triangle color
	color = KSPEC * pow(specular_base, NSPEC) + KDIFF * diffuse_dot + KAMBIENT;
	gl_Position = P * gl_Position;

}
