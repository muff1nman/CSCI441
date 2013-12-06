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
#include "glviewer/gl/texture.h"
#include "glviewer/domain/triangle.h"

#include "glviewer/shader_locations.h"
#include "glviewer/texture_locations.h"

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

vec3 initial_mouse_point_on_sphere;


/* ----------------------------------------------------- */

bool animate = true;    // animate or not
float multiplier = 1.0; // controls rotation speed
int dcounter = 1;       // used to increment the frame counter (set to zero to freeze)

/* ----------------------------------------------------- */

// all buffer and program objects used 
Buffer* vertices = NULL;

VertexArray *va_square = NULL;
GLfloat square_vertices[] = {
  -1, -1,
  -1,  1,
   1, -1,
   1,  1
};
Buffer* sites = NULL;
Buffer* buf_square_vertices = NULL;

// DONT deallocate this one
VertexArray* current_vao = NULL;

Program* voronoi_program = NULL;
// DONT deallocate this one
Program* current_program = NULL;


/* ----------------------------------------------------- */

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
}

/* ----------------------------------------------------------------------------------*/
// Voronoi program
float max_window_distance = 1;
size_t number_of_sites;
//mat4 rotating;
float some_time;
float speed = 0.01f;
bool is_rotate;
RGBTexture2D* voronoi_texture;

int show_sites;

CoordBuffer sites_internal = NULL;
Buffer* site_buffer = NULL;

CoordBuffer colors_internal = NULL;
Buffer* color_buffer = NULL;

CoordBuffer angular_velocities_internal = NULL;
Buffer* angular_velocities_buffer = NULL;

void voronoi_setup_textures() {
	voronoi_texture->attach(1);
}

void increment_time() {
	some_time += speed;
	cout << "Current time is: " << some_time << endl;
}

void increase_number_of_sites() {
	size_t new_number_of_sites = number_of_sites * 2;
	if( new_number_of_sites  < MAXIMUM_NUMBER_SITES ) {
		number_of_sites = new_number_of_sites;
		cout << "Number of sites: " << number_of_sites << endl;
	}
}

//void update_rotation_matrix() {
	//rotating = rotate(mat4(),some_time,vec3(0,0,1));
	//cout << "rotating : " << rotating[0][0] << endl;
//}

void set_default_voronoi() {
	number_of_sites = DEFAULT_NUMBER_SITES;
	show_sites = false;
	//rotating = mat4();
	some_time = 0.0f;
	is_rotate = false;
}

void toggle_site_display() {
	show_sites = !show_sites;
	cout << "Show sites: " << show_sites << endl;
}

void toggle_rotate() {
	is_rotate = !is_rotate;
}

void program_voronoi_draw() {
	voronoi_texture->on();
	current_vao->sendToPipeline(GL_TRIANGLE_STRIP,0,4,number_of_sites);
  current_program->setUniform("SITEDISPLAY",&show_sites);
	current_program->setUniform("time",&some_time);
	if(is_rotate) {
		increment_time();
	}
}

void program_voronoi_finish_draw() {
	voronoi_texture->off();
}

GLfloat	randomfloat() {
	return rand() / (float) RAND_MAX;
}

GLfloat randfloat_in_box() {
	return 1.0f - 2.0f * randomfloat();
}

typedef GLfloat (*RandFun)();

CoordBuffer generate_random_data(size_t size, size_t DIM, RandFun func) {
	CoordBuffer coords = new Coord[size * DIM];
	for( size_t site = 0; site < size; ++site ) {
		for( size_t dim = 0; dim < DIM; ++dim) {
			coords[site*DIM + dim] = func();
			//cout << "rand num: " << coords[site*DIM + dim] << endl;
		}
	}

	return coords;
}

typedef Buffer* BufferPtr;

void generate_random_buffer( BufferPtr& buffer, CoordBuffer& internal, size_t size, size_t DIM, RandFun func = &randfloat_in_box) {
	if(buffer != NULL) {
		delete buffer;
	}
	if( internal != NULL ) {
		delete internal;
	}

	internal = generate_random_data(size, DIM, func);
	buffer = new Buffer(DIM, size, internal);

}

