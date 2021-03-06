/*
 * glviewer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#ifdef WITH_BOOST
#ifndef OLD_BOOST
#include <boost/filesystem.hpp>
#else
#include <boost/filesystem/operations.hpp>
#endif
#endif

#include "glviewer/config.h"
#include "glviewer/parse/parse.h"
#include "glviewer/gl/program.h"
#include "glviewer/gl/vertexarray.h"
#include "glviewer/gl/shader.h"
#include "glviewer/domain/triangle.h"

#include "shader_locations.h"

using namespace gl_CSCI441;
using namespace std;
using namespace glm;

/* --------------------------------------------- */
/* ----- GLOBAL VARIABLES  --------------------- */
/* --------------------------------------------- */

static const GLint VPD_DEFAULT = 800;
static GLint wid;               /* GLUT window id; value asigned in main() and should stay constant */
static GLint vpw = VPD_DEFAULT; /* viewport dimensions; changed when window is resized (resize callback) */
static GLint vph = VPD_DEFAULT;

static const size_t THIRD_DIM = 3;

size_t num_vertices;

vec3 min_bound;
vec3 max_bound;

vec3 initial_mouse_point_on_sphere;

mat4 global_rotation;
mat4 current_rotation;

// pick an alpha
GLfloat alpha = 14.0f;
GLfloat d;

glm::mat4 Perspective;
glm::mat4 Translate;
glm::mat4 Scale;
glm::mat4 to_view_t;


/* ----------------------------------------------------- */

bool animate = true;    // animate or not
float multiplier = 1.0; // controls rotation speed
int dcounter = 1;       // used to increment the frame counter (set to zero to freeze)

/* ----------------------------------------------------- */
/* ----------------------------------------------------- */

// all buffer and program objects used 
Buffer* vertices = NULL;

VertexArray* flat_vao = NULL;
Buffer* flat_normals = NULL;

VertexArray* gphong_vao = NULL;
Buffer* gphong_normals = NULL;

// DONT deallocate this one
VertexArray* current_vao = NULL;

Program* flat_program = NULL;
Program* gouraud_program = NULL;
Program* phong_program = NULL;
// DONT deallocate this one
Program* current_program = NULL;

/* ----------------------------------------------------- */
static vec3 light_source(50.0f,10.0f,100.0f);
static vec3 kdiff(0.4,0.2,0.6);
static vec3 kambient(0.1,0.1,0.1);
static vec3 kspec(0.2,0.7,0.5);
static GLfloat nspec = 100;
static vec3 none(0.0, 0.0, 0.0);

void turn_on_diffuse() {
	current_program->setUniform("KDIFF",&kdiff.x);
}

void turn_off_diffuse() {
	current_program->setUniform("KDIFF",&none.x);
}

void turn_on_specular() {
	current_program->setUniform("KSPEC", &kspec.x);
}

void turn_off_specular() {
	current_program->setUniform("KSPEC", &none.x);
}

void toggle_specular() {
	static bool on = true;
	if( on ) {
		turn_off_specular();
	} else {
		turn_on_specular();
	}
	on = !on;
}

void toggle_diffuse() {
	static bool on = true;
	if( on ) {
		turn_off_diffuse();
	} else {
		turn_on_diffuse();
	}
	on = !on;
}

void setup_globals() {
	// no intial rotation
	global_rotation = mat4();

}

void setup_const_uniforms() {
	// set the light source location
  current_program->setUniform("LV",&light_source.x);

	// set material properties
	turn_on_diffuse();
	turn_on_specular();
	current_program->setUniform("KAMBIENT",&kambient.x);
	current_program->setUniform("NSPEC", &nspec);

}

void set_pre_program() {
	current_program->off();

	// make sure all the stuff is drawn
	glFlush();

	// this exchanges the invisible back buffer with the visible buffer to 
	//  avoid refresh artifacts
	glutSwapBuffers();

	// Request another call to draw() in the "animation" mode.
	// Note that in the viewer you'll be implementing you may not need this - 
	//  all you have to do is to make sure the image is redrawn when rendering parameters change,
	//  e.g. as a result of mouse events.
	if (animate) 
		glutPostRedisplay();
}

void set_post_program() {
	setup_const_uniforms();
}

