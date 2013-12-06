#version 420

/* --------------- INPUT VARIABLES -------------- */
/* In a fragment shader, attributes sent out with */
/* processed vertices in the vertex shader        */
/* and interpolated on the rasterization stage    */
/* ---------------------------------------------- */

flat in vec3 col;
flat in vec2 site_location;
flat in float maximum_distance;

/* ----------- OUTPUT VARIABLES ----------------- */
/* For `simple' rendering we do here, there is    */ 
/* just one: RGB value for the fragment           */
/* ---------------------------------------------- */

out vec3 fragcolor;

/* ---------------------------------------------- */
/* ----------- MAIN FUNCTION -------------------- */
/* goal: compute the color of the fragment        */
/*  [put it into the only output variable]        */
/* ---------------------------------------------- */

void main() {

  // alter depth depending on where you are (param) and 
  // dir (which is an instanced attribute value passed here
  // from the vertex shader)

  //gl_FragDepth = 0.5*(1+sin(10/(0.3+abs(dot(param,dir)))));
	gl_FragDepth = distance(site_location, gl_FragCoord.xy) / maximum_distance;

  // col is also an instanced attribute - color each instance
  // using a constant color

  fragcolor = col;
}
