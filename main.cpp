#if defined(__APPLE_CC__)
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#include<GLUT/glut.h>
#elif defined(WIN32)
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdint.h>
#endif

#include<iostream>
#include<stdlib.h>
#include<time.h>

//new headers and functions
#include "p2.h"
bool invert_pose( float *m );
void reset();
unsigned int mode = ABS_LOOK_AT;
float move_speed = DEFAULT_SPEED;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Global State Variables ///////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// time increment between calls to idle() in ms,
// currently set to 30 FPS
float dt = 1000.0f*1.0f/30.0f;

// flag to indicate that we should clean up and exit
bool quit = false;

// window handles for mother ship and scout ship
int mother_window, scout_window;

// display width and height
int disp_width=512, disp_height=512;

// ships
ship mother;
ship scout;


bool paused = 0;
bool scout_ctrl = false;

// mouse
bool left_pressed = 0;
int prev_x, prev_y;

// Solar system
float obj_spin_rots[NUM_SPHERE] = {0};
float obj_orbit_rots[NUM_SPHERE] = {0};
GLUquadricObj* spheres[NUM_SPHERE] = {0};
GLUquadricObj* disks[NUM_DISKS] = {0};


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Initialization/Setup and Teardown ////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// set up opengl state, allocate objects, etc.  This gets called
// ONCE PER WINDOW, so don't allocate your objects twice!
void init(){
	/////////////////////////////////////////////////////////////
	/// TODO: Put your initialization code here! ////////////////
	/////////////////////////////////////////////////////////////
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glViewport( 0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_NORMALIZE );

	// lighting stuff
	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
	GLfloat specular[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat position0[] = {1.0, 1.0, 1.0, 0.0};
	glLightfv( GL_LIGHT0, GL_POSITION, position0 );
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
	GLfloat position1[] = {-1.0, -1.0, -1.0, 0.0};
	glLightfv( GL_LIGHT1, GL_POSITION, position1 );
	glLightfv( GL_LIGHT1, GL_AMBIENT, ambient );
	glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT1, GL_SPECULAR, specular );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );
	glEnable( GL_COLOR_MATERIAL );

	// create solar system geometric objects
	reset();
	for (int i = 0; i <NUM_SPHERE; i++) {
		spheres[i] = gluNewQuadric();
		if(spheres[i] == NULL) {
			exit(1);
		}
	}
	for (int i = 0; i <NUM_DISKS; i++) {
		disks[i] = gluNewQuadric();
		if(disks[i] == NULL) {
			exit(1);
		}
	}
	// randomize planet locations
	srand(time(NULL));
	for (int i = 0; i <NUM_SPHERE; i++) {
		obj_orbit_rots[i] = rand() % 360;
	}

}

void debug_matrix(GLfloat* m) {
	for (int i =0;i<16;i++) {
		printf("%f ", m[i]);
		if (i % 4 == 1)
			printf("\n");
	}
}

// free any allocated objects and return
void cleanup(){
	/////////////////////////////////////////////////////////////
	/// TODO: Put your teardown code here! //////////////////////
	/////////////////////////////////////////////////////////////
	for (int i = 0; i <NUM_SPHERE; i++) {
		delete spheres[i];
	}
	for (int i = 0; i <NUM_DISKS; i++) {
		delete disks[i];
	}

}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Callback Stubs ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// mouse callback
void mouse_callback(int button, int state, int x, int y) {

	//printf("button:%d, state:%d\n", button, state);
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN ) { 
			left_pressed = true;
			prev_x = x;
			prev_y = y;
		}
		else 
			left_pressed = false;
		break;
	default:
		break;
	}
}

// motion callback
void motion_callback(int x, int y) {
	int current_window;
	int x_move, y_move;
	float gaze_x, gaze_y, gaze_z;

	// retrieve the currently active window
	current_window = glutGetWindow();

	if (left_pressed) {
		x_move = x - prev_x;
		y_move = y -prev_y;
		prev_x = x;
		prev_y = y;
	}
	glPushMatrix();

}