void set_phong_program() {
	set_pre_program();
	current_program = phong_program;
	current_vao = gphong_vao;
	set_post_program();
}

void set_gouraud_program() {
	set_pre_program();
	current_program = gouraud_program;
	current_vao = gphong_vao;
	set_post_program();
}

void set_flat_program() {
	set_pre_program();
	current_program = flat_program;
	current_vao = flat_vao;
	set_post_program();
}

void set_default_program() {
	set_flat_program();
}

// just a handy print helper
void print_vec( const vec3& vec ) {
	cout << "(" << vec.x << "," << vec.y << "," << vec.z << ")" << endl;
}

void check_valid_vecs_size( const VectorStream& vecs ) {
	if( vecs.size() % VERTS_PER_TRIANGLE != 0 ) {
		cerr << "Could not evenly divide vector stream into triangles" << endl;
		exit(1);
	}
}

vec3 compute_normal_at_vec_index( const VectorStream& vecs, size_t i ) {
	// compute the normal for the given triangle
	vec3 ab = (vecs.at(3*i + 1) - vecs.at(3*i));
	vec3 ac = (vecs.at(3*i + 2) - vecs.at(3*i));
	vec3 norm_out = cross(ab, ac);
	// really we want to use zero but we account for floating point shit
	if( length(norm_out) < 0.001 ) {
		return norm_out;
	}
	return normalize(norm_out);
}

// Creates a list of vec3 for normals.  It will output 3 vec3 for each triangle
// in the given vector stream
VectorStream create_flat_normal_stream( const VectorStream& vecs ) {
	check_valid_vecs_size(vecs);
	VectorStream normals;
	//cout << "Normals:" << endl;
	//  Iterate over every third vec3 so that we can treat them as groups of
	//  triangles
	for( size_t i = 0; i < (vecs.size() / VERTS_PER_TRIANGLE); ++i ) {
		vec3 norm_out = compute_normal_at_vec_index(vecs, i);
		// push normals back three times
		for( size_t i = 0; i < VERTS_PER_TRIANGLE; ++i ) {
			///print_vec(norm_out);
			normals.push_back(norm_out);
		}
	}

	//cout << "End normals" << endl;
	return normals;
}

bool compare_vecs( const glm::vec3& a, const glm::vec3& b ) {
	if( a.x != b.x ) {
		return a.x < b.x;
	} else if( a.y != b.y ) {
		return a.y < b.y;
	} else {
		return a.z < b.z;
	}
}

VectorStream create_gphong_normal_stream( const VectorStream& vecs ) {
	check_valid_vecs_size(vecs);
	VectorStream normals;

	// create a mapping of vertices to normals and populate
	typedef bool (*Vec3Compare)(const glm::vec3&, const glm::vec3&);
	typedef map< glm::vec3, glm::vec3, Vec3Compare > NormMap;
	NormMap normmap(compare_vecs);
	for( size_t i = 0; i < (vecs.size() / VERTS_PER_TRIANGLE); ++i ) {
		vec3 norm_to_add = compute_normal_at_vec_index(vecs, i);
		// add normal to map
		for( size_t j = 0; j < VERTS_PER_TRIANGLE; ++j ) {
			vec3 current_vertex = vecs.at(VERTS_PER_TRIANGLE*i + j);
			// we dont need to worry about initializing the vecs because the map does
			// that for us
			normmap[current_vertex] += norm_to_add;
		}
	}

	// now iterate again and pull out the normals from the map
	for( size_t i = 0; i < vecs.size(); ++i ) {

		// TODO remove checks
		NormMap::iterator normal_there = normmap.find( vecs.at(i) );

		// TODO normalize unneeded because it is done in vertex shader?
		normals.push_back( normalize(normmap[vecs.at(i)]) );
	}	

	return normals;

}

