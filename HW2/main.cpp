/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
//#include <GL/freeglut.h>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; 

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1(){
  // Define the size of each teapot
  float size_of_teapot {.3f};
  // Set the one_cycle to 360 to complete one cycle
  float one_cycle {360};
  // Initialize radius to 0
  float radius {.0f};

  // Create a new teapot while the camera angle is less than 360 degrees
  while(radius != one_cycle){ 
    // Push the current matrix onto the stack
    glPushMatrix();
    // Move the object to the center of the screen
    glTranslatef(0, -0.5, -2);
    // Rotate the object around the z-axis by the given radius angle
    glRotatef(radius, 0, 0, 1);
    // Translate the object along the x-axis by 2 units
    glTranslatef(2, 0, 0);
    // Draw a solid teapot of size_of_teapot
    glutSolidTeapot(size_of_teapot);
    // Pop the current matrix off the stack
    glPopMatrix();
    // Increment the radius by 36 to create 10 teapots in total
    radius += 36;
  }
}

void problem2(){
  unsigned int max_stair{20}; //we want 20 stairs (cube)
  unsigned int curr_num{1}; //start from one stair cube
  float xdir{-10}; //x-direction/position
  float ydir{-7};  //y-direction/position
  float zdir{-7}; // z-direction/position 
  float stair_size{.8}; //decrease the size of the stair cubes
  float increment_height{.26f}; 
  int counter = 20;

  glPushMatrix();
  glRotatef(180, 0, 1, 0); // rotate the scene by 180 degrees along the y-axis
  while(curr_num <= max_stair){
    glPushMatrix();
    glTranslatef(xdir, ydir, zdir); //move along x, y and z direction
    glScalef(1, curr_num*.5, 1); //1 x, currnum*1/2 y (increase height), 1 is z axis
    glutSolidCube(stair_size); 
    glPopMatrix();
    counter--;

    // decrease the y-position and z-position for the next stair
    ydir += increment_height; 
    zdir += stair_size; 
    ++curr_num;
  }
  glPopMatrix(); // restore the original transformation matrix
}

void problem3() {
  float teapot_size{0.25};
  int level{1};
  int pyramid_level{6}; //# of levels/rows in the pyramid
  

  for (; level <= pyramid_level; ++level) {
    // Calculate the horizontal offset for this row
    float offset = (pyramid_level - level) * 0.6f;
    // Calculate the starting position for the first teapot in this row
    float first_teapot_offset = -offset / 2;
    // Calculate the number of teapots on this row
    int num_teapots = pyramid_level - level + 1;
    // Calculate the spacing between teapots on this row
    float spacing = 0.6f;
    if (num_teapots > 1) {
      spacing = offset / (num_teapots - 1);
    }

    for (int teapot = 0; teapot < num_teapots; ++teapot) {
      glPushMatrix();
      // Calculate the horizontal position of this teapot
      float teapot_offset = first_teapot_offset + teapot * spacing;
      // Calculate the vertical position of this teapot
      float y = (pyramid_level - level) * 0.6f - pyramid_level * 0.3f;
      glTranslatef(teapot_offset, y, 0);
      glutSolidTeapot(teapot_size);
      glPopMatrix();
    }
  }
}