// window resize callback
void resize_callback( int width, int height ){    
	/////////////////////////////////////////////////////////////
	/// TODO: Put your resize code here! ////////////////////////
	/////////////////////////////////////////////////////////////
	glMatrixMode (GL_MODELVIEW);		  /* back to modelview matrix */
	glViewport (0, 0, width, height);      /* define the viewport */
}

void reset() {
	mother.x = MOTHER_INIT_X;
	mother.y = MOTHER_INIT_Y;
	mother.z = MOTHER_INIT_Z;
	mother.lookat_x = 0;
	mother.lookat_y = 0;
	mother.lookat_z = 0;
	mother.up_x = 0;
	mother.up_y = 1;
	mother.up_z = 0;
	mother.yaw = 0;
	mother.roll = 0;
	mother.pitch = 0;

	scout.x = SCOUT_INIT_X;
	scout.y = SCOUT_INIT_Y;
	scout.z = SCOUT_INIT_Z;
	scout.lookat_x = 0;
	scout.lookat_y = 0;
	scout.lookat_z = 0;
	scout.up_x = 0;
	scout.up_y = 1;
	scout.up_z = 0;
	scout.yaw = 0;
	scout.roll = 0;
	scout.pitch = 0;

	mode = ABS_LOOK_AT;
	move_speed = DEFAULT_SPEED;
}