void set_voronoi_program() {
	set_pre_program();
	current_program = voronoi_program;
	current_vao = va_square;
	voronoi_setup_textures();

	// sites
	generate_random_buffer(site_buffer, sites_internal, MAXIMUM_NUMBER_SITES,2);
	current_vao->attachAttribute(2,site_buffer,1);

	// colors
	generate_random_buffer(color_buffer, colors_internal, MAXIMUM_NUMBER_SITES, 3, randomfloat);
	current_vao->attachAttribute(3,color_buffer,1);

	set_default_voronoi();

	// angular velocities
	generate_random_buffer(angular_velocities_buffer, angular_velocities_internal, MAXIMUM_NUMBER_SITES, 1);
	current_vao->attachAttribute(4,angular_velocities_buffer,1);

	set_post_program();
}

/* ----------------------------------------------------------------------------------*/

void set_default_program() {
	set_voronoi_program();
}

void program_draw() {
	program_voronoi_draw();
}

void program_finish_draw() {
	program_voronoi_finish_draw();
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


void setup_buffers() {
  va_square = new VertexArray;
  buf_square_vertices = new Buffer(2,4,square_vertices);
  va_square->attachAttribute(0,buf_square_vertices);
}

void setup_textures(const char* filename) {
	voronoi_texture = createRGBTexture2D(filename);
	voronoi_texture->linear();
	voronoi_texture->repeat();
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

	cout << "Creating the voronoi program..." << endl;
	voronoi_program = createProgram(VORONOI_VERTEX_SHADER, VORONOI_FRAGMENT_SHADER);
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

  current_program->on();

	// program specific stuffs
	program_draw();

  // turn the program off
  current_program->off();

	program_finish_draw();

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

					break;
				case GLUT_UP: 
					if (!mouse_button_down) 
						return;
					mouse_button_down = false;
					break;
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			switch( state ) {
				case GLUT_DOWN: 
					mouse_button_down = true;
					break;
				case GLUT_UP:   
					if (!mouse_button_down) 
						return;
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

  // refresh the image - in your code, rendering parameters may be changed in button_motion
  glutPostRedisplay();
}

/* --------------------------------------------- */

/* menu callback */

// you'll need to change this one as well...

static const int MENU_MORE_POINTS = 1;
static const int MENU_TOGGLE_HIDE_SITES = 2;
static const int MENU_RESET = 3;
static const int MENU_ANIMATE = 4;
static const int MENU_TOGGLE_COLOR = 5;

static const GLfloat ZOOM_FACTOR = 0.20f;

void menu ( int value )
{
	switch(value) {
		case MENU_MORE_POINTS:
			increase_number_of_sites();
			break;
		case MENU_TOGGLE_HIDE_SITES:
			toggle_site_display();
			break;
		case MENU_RESET:
			set_default_voronoi();
			break;
		case MENU_ANIMATE:
			toggle_rotate();
			break;
		case MENU_TOGGLE_COLOR:
		default:
			cout << "Unknown menu entry" << endl;
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

	//update_uniform_distance();

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
	glutAddMenuEntry("Spray More Points", MENU_MORE_POINTS);
	glutAddMenuEntry("Show/hide sites", MENU_TOGGLE_HIDE_SITES);
	glutAddMenuEntry("Reset", MENU_RESET);
	glutAddMenuEntry("Move points", MENU_ANIMATE);
	glutAddMenuEntry("Toggle Color", MENU_TOGGLE_COLOR);
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

	// setup random
	srand(16);

  // initialize programs and buffers
  setup_programs();
	setup_buffers();
	setup_textures(file_name.c_str());
	set_default_program();

  // Main loop: keep processing events.
  // This is actually an indefinite loop - you can only exit it using 
  // brutal means like the exit() function in one of the event handlers.
  // In this code, the exit point is in the keyboard event handler.
  glutMainLoop();

  return 0;
}