Buffer* create_triangle_buffer( const VectorStream& verts ) {
	// Loop over all the vertex vec's and output three times to the coordinate
	// buffer, once for each coordinate in a vec3.  Also find the max and min
	// bounds while we're at it
	CoordBuffer tri_buffer = new Coord[3*verts.size()];
	for( size_t i = 0; i < verts.size(); ++i ) {
		//print_vec( verts.at(i) );

		// set the min and max first time around
		if( i == 0 ) {
			min_bound = verts.at(i);
			max_bound = verts.at(i);
		}

		// check to set max or min
		GLfloat cur_x = verts.at(i).x;
		GLfloat cur_y = verts.at(i).y;
		GLfloat cur_z = verts.at(i).z;

		if( cur_x > max_bound.x ) {
			max_bound.x = cur_x;
		}
		if( cur_x < min_bound.x ) {
			min_bound.x = cur_x;
		}
		if( cur_y > max_bound.y ) {
			max_bound.y = cur_y;
		}
		if( cur_y < min_bound.y ) {
			min_bound.y = cur_y;
		}
		if( cur_z > max_bound.z ) {
			max_bound.z = cur_z;
		}
		if( cur_z < min_bound.z ) {
			min_bound.z = cur_z;
		}
		
		//cout << "(" << verts.at(i).x << "," <<verts.at(i).y  << "," << verts.at(i).z << ")" << endl;

		// Set the actual buffer
		tri_buffer[ 3*i+0 ] = cur_x;
		tri_buffer[ 3*i+1 ] = cur_y;
		tri_buffer[ 3*i+2 ] = cur_z;
	}

	//cout << "Max : " << to_string( max_bound ) << endl;
	//cout << "Min : " << to_string( min_bound ) << endl;

	//ostream_iterator<GLfloat> out_it(cout,", ");
	//copy(tri_buffer, tri_buffer + 3 * num_vertices, out_it);
  return new Buffer(3,verts.size(),tri_buffer);

}

Buffer* create_normal_buffer( const VectorStream& norms ) {
	// Loop over all normal vec3's and output three times to the coordinate
	// buffer, once for each coordinate in a vec3.
	CoordBuffer norm_buffer = new Coord[THIRD_DIM*norms.size()];
	for( size_t i = 0; i < norms.size(); ++i ) {
		vec3 cur = norms.at(i);
		norm_buffer[ THIRD_DIM*i+0 ] = cur.x;
		norm_buffer[ THIRD_DIM*i+1 ] = cur.y;
		norm_buffer[ THIRD_DIM*i+2 ] = cur.z;
	}
	return new Buffer(THIRD_DIM,norms.size(),norm_buffer);

}

void setup_buffers(const char* input_file) {
	// get a stream of vertices 
	VectorStream verts = to_vec_stream( input_file );
	
	// create a stream of normals for phong/gouraud shading
	//VectorStream gphong_norms = create_gphong_normal_stream( verts );

	// assuming flat_norms.size() == verts.size() == gphong_norms.size()
	num_vertices = verts.size();

	vertices = create_triangle_buffer( verts );

  // construct the flat shading VA
  flat_vao = new VertexArray;
	// create a stream of normals for flat shading from the vertice stream
	flat_normals = create_normal_buffer(create_flat_normal_stream( verts ) );
  flat_vao->attachAttribute(0,vertices);
	flat_vao->attachAttribute(1,flat_normals);

	// construct the vaos for both phong and gouraud shading models
	gphong_vao = new VertexArray;
	gphong_normals = create_normal_buffer(create_gphong_normal_stream( verts ));
	gphong_vao->attachAttribute(0,vertices);
	gphong_vao->attachAttribute(1,gphong_normals);

}

/* ----------------------------------------------------- */

void setup_programs()
{
  // There is a handy function createProgram implemented in program.c,
  // which takes two file names (first=vertex shader source, 
  // second=fragment shader source) and creates a program from them.
  // The return value is of type Program*.
  // Note that we print a messahe before calling it because it
  // prints out the GLSL compiler and linker messages - this is a way to know
  // which of your shaders/programs has a problem.

  cout << "Creating the flat program..." << endl;
  flat_program = createProgram(FLAT_VERTEX_SHADER,FLAT_FRAGMENT_SHADER);
	cout << "Creating the gouraud program..." << endl;
	gouraud_program = createProgram(GOURAUD_VERTEX_SHADER, GOURAUD_FRAGMENT_SHADER);
	cout << "Creating the phong program..." << endl;
	phong_program = createProgram(PHONG_VERTEX_SHADER, PHONG_FRAGMENT_SHADER);
}

void update_d() {
	d = 1.0f / tan(alpha / 180.0 * M_PI / 2.0f);
}