// keyboard callback
void keyboard_callback( unsigned char key, int x, int y ){
	switch( key ){
	case 27:
		quit = true;
		break;
	case '-':
		move_speed -= SPEED_UNIT;
		if (move_speed < 0)
			move_speed = 0;
		break;
	case '=':
		move_speed += SPEED_UNIT;
		if (move_speed > SPEED_LIMIT)
			move_speed = SPEED_LIMIT;
		break;
	case 'w':
		if (scout_ctrl) { 
			if (mode&REL_FLYING) 
				scout.forward += move_speed;
		}
		else {
			if (mode&REL_FLYING)
				mother.forward += move_speed;
		}
		break;
	case 's':
		if (scout_ctrl) { 
			if (mode&REL_FLYING) 
				scout.forward -= move_speed;
		}
		else {
			if (mode&REL_FLYING)
				mother.forward -= move_speed;
		}
		break;
	case 'p':
		paused = !paused;
		break;
	case 'm':
		reset();
		break;
	case 'l':
		mode = ABS_LOOK_AT;
		break;
	case 'r':
		mode = REL_FLYING;
		break;
	case 'g':
		mode = GEO_SYNC;
		break;
	case 'q':
		if (scout_ctrl) { 
			if (mode&REL_FLYING) 
				scout.yaw -= ROTATE_UNIT;
		}
		else {
			if (mode&REL_FLYING)
				mother.yaw -= ROTATE_UNIT;
		}
		break;
	case 'a':
		if (scout_ctrl) {
			if (mode&ABS_LOOK_AT)
				scout.lookat_x += LOOKAT_MOVE_UNIT;
			if (mode&REL_FLYING)
				scout.roll -= ROTATE_UNIT;
		}
		else {
			if (mode&ABS_LOOK_AT)
				mother.lookat_x += LOOKAT_MOVE_UNIT;
			if (mode&REL_FLYING)
				mother.roll -= ROTATE_UNIT;
		}
		break;
	case 'A':
		if (scout_ctrl)
			scout.lookat_x -= LOOKAT_MOVE_UNIT;
		else
			mother.lookat_x -= LOOKAT_MOVE_UNIT;
		break;
	case 'b':
		if (scout_ctrl)
			scout.lookat_y += LOOKAT_MOVE_UNIT;
		else
			mother.lookat_y += LOOKAT_MOVE_UNIT;
		break;
	case 'B':
		if (scout_ctrl)
			scout.lookat_y -= LOOKAT_MOVE_UNIT;
		else
			mother.lookat_y -= LOOKAT_MOVE_UNIT;
		break;
	case 'c':
		if (scout_ctrl) {
			if (mode&ABS_LOOK_AT)
				scout.lookat_z += LOOKAT_MOVE_UNIT;
			if (mode&REL_FLYING)
				scout.pitch += ROTATE_UNIT;
		}
		else {
			if (mode&ABS_LOOK_AT)
				mother.lookat_z += LOOKAT_MOVE_UNIT;
			if (mode&REL_FLYING)
				mother.pitch += ROTATE_UNIT;
		}
		break;
	case 'C':
		if (scout_ctrl)
			scout.lookat_z -= LOOKAT_MOVE_UNIT;
		else
			mother.lookat_z -= LOOKAT_MOVE_UNIT;
		break;
	case 'd':
		if (scout_ctrl) {
			if (mode&ABS_LOOK_AT)
				scout.up_x += UP_MOVE_UNIT;
			if (mode&REL_FLYING)
				scout.roll += ROTATE_UNIT;
		}
		else {
			if (mode&ABS_LOOK_AT)
				mother.up_x += UP_MOVE_UNIT;
			if (mode&REL_FLYING)
				mother.roll += ROTATE_UNIT;
		}
		break;
	case 'D':
		if (scout_ctrl)
			scout.up_x -= UP_MOVE_UNIT;
		else
			mother.up_x -= UP_MOVE_UNIT;
		break;
	case 'e':
		if (scout_ctrl){
			if (mode&ABS_LOOK_AT) 
				scout.up_y += UP_MOVE_UNIT;
			else if (mode&REL_FLYING)
				scout.yaw += ROTATE_UNIT;
		}
		else {
			if (mode&ABS_LOOK_AT)
				mother.up_y += UP_MOVE_UNIT;
			else if (mode&REL_FLYING)
				mother.yaw += ROTATE_UNIT;
		}
		break;
	case 'E':
		if (scout_ctrl)
			scout.up_y -= UP_MOVE_UNIT;
		else
			mother.up_y -= UP_MOVE_UNIT;
		break;
	case 'f':
		if (scout_ctrl)
			scout.up_z += UP_MOVE_UNIT;
		else
			mother.up_z += UP_MOVE_UNIT;
		break;
	case 'F':
		if (scout_ctrl)
			scout.up_z -= UP_MOVE_UNIT;
		else
			mother.up_z -= UP_MOVE_UNIT;
		break;
	case 'x':
		if (scout_ctrl){
			if (mode&ABS_LOOK_AT)
				scout.x += move_speed;
			if (mode&REL_FLYING)
				scout.pitch -= ROTATE_UNIT;
		}
		else {
			if (mode&ABS_LOOK_AT)
				mother.x += move_speed;
			if (mode&REL_FLYING)
				mother.pitch -= ROTATE_UNIT;
		}
		break;
	case 'X':
		if (scout_ctrl)
			scout.x -= move_speed;
		else
			mother.x -= move_speed;
		break;
	case 'y':
		if (scout_ctrl)
			scout.y += move_speed;
		else
			mother.y += move_speed;
		break;
	case 'Y':
		if (scout_ctrl)
			scout.y -= move_speed;
		else
			mother.y -= move_speed;
		break;
	case 'z':
		if (scout_ctrl)
			scout.z += move_speed;
		else
			mother.z += move_speed;
		break;
	case 'Z':
		if (scout_ctrl)
			scout.z -= move_speed;
		else
			mother.z -= move_speed;
		break;
	case 62:
		scout_ctrl = false;
		break;
	case 60:
		scout_ctrl = true;
		break;
	default:
		break;
	}

	/////////////////////////////////////////////////////////////
	/// TODO: Put your keyboard code here! //////////////////////
	/////////////////////////////////////////////////////////////

}

