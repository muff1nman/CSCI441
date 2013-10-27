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

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>

#include "glviewer/parse/parse.h"
#include "glviewer/gl/program.h"
#include "glviewer/gl/vertexarray.h"
#include "glviewer/gl/shader.h"

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

size_t num_vertices;

vec3 min_bound;
vec3 max_bound;

vec3 initial_mouse_point_on_sphere;

mat4 global_rotation;
mat4 current_rotation;

/* ----------------------------------------------------- */

// all buffer and program objects used 

VertexArray *va_square = NULL;
Buffer *buf_square_vertices = NULL;
IndexBuffer *ix_square = NULL;

VertexArray *va_cube = NULL;
Buffer *buf_cube_vertices = NULL;
Buffer *buf_cube_faceId = NULL;

Program *square_program = NULL;
Program *cube_program = NULL;

/* ----------------------------------------------------- */

void setup_globals() {
	// no intial rotation
	global_rotation = mat4();
}

void setup_buffers(const char* input_file) {
	//Environment e = parse(input_file);
	VectorStream tris = to_vec_stream( input_file );

	num_vertices = tris.size();

	CoordBuffer tri_buffer = new Coord[3*num_vertices];
	for( size_t i = 0; i < tris.size(); ++i ) {

		// set the min and max first time around
		if( i == 0 ) {
			min_bound = tris.at(i);
			max_bound = tris.at(i);
		}

		// check to set max or min
		GLfloat cur_x = tris.at(i).x;
		GLfloat cur_y = tris.at(i).y;
		GLfloat cur_z = tris.at(i).z;

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
		
		//cout << "(" << tris.at(i).x << "," <<tris.at(i).y  << "," << tris.at(i).z << ")" << endl;
		tri_buffer[ 3*i+0 ] = cur_x;
		tri_buffer[ 3*i+1 ] = cur_y;
		tri_buffer[ 3*i+2 ] = cur_z;
	}

  // Fhe first argument to the Buffer constructor is the number of 
  // components per vertex (basically, numbers per vertex)
  // For square, vertices are 2D - they have 2 coordinates; hence 
  //  the number of components is 2, and there are 4 vertices.
  // The last argument is a pointer to the actual vertex data.
  buf_square_vertices = new Buffer(3,tris.size(),tri_buffer);

  // construct the square VA
  va_square = new VertexArray;

  // vertices are attribute #0
  va_square->attachAttribute(0,buf_square_vertices);

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

  cout << "Creating the cube program..." << endl;
  cube_program = createProgram("lib/shaders/vsh_cube.glsl","lib/shaders/fsh_cube.glsl");
  cout << "Creating the square program..." << endl;
  square_program = createProgram("lib/shaders/vertex.glsl","lib/shaders/fragment.glsl");
}

/* ----------------------------------------------------- */

bool animate = true;    // animate or not
float multiplier = 1.0; // controls rotation speed
int dcounter = 1;       // used to increment the frame counter (set to zero to freeze)

/* ----------------------------------------------------- */

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
  glDisable(GL_CULL_FACE);

  // want to use depth test to get visibility right
  glEnable(GL_DEPTH_TEST);

	// pick an alpha
	GLfloat alpha = 14.0f;

	GLfloat d = 1 / tan(alpha / 180.0 * M_PI / 2.0f);

  // Compute projection matrix; perspective() is a glm function
  // Arguments: field of view in DEGREES(!), aspect ratio (1 if square window), distance to front and back clipping plane
  // Camera is located at the origin and points along -Z direction
  //mat4 P = perspective(float(1.0+0.5*sin(counter/100.0))*1.0f,1.0f,18.0f,22.0f);
  mat4 P = perspective(alpha,1.0f, d - 1.0f, d+ 3.0f);

	// calculate what to transform by to get to zero zero
	vec3 trans( 
			- (max_bound.x + min_bound.x) / 2.0f,
			- (max_bound.y + min_bound.y) / 2.0f,
			- (max_bound.z + min_bound.z) / 2.0f);

	// and form into a matrix
	mat4 T = translate(mat4(), trans);

	// calculatre the scalar to scale by
	GLfloat sc = 2.0f / std::max( max_bound.x - min_bound.x, 
			std::max( max_bound.y - min_bound.y, max_bound.z - min_bound.z ));

	// put it into matrix form
	mat4 S = scale( mat4(), vec3(sc,sc,sc) );

	mat4 to_view_t = translate(mat4(), vec3(0.0f, 0.0f, -1.0f - d));

  // this is technically a part of the modelview matrix - it rotates around the axis [0,0,20]
  //  and then moves "forward", i.e. along -Z, by 20 units
  mat4 MV = to_view_t * current_rotation * global_rotation * S * T;

  // send matrices P and MV into uniform variables of the program used to render square
  // &P[0][0] is the pointer to the entries of matrix P, same for MV
  // Note that it's a coincidence that uniform names are the same as CPU code variable names 
  //    - they don't have to be the same
  square_program->setUniform("P",&P[0][0]);
  square_program->setUniform("MV",&MV[0][0]);

  // turn on the square program...
  square_program->on();

  // Send vertices 0...5 to pipeline; use the index buffer ix_square.
  // Recall that ix_square contains 0 1 2 0 2 3, which means that 
  // vertices with data at indices 0 1 2 0 2 3 in the buffers attached to the 
  // vertex array are going to be generated.
  // The first argument instructs the pipeline how to set up triangles; GL_TRIANGLES=triangle soup
	va_square->sendToPipeline(GL_TRIANGLES,0, num_vertices );

  // turn the program off
  square_program->off();

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

	GLfloat x_sq_y_sq = pow(x,2) + pow(y,2);

	if( 1.0f - x_sq_y_sq  >= 0.0f ) {
		return vec3( x, y, pow(1.0f - x_sq_y_sq, 0.5f));
	} 
	// outside of circle --- project onto it
	else {
		return vec3( x / pow( x_sq_y_sq, 0.5f ), y / pow( x_sq_y_sq, 0.5f ), 0);
	}
}

mat4 create_rotation(vec3 initial, vec3 final) {
	// make sure to return identiy if these are parallel
	GLfloat rangle = angle(initial, final );
	if( rangle != 0.0f ) {
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

static const int MENU_SLOWER = 1;
static const int MENU_FASTER = 2;
static const int MENU_STOP_RUN = 3;

void menu ( int value )
{
  static GLfloat stored_multiplier = 0;
  static int stored_dcounter;

  switch(value)
    {
    case MENU_SLOWER:
      multiplier *= 0.6;
      break;
    case MENU_FASTER:
      multiplier *= 1.4;
      break;
    case MENU_STOP_RUN:
      animate = !animate;
      
      // this is to make sure that when animation is off, things don't move even if
      //  glutPostRedisplay comes up somewhere (e.g. in a mouse event)
      swap(dcounter,stored_dcounter);
      swap(multiplier,stored_multiplier);

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
  glutAddMenuEntry("slower",MENU_SLOWER);
  glutAddMenuEntry("faster",MENU_FASTER);
  glutAddMenuEntry("stop/run",MENU_STOP_RUN);
  glutSetMenu(menuID);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  return id;
}

/* --------------------------------------------- */
/* --------------------------------------------- */
/* --------------------------------------------- */

GLint main(GLint argc, char **argv)
{
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
  setup_buffers("../input.t");
	setup_globals();

  // Main loop: keep processing events.
  // This is actually an indefinite loop - you can only exit it using 
  // brutal means like the exit() function in one of the event handlers.
  // In this code, the exit point is in the keyboard event handler.
  glutMainLoop();

  return 0;
}