void update_perspective() {
  // Compute projection matrix; perspective() is a glm function
  // Arguments: field of view in DEGREES(!), aspect ratio (1 if square window), distance to front and back clipping plane
  // Camera is located at the origin and points along -Z direction
  Perspective = perspective(alpha,1.0f, d - 1.0f, d+ 3.0f);
}

void setup_intial_transforms() {

	update_d();

	update_perspective();

	// calculate what to transform by to get to zero zero
	vec3 trans( 
			- (max_bound.x + min_bound.x) / 2.0f,
			- (max_bound.y + min_bound.y) / 2.0f,
			- (max_bound.z + min_bound.z) / 2.0f);
	//cout << "translate is: " << to_string(trans) << endl;

	// and form into a matrix
	Translate = translate(mat4(), trans);

	// calculatre the scalar to scale by
	GLfloat sc = 2.0f / std::max( max_bound.x - min_bound.x, 
			std::max( max_bound.y - min_bound.y, max_bound.z - min_bound.z ));

	//cout << "Scale is: " << sc << endl;

	// put it into matrix form
	Scale = scale( mat4(), vec3(sc,sc,sc) );

	// calculate the translate required to get into camera fov
	to_view_t = translate(mat4(), vec3(0.0f, 0.0f, -1.0f - d));

	//cout << "What is translate? " << to_string( to_view_t) << endl;


}


void draw()
{
  // ensure we're drawing to the correct GLUT window 
  glutSetWindow(wid);

  // frame counter for zoom animation
  static int counter = 0;
  counter += dcounter;

  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // want to disable culling for square - it's not a watertight surface
  //  what would happen if you enable it?
	//glCullFace(GL_FRONT);
  glEnable(GL_CULL_FACE);

	glFrontFace(GL_CW);

  // want to use depth test to get visibility right
  glEnable(GL_DEPTH_TEST);


	// join all the matrices together for the complete MV matrix
  mat4 MV = to_view_t * current_rotation * global_rotation * Scale * Translate;

	// compute the normal matrix from the MV matrix
	//mat4 NMV = transpose(inverse(MV));
	//mat4 NMV = current_rotation * global_rotation;
	mat3 NMV = mat3(MV);

  // send matrices P and MV into uniform variables of the program used to render square
  // &P[0][0] is the pointer to the entries of matrix P, same for MV
  // Note that it's a coincidence that uniform names are the same as CPU code variable names 
  //    - they don't have to be the same
  current_program->setUniform("P",&Perspective[0][0]);
  current_program->setUniform("MV",&MV[0][0]);
	current_program->setUniform("NMV",&NMV[0][0]);

  // turn on the square program...
  current_program->on();

  // Send vertices 0...5 to pipeline; use the index buffer ix_square.
  // Recall that ix_square contains 0 1 2 0 2 3, which means that 
  // vertices with data at indices 0 1 2 0 2 3 in the buffers attached to the 
  // vertex array are going to be generated.
  // The first argument instructs the pipeline how to set up triangles; GL_TRIANGLES=triangle soup
	current_vao->sendToPipeline(GL_TRIANGLES,0, num_vertices );

  // turn the program off
  current_program->off();

  // make sure all the stuff is drawn
  glFlush();

  // this exchanges the invisible back buffer with the visible buffer to 
  //  avoid refresh artifacts
  glutSwapBuffers();

  // Request another call to draw() in the "animation" mode.
  // Note that in the viewer you'll be implementing you may not need this - 
  //  all you have to do is to make sure the image is redrawn when rendering parameters change,
  //  e.g. as a result of mouse events.
  if (animate) 
    glutPostRedisplay();
}

vec3 calculate_point_on_sphere( GLint mx, GLint my ) {

	// scale to -1 to 1 range
	GLfloat x = 2.0f * mx / (vpw - 1.0f) - 1.0f;
	GLfloat y = -(2.0f * my  / (vph - 1.0f) - 1.0f);

	// compute x^2 + y^2
	GLfloat x_sq_y_sq = pow(x,2) + pow(y,2);

	// make sure that the square root wont be negative
	if( 1.0f - x_sq_y_sq  >= 0.0f ) {
		// inside the sphere
		return vec3( x, y, pow(1.0f - x_sq_y_sq, 0.5f));
	} 
	// outside of sphere --- project onto it
	else {
		return vec3( x / pow( x_sq_y_sq, 0.5f ), y / pow( x_sq_y_sq, 0.5f ), 0);
	}
}