void update_solar_system() {
	for(int i=0;i<NUM_SPHERE;i++) {
		// increment axle spin
		obj_spin_rots[i]+=SPIN_UNITS[i];
		if (obj_spin_rots[i] >= FULL_ROTATION) 
			obj_spin_rots[i] = 0;

		// increment location on orbit
		obj_orbit_rots[i]+=ORBIT_UNITS[i];
		if (obj_orbit_rots[i] >= FULL_ROTATION) 
			obj_orbit_rots[i] = 0;

		//printf("obj[%d]: spin_rot=%f orbit_rot=%f\n",i,obj_spin_rots[i],obj_orbit_rots[i]);
	}

}

void draw_box(float x, float y, float z) {	
	glPushMatrix();
	glScalef(x,y,z);
	glutSolidCube(1);
	glPopMatrix();
}

void draw_cone(float x, float y, float z) {	
	glPushMatrix();
	glScalef(x,y,z);
	glutSolidCone(1,1,CONE_SLICES,CONE_STACKS);
	glPopMatrix();
}

void draw_scaled_icosahedron(float x, float y, float z) {	
	glPushMatrix();
	glScalef(x,y,z);
	glutSolidIcosahedron();
	glPopMatrix();
}

void draw_scoutship_wing() {
	// wing
	glPushMatrix();
	glTranslatef(SCOUT_BODY_SIZE/2+SCOUT_WING_LENGTH/2,0,0);
	draw_box(SCOUT_WING_LENGTH,SCOUT_WING_WIDTH,SCOUT_WING_WIDTH);
	glPushMatrix();
	// wing center panel
	glTranslatef(SCOUT_WING_LENGTH/2+SCOUT_PANEL_WIDTH/2,0,0);
	glRotatef(90,0,1,0);
	draw_box(SCOUT_PANEL_LENDTH,SCOUT_PANEL_HEIGHT,SCOUT_PANEL_WIDTH);
	glPushMatrix();
	// wing bottom panel
	glTranslatef(0,-SCOUT_PANEL_HEIGHT/2,0);
	glRotatef(SCOUT_PANEL_ANGLE,1,0,0);
	glTranslatef(0,-SCOUT_PANEL_HEIGHT/2,0);
	draw_box(SCOUT_PANEL_LENDTH,SCOUT_PANEL_HEIGHT,SCOUT_PANEL_WIDTH);
	glPopMatrix();
	// wing top panel
	glTranslatef(0,SCOUT_PANEL_HEIGHT/2,0);
	glRotatef(-SCOUT_PANEL_ANGLE,1,0,0);
	glTranslatef(0,SCOUT_PANEL_HEIGHT/2,0);
	draw_box(SCOUT_PANEL_LENDTH,SCOUT_PANEL_HEIGHT,SCOUT_PANEL_WIDTH);
	glPopMatrix();
	glPopMatrix();
}

void draw_scoutship() {
	// main body
	glPushMatrix();
	glColor3f(WHITE);
	draw_scaled_icosahedron(SCOUT_BODY_SIZE,SCOUT_BODY_SIZE,SCOUT_BODY_SIZE);
	// right wing
	draw_scoutship_wing();
	// left wing
	glRotatef(180,0,1,0);
	draw_scoutship_wing();
	glPopMatrix();
}

void draw_mothership() {
	// main body
	glPushMatrix();
	glScalef(1.0,1.0,-1.0);
	glColor3f(WHITE);
	draw_cone(MOTHER_BODY_WIDTH,MOTHER_BODY_HEIGHT,MOTHER_BODY_LENGTH);
	glTranslatef(0,MOTHER_BODY_HEIGHT,MOTHER_PLATFORM_LENGTH/2);
	draw_box(MOTHER_PLATFORM_WIDTH,MOTHER_PLATFORM_HEIGHT,MOTHER_PLATFORM_LENGTH);
	glTranslatef(0,MOTHER_PLATFORM_HEIGHT/4,0);
	draw_box(MOTHER_DECK_WIDTH,MOTHER_DECK_HEIGHT,MOTHER_DECK_LENDTH);
	glPopMatrix();
}

