#version 420

uniform vec3 LV;
uniform vec3 KDIFF;
uniform vec3 KAMBIENT;
uniform vec3 KSPEC;
uniform float NSPEC;

out vec3 fragcolor;

smooth in vec3 normal;
smooth in vec4 position;

void main() {

	// vector from object to light
	vec3 location_to_light_vector = normalize(LV - position.xyz);

	// view ray
	vec3 location_to_view_ray = normalize( -position.xyz );

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
	fragcolor = KSPEC * pow(specular_base, NSPEC) + KDIFF * diffuse_dot + KAMBIENT;
}