mat4 create_rotation(vec3 initial, vec3 final) {
	// make sure to return identiy if these are parallel
	GLfloat rangle = angle(initial, final );
	// we use 0.1 here because if we test strictly against 0.0 we get divide by
	// zero errors very occaisionaly
	if( rangle > 0.1f ) {
		return rotate( mat4(), rangle, cross(initial, final));
	}
	return mat4();
}

/* ----------------------------------------------------- */

/* --------------------------------------------- */
/* --- INTERACTION ----------------------------- */
/* --------------------------------------------- */

/* handle mouse events */

// you'll need to replace code that prints out messages with trackball code 
// in the two functions below

// some versions of glut like to generate a mouse button up event
//  after the user selects a menu item
// this variable will allow us to distinguish these spurious events
//  and the actual mouse button up events...
bool mouse_button_down = false;

void mouse_button(GLint btn, GLint state, GLint mx, GLint my)
{
  switch( btn ) {
		case GLUT_LEFT_BUTTON:
			switch( state ) {
				case GLUT_DOWN: 
					cout << "Left mouse button pressed @ " << mx << " " << my << endl;
					mouse_button_down = true;

					// save for rotation
					cout << "(" << mx << "," << my << ") saved for intial rotation point" << endl;
					initial_mouse_point_on_sphere = calculate_point_on_sphere( mx, my );

					break;
				case GLUT_UP: 
					if (!mouse_button_down) 
						return;
					cout << "Left mouse button went up @ " << mx << " " << my << endl;

					// rotation added to global rotation
					global_rotation = current_rotation * global_rotation;
					// clear current_rotation
					current_rotation = mat4();

					mouse_button_down = false;
					break;
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			switch( state ) {
				case GLUT_DOWN: 
					cout << "Middle mouse button pressed @ " << mx << " " << my << endl;
					mouse_button_down = true;
					break;
				case GLUT_UP:   
					if (!mouse_button_down) 
						return;
					cout << "Middle mouse button went up@ " << mx << " " << my << endl;
					mouse_button_down = false;
					break;
			}
			break;
		default:
			return;  // ignore anything else, e.g. right button pressed
	}

	// refresh the image - in your code, rendering parameters may be changed in mouse_button
	glutPostRedisplay();
}

GLvoid button_motion(GLint mx, GLint my)
{
  if (!mouse_button_down)
    return;   // mouse button not down - ignore!

  cout << "Mouse movement with some button down @ " << mx << " " << my << endl;

	// rotate image
	current_rotation = create_rotation( initial_mouse_point_on_sphere, calculate_point_on_sphere(mx, my));

  // refresh the image - in your code, rendering parameters may be changed in button_motion
  glutPostRedisplay();
}

/* --------------------------------------------- */

/* menu callback */

// you'll need to change this one as well...

static const int MENU_FLAT = 1;
static const int MENU_GOURAUD = 2;
static const int MENU_PHONG = 3;
static const int MENU_SPECULAR = 4;
static const int MENU_DIFFUSE = 5;
static const int MENU_ZOOM_IN = 6;
static const int MENU_ZOOM_OUT = 7;

static const GLfloat ZOOM_FACTOR = 0.20f;

void increase_alpha() {
	alpha *=  (1 + ZOOM_FACTOR);
	update_perspective();
}

void decrease_alpha() {
	alpha *= (1 - ZOOM_FACTOR);
	update_perspective();
}

void menu ( int value )
{
  switch(value)
    {
    case MENU_FLAT:
			set_flat_program();
      break;
    case MENU_GOURAUD:
			set_gouraud_program();
      break;
    case MENU_PHONG:
			set_phong_program();
      break;
    case MENU_SPECULAR:
			toggle_specular();
      break;
    case MENU_DIFFUSE:
			toggle_diffuse();
      break;
    case MENU_ZOOM_IN:
			decrease_alpha();
      break;
    case MENU_ZOOM_OUT:
			increase_alpha();
      break;
    }

  // and again, in case any rendering paramters changed, redraw
  glutPostRedisplay();
}

/* --------------------------------------------- */

/* handle keyboard events; here, just exit if ESC is hit */

void keyboard(GLubyte key, GLint x, GLint y)
{
  switch(key) {
  case 27:  /* ESC */
    
    // clean up and exit
    // you may remove these deletes and let the OS do the work
		// TODO

    exit(0);

  default:  break;
  }
}

/* --------------------------------------------- */

/* handle resizing the glut window */

GLvoid reshape(GLint sizex, GLint sizey)
{
  glutSetWindow(wid);

  // keep the viewport square...
  vpw = sizex < sizey ? sizex : sizey;
  vph = vpw;

  glViewport(0, 0, vpw, vph);
  glutReshapeWindow(vpw, vph);

  glutPostRedisplay();
}

/* --------------------------------------------- */
/* -------- SET UP GLUT  ----------------------- */
/* --------------------------------------------- */

// initialize glut, callbacks etc.

GLint init_glut(GLint *argc, char **argv)
{
  GLint id;

  glutInit(argc,argv);

  /* size and placement hints to the window system */
  glutInitWindowSize(vpw, vph);
  glutInitWindowPosition(10,10);

  /* double buffered, RGB color mode */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  /* create a GLUT window (not drawn until glutMainLoop() is entered) */
  id = glutCreateWindow("MACS441 OpenGL Sample code");    

  /* register callbacks */

  /* window size changes */
  glutReshapeFunc(reshape);

  /* keypress handling when the current window has input focus */
  glutKeyboardFunc(keyboard);

  /* mouse event handling */
  glutMouseFunc(mouse_button);           /* button press/release        */
  glutMotionFunc(button_motion);         /* mouse motion w/ button down */

  /* window obscured/revealed event handler */
  glutVisibilityFunc(NULL);

  /* handling of keyboard SHIFT, ALT, CTRL keys */
  glutSpecialFunc(NULL);

  /* what to do when mouse cursor enters/exits the current window */
  glutEntryFunc(NULL);

  /* what to do on each display loop iteration */
  glutDisplayFunc(draw);

  /* create menu */
  // you'll need to change this to build your menu
  GLint menuID = glutCreateMenu(menu);
  glutAddMenuEntry("Flat shading",MENU_FLAT);
  glutAddMenuEntry("Gouraud shading",MENU_GOURAUD);
  glutAddMenuEntry("Phong shading",MENU_PHONG);
  glutAddMenuEntry("Enable/Disable specular",MENU_SPECULAR);
  glutAddMenuEntry("Enable/Disable diffuse",MENU_DIFFUSE);
  glutAddMenuEntry("Zoom In",MENU_ZOOM_IN);
  glutAddMenuEntry("Zoom Out",MENU_ZOOM_OUT);
  glutSetMenu(menuID);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  return id;
}

/* --------------------------------------------- */
/* --------------------------------------------- */
/* --------------------------------------------- */

GLint main(GLint argc, char **argv) {

	string file_name = DEFAULT_INPUT_FILE;
	if( argc < 2 ) {
		cout << "Using default file name: " << file_name << endl;
	} else {
		file_name = string(argv[1]);
	}

#ifdef WITH_BOOST
	if( !boost::filesystem::exists( file_name ) ) {
		cout << "Input file not found" << endl;
		return 1;
	}
#else
	cout << "Make sure that this file [" << file_name << "] is reachable" << endl;
#endif

  /* initialize GLUT: register callbacks, etc */
  wid = init_glut(&argc, argv);

  // initialize glew and check for OpenGL 4.2 support
  glewInit();
  if (glewIsSupported("GL_VERSION_4_0"))
    cout << "Ready for OpenGL 4.0" << endl;
  else 
    {
      cout << "OpenGL 4.0 not supported" << endl;;
      return 1;
    }

  // initialize programs and buffers
  setup_programs();
	setup_buffers(file_name.c_str());
	setup_intial_transforms();
	setup_globals();
	set_default_program();

  // Main loop: keep processing events.
  // This is actually an indefinite loop - you can only exit it using 
  // brutal means like the exit() function in one of the event handlers.
  // In this code, the exit point is in the keyboard event handler.
  glutMainLoop();

  return 0;
}