void draw_orbit_and_planet(int i) {
	glPushMatrix();
	glRotatef(-90,1.0,0,0);
	gluDisk(disks[i],OBJ_ORBIT_RADIUS[i]-ORBIT_WEIGHT/2,
		OBJ_ORBIT_RADIUS[i]+ORBIT_WEIGHT/2,DISK_SLICES,DISK_LOOPS);
	glRotatef(obj_orbit_rots[i], 0, 0, 1.0);
	glTranslatef(OBJ_ORBIT_RADIUS[i], 0, 0);
	glColor3f(OBJ_COLORS[i][RED],OBJ_COLORS[i][GREEN],OBJ_COLORS[i][BLUE]);
	gluSphere(spheres[i], OBJ_RADIUS[i], SPHERE_SLICES, SPHERE_STACKS); 
	if (i == SATURN) {
		glRotatef(SATURN_RING_ANGLE, 0,1.0,0);
		glColor4f(BROWN,ORBIT_ALPHA);
		gluDisk(disks[SATURN_RING],SATURN_RING_INNER_RAD,
			SATURN_RING_OUTER_RAD,DISK_SLICES,DISK_LOOPS);
	}
	glPopMatrix();
}

void draw_solar_system() {

	for (int i=0;i<NUM_SPHERE;i++) {

		glPushMatrix();
		if(!paused) {
			//printf("obj[%d]: orbit_rad=%f sphere_rad=%f\n",i,OBJ_ORBIT_RADIUS[i],OBJ_RADIUS[i]);
		}
		switch(i) {
		case SUN:
			glRotatef(obj_spin_rots[i], 0, 1.0, 0);
			glColor3f(OBJ_COLORS[i][RED],OBJ_COLORS[i][GREEN],OBJ_COLORS[i][BLUE]);
			gluSphere(spheres[i], OBJ_RADIUS[i], SPHERE_SLICES, SPHERE_STACKS);
			break;
		case MOON:
			glRotatef(obj_orbit_rots[EARTH], 0, 1.0, 0);
			glTranslatef(OBJ_ORBIT_RADIUS[EARTH], 0, 0);
		default:
			glColor4f(WHITE,ORBIT_ALPHA);
			draw_orbit_and_planet(i);
			break;
		}
		glPopMatrix();
	}

}

// display callback
void display_callback( void ){
	int current_window;
	GLfloat tmp_m[16];

	// retrieve the currently active window
	current_window = glutGetWindow();

	// clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/////////////////////////////////////////////////////////////
	/// TODO: Put your rendering code here! /////////////////////
	/////////////////////////////////////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 70.0f, float(glutGet(GLUT_WINDOW_WIDTH))/float(glutGet(GLUT_WINDOW_HEIGHT)), 0.1f, 2000.0f );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*glLoadIdentity();
	gluLookAt(mother.x, mother.y, mother.z, mother.lookat_x, mother.lookat_y, mother.lookat_z,
	mother.up_x, mother.up_y, mother.up_z);
	glGetFloatv(GL_MODELVIEW_MATRIX,mother.current_m);
	debug_matrix(mother.current_m);

	glLoadIdentity();
	gluLookAt(scout.x, scout.y, scout.z, scout.lookat_x, scout.lookat_y, scout.lookat_z,
	scout.up_x, scout.up_y, scout.up_z);	
	glGetFloatv(GL_MODELVIEW_MATRIX,scout.current_m);
	debug_matrix(scout.current_m);
	glLoadIdentity();*/


	if (current_window == mother_window) {
		glMultMatrixf(mother.current_m);

		glPushMatrix();
		memcpy(tmp_m,scout.current_m,sizeof(tmp_m));
		invert_pose(tmp_m);
		glMultMatrixf(tmp_m);
		draw_scoutship();
		glPopMatrix();
	} else if (current_window == scout_window) {
		glMultMatrixf(scout.current_m);	

		glPushMatrix();
		memcpy(tmp_m,mother.current_m,sizeof(tmp_m));
		invert_pose(tmp_m);
		glMultMatrixf(tmp_m);
		draw_mothership();
		glPopMatrix();
	}

	if (!paused) {
		update_solar_system();
	}
	draw_solar_system();

	// swap the front and back buffers to display the scene
	glutSetWindow( current_window );
	glutSwapBuffers();
}