void problem4(){
  static float thumb_up = 30, point_up = 15, middle_up = 0, ring_up = 35, tiny_up = 35;
  static float hand_body = 90, thumb_fngr = 35, point_fngr = 10, middle_fngr = 0, ring_fngr = 60, tiny_fngr = 35;
  glClear (GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);
  float r{1.0f}, b{1.0f}, g{0.75f};
  glColor3f(r, g, b);
   
  // Palm of hand
  glTranslatef(0.0, 0.0, 0.0);
  glRotatef((GLfloat)hand_body, 0.0, 0.0, 5.0);
  glTranslatef(0.20, 0.5, 0.5);
  glPushMatrix();  // push the current matrix
  glColor3f(0.8f, 0.5f, 0.2f);
  glScalef(0.75, 0.2, 1.1);
  glutSolidCube(1.0);

  // add nested matrix transformation
  glPushMatrix();
  // Add matrix transformations for equilateral triangle
  glTranslatef(-1.0, 0.0, 0.0);
  glRotatef(60.0, -1.0, -1.0, 1.0);
  glRotatef(-60.0, 1.0, -4.0, -1.0); 
  glColor3f(1.0f, 1.0f, 1.0f); 
  glBegin(GL_TRIANGLES);
  glVertex3f(0.0, 0.5, 0.0);
  glVertex3f(-0.5, -0.5, 0.0);
  glVertex3f(0.5, -0.5, 0.0);
  glEnd();
  glPopMatrix();
  glPopMatrix();  

  
  // Bottom Joint of Thumb finger
  glPushMatrix();
  glTranslatef(0.0, 0.125, -0.1);
  glRotatef((GLfloat)thumb_fngr, 0.0, 0.0, 1.0);
  glTranslatef(0.25, 0.0, 0.8);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef(0.5, 0.2, 0.2);
  glutSolidCube(0.7);
  glPopMatrix();

  // Upper Joint of Thumb finger
  glTranslatef(0.15, 0.0, -0.8);
  glRotatef((GLfloat)thumb_up, 0.0, 0.0, 1.0); 
  glTranslatef(0.25, 0.0, 0.8);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef(0.5, 0.2, 0.2);
  glutSolidCube(0.7);
  glPopMatrix();
  glPopMatrix();

  
  //Bottom Joint Pointer Finger
  glPushMatrix();
  glTranslatef (0.5, 0.1, 0.0);
  glRotatef ((GLfloat) point_fngr, 0.0, 0.0, 0);
  glTranslatef (0.0, 0.0, 0.4);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef (0.6, 0.2, 0.2);
  glutSolidCube (0.8);
  glPopMatrix();

  //Upper Joint of Pointer finger
  glTranslatef (0.5, 0.0, 0.0);
  glRotatef ((GLfloat) point_up, 0.0, 0.0, 0);
  glTranslatef (0.0, 0.0, 0.0);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef (0.6, 0.2, 0.2);
  glutSolidCube (0.8);
  glPopMatrix();       
  glPopMatrix();

  
  //Upper Joint of Middle Finger
  glPushMatrix();
  glTranslatef (0.5, 0.10, 0.0);
  glRotatef ((GLfloat) middle_fngr, 0.0, 0.0, 1.0);
  glTranslatef (0.0, 0.0, 0.0);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef (0.6, 0.2, 0.2);
  glutSolidCube (0.8);
  glPopMatrix();

  //Bottom Joint of Middle Finger
  glTranslatef (0.5, 0.0, 0.0);
  glRotatef ((GLfloat) middle_up, 0.0, 0.0, 1.0); 
  glTranslatef (0.0, 0.0, 0.0);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef (0.6, 0.2, 0.2);
  glutSolidCube (0.8);
  glPopMatrix();
  glPopMatrix();

  //Upper Joint of Ring Finger
  glPushMatrix();
  glTranslatef (0.5, 0.1, 0.1);
  glRotatef ((GLfloat) ring_fngr, 0.0, 0.0, 4.0);

  glTranslatef (0.0, 0.0, -0.4);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef (0.6, 0.2, 0.2);
  glutSolidCube (0.8);
  glPopMatrix();

  //Bottom Joint of Ring Finger
  glTranslatef (0.5, 0.1, 0.0);
  glRotatef ((GLfloat) ring_up, 0.0, 0.0, 8.0);

  glTranslatef (0.0, -0.1,  0.0);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef (0.6, 0.2, 0.2);
  glutSolidCube (0.8);
  glPopMatrix();
  glPopMatrix();

  
  //Bottom Joint Pinky Finger
  glPushMatrix();
  glTranslatef (0.2, 0.1, 0.0);
  glRotatef ((GLfloat) tiny_fngr, 0.0, 0.0, 4.0);
  glTranslatef (0.0, 0.0, -0.6);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef (0.5, 0.2, 0.2);
  glutSolidCube (0.8);
  glPopMatrix();

  //Upper Joint of Pinky Finger
  glTranslatef (0.4, 0.1, 0.0);
  glRotatef ((GLfloat) tiny_up, 0.0, 0.0, 4.0);
  glTranslatef (0.0, -0.1, 0.0);
  glPushMatrix();
  glColor3f(r, g, b);
  glScalef (0.6, 0.2, 0.2);
  glutSolidCube (0.8);
  glPopMatrix();
  glPopMatrix();

  
  glPopMatrix();
  glutSwapBuffers();
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
