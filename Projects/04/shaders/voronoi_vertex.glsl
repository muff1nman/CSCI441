#version 420

/* --------------- INPUT VARIABLES -------------- */
/* In a vertex shader, they are vertex attributes */
/* location=... informs the shader of the index   */
/* of the attribute - it has to be in agreement   */
/* with the first argument of attachAttribute()   */
/* in the CPU code                                */
/* ---------------------------------------------- */

layout (location=0) in vec2 model_coord;
layout (location=2) in vec2 site;
layout (location=3) in vec3 color;
layout (location=4) in float angular;

layout (binding=1) uniform sampler2D tex;

uniform int SITEDISPLAY = 1;
//uniform mat4 ROT;
uniform float time;

/* -------------- OUTPUT VARIABLES -------------- */
/* Attributes of the processed vertices           */
/* Interpolated by the rasterizer and sent with   */
/* fragments to the fragment shader               */
/* ---------------------------------------------- */

// x- and y- coordinates scaled to 0...1
// since we are using parallel projection, linear
// interpolation in screen space is the same
// as perspectively correct interpolation (and cheaper),
// so this is what we are requesting here

noperspective out vec2 frag_pos;

// same for color

flat out vec3 col;
flat out vec2 site_location;

flat out int show;

// if = 2 we will rotate the wave in the fragment shader

flat out int instance;

/* ---------------------------------------------- */
/* ----------- MAIN FUNCTION -------------------- */
/* goal: set gl_Position (location of the         */
/* projected vertex in homogenous coordinates)    */
/* and values of the output variables             */
/* ---------------------------------------------- */

void main()
{
  // vertices of the square scaled to 0...1

  /*param = model_coord;*/
  /*wdir = wave_dir;*/
  col = color;

	float angle = angular * time;
	mat3 site_speed = mat3(
		vec3(cos(angle), sin(angle), 0.0),
		vec3(-sin(angle),cos(angle), 0.0),
		vec3(0.0,0.0,1.0)
	);

	site_location = (site_speed * vec3(site,0.0f)).xy;

	col = texture(tex, (vec2(1.0f) + vec2(1.0,-1.0) * site_location)/2).xyz;

	frag_pos = vec2(model_coord);

	show = SITEDISPLAY;

  // gl_InstanceID is a built-in input variable that tells
  //  which instance the vertex belongs to
  // In your project, you probably won't need it, but it's
  //  a nice thing to know that it exists :)
  // see GLSL specification for other built-in variables

  instance = gl_InstanceID;

  // just add 0 z-coordinate and 1 homogenous coordinate

  gl_Position = vec4(model_coord,0,1);
}