void abs_lookat_matrix(ship* ship) {
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(ship->x, ship->y, ship->z, ship->lookat_x, ship->lookat_y, ship->lookat_z,
		ship->up_x, ship->up_y, ship->up_z);
	glGetFloatv(GL_MODELVIEW_MATRIX,ship->current_m);
	glPopMatrix();
}

void rel_flying_matrix(ship* ship) {
	glPushMatrix();
	glLoadIdentity();
	glRotatef(ship->yaw,0,1,0);
	glRotatef(ship->roll,0,0,1);
	glRotatef(ship->pitch,1,0,0);
	glTranslatef(0,0,ship->forward);
	ship->yaw=0;
	ship->roll=0;
	ship->pitch=0;
	ship->forward=0;
	glMultMatrixf(ship->current_m);
	glGetFloatv(GL_MODELVIEW_MATRIX, ship->current_m);
	glPopMatrix();
}

void getCurrentMatrice() {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	if (mode & ABS_LOOK_AT) {
		abs_lookat_matrix(&mother);
		abs_lookat_matrix(&scout);

	} else if (mode & REL_FLYING) {
		rel_flying_matrix(&mother);
		rel_flying_matrix(&scout);
	} else if (mode & GEO_SYNC) {

	}

	//debug_matrix(scout.current_m);
	//debug_matrix(mother.current_m);
	glPopMatrix();
}

// not exactly a callback, but sets a timer to call itself
// in an endless loop to update the program
void idle( int value ){

	// if the user wants to quit the program, then exit the
	// function without resetting the timer or triggering
	// a display update
	if( quit ){
		// cleanup any allocated memory
		cleanup();

		// perform hard exit of the program, since glutMainLoop()
		// will never return
		exit(0);
	}

	/////////////////////////////////////////////////////////////
	/// TODO: Put your idle code here! //////////////////////////
	/////////////////////////////////////////////////////////////

	getCurrentMatrice();

	// set the currently active window to the mothership and
	// request a redisplay
	glutSetWindow( mother_window );
	glutPostRedisplay();

	// now set the currently active window to the scout ship
	// and redisplay it as well
	glutSetWindow( scout_window );
	glutPostRedisplay();

	// set a timer to call this function again after the
	// required number of milliseconds
	glutTimerFunc( dt, idle, 0 );

}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Program Entry Point //////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
int main( int argc, char **argv ){
	// initialize glut
	glutInit( &argc, argv );

	// use double-buffered RGB+Alpha framebuffers with a depth buffer.
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );

	// initialize the mothership window
	glutInitWindowSize( disp_width, disp_height );
	glutInitWindowPosition( 0, 100 );
	mother_window = glutCreateWindow( "Mother Ship" );
	glutKeyboardFunc( keyboard_callback );
	glutDisplayFunc( display_callback );
	glutReshapeFunc( resize_callback );
	glutMouseFunc( mouse_callback );
	glutMotionFunc ( motion_callback );

	// initialize the scout ship window
	glutInitWindowSize( disp_width, disp_height );
	glutInitWindowPosition( disp_width+50, 100 );
	scout_window = glutCreateWindow( "Scout Ship" );
	glutKeyboardFunc( keyboard_callback );
	glutDisplayFunc( display_callback );
	glutReshapeFunc( resize_callback );

	glutSetWindow( mother_window );
	init();
	glutSetWindow( scout_window );
	init();

	// start the idle on a fixed timer callback
	idle( 0 );

	// start the blug main loop
	glutMainLoop();

	return 0;
}


// inversion routine originally from MESA
bool invert_pose( float *m ){
	float inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		m[i] = inv[i] * det;

	return true;
}