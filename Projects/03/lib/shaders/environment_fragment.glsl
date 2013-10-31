#version 420
layout (binding=1) uniform sampler2D mirror;

uniform vec3 LV;
uniform vec3 KDIFF;
uniform vec3 KAMBIENT;
uniform vec3 KSPEC;
uniform float NSPEC;
uniform mat4 MIRRORT;

out vec3 fragcolor;

smooth in vec3 normal;
smooth in vec4 position;

void main() {
	vec4 normalxy = vec4(normalize(normal), 0.0f);
	normalxy.w = 1.0;
	vec4 texture_coord = (MIRRORT * normalxy);
	vec4 texture_color = texture(mirror, texture_coord.xy);

	// vector from object to light
	vec3 location_to_light_vector = normalize(LV - position.xyz);

	// view ray
	vec3 location_to_view_ray = normalize( -position.xyz );

	// halfway vector between light vector and view ray
	vec3 halfway_vec = normalize(location_to_light_vector + location_to_view_ray);

	// calculate the diffused as dot between normal and direction of light
	float diffuse_dot = dot(normalize(normal), location_to_light_vector);
	if(diffuse_dot < 0.0f) {
		diffuse_dot = 0;
	} 

	// calculate the specular component
	float specular_base = dot(halfway_vec, normalize(normal));

	if( specular_base < 0 ) {
		specular_base = 0;
	}

	// calculate triangle color
	fragcolor = 
		texture_color.xyz * (KSPEC * pow(specular_base, NSPEC) + KDIFF * diffuse_dot) + KAMBIENT;
}
