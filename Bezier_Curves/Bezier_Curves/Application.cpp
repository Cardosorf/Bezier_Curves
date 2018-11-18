#include <OpenGL/gl.h>     // The GL Header File
#include <cmath>
#include <stdlib.h>
#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
#include <iostream>
#include <vector>
#include <queue> 
#include <algorithm>
#include <utility> 
#include <ctime>
#include <stdio.h>
#include <string.h>


#include <GL/glut.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES

#define WIDTH 800
#define HEIGHT 600

static int horizontal = 0;
static int vertical = 0;
static int diagonal = 0;

using namespace std;


//Creates a class to handle OrderedPairs
class OrderedPair {

public:
	float getAxis_x(void);
	float getAxis_y(void);
	float getAxis_z(void);
	OrderedPair(float x_value, float y_value, float z_value);

private:
	float x;
	float y;
	float z;
};

//Sets the ordered pair
OrderedPair::OrderedPair(float x_value, float y_value, float z_value) {
	x = x_value;
	y = y_value;
	z = z_value;
}

float OrderedPair::getAxis_x(void) {
	return x;
}

float OrderedPair::getAxis_y(void) {
	return y;
}

float OrderedPair::getAxis_z(void) {
	return z;
}

vector<OrderedPair> pointsArray;


int factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


OrderedPair bezier_curve(int n, float t) {
	float x = 0;
	float y = 0;
	float z = 0;
	n = n - 1;
	for (int i = 0; i < n + 1; i++) {
		x += (factorial(n) / (factorial(i)*factorial(n - i))) *pow(1 - t, n - i)*pow(t, i)*(pointsArray[i].getAxis_x());
		y += (factorial(n) / (factorial(i)*factorial(n - i))) *pow(1 - t, n - i)*pow(t, i)*(pointsArray[i].getAxis_y());
		z += (factorial(n) / (factorial(i)*factorial(n - i))) *pow(1 - t, n - i)*pow(t, i)*(pointsArray[i].getAxis_z());
	}

	OrderedPair temp(x, y, z);

	return temp;
}


void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	//glTranslatef(0.0, 0.0, -5.0);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)horizontal, 0.0, 0.0, 1.0);
	glRotatef((GLfloat)vertical, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)diagonal, 1.0, 0.0, 0.0);

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(0.6,0.0, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'X');

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(0.0, 0.6, 0.0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'Y');

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(0.0, 0.0, 0.6);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'Z');

	// X axis
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glEnd();
	glPopMatrix();

	// Y axis
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	glPopMatrix();

	// Z axis
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(4.0);
	glScalef(1.0, 2.0, 5.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < pointsArray.size(); i++) {
		glVertex3f(pointsArray[i].getAxis_x(), pointsArray[i].getAxis_y(), pointsArray[i].getAxis_z());
	}
	glEnd();
	glPopMatrix();

	vector<OrderedPair> bezier_points;

	for (float t = 0; t < 1.0; t += 0.01) {
		bezier_points.push_back(bezier_curve(pointsArray.size(), t));
	}
	
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);

	glScalef(1.0, 2.0, 5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < bezier_points.size(); i++) {
		glVertex3f(bezier_points[i].getAxis_x(), bezier_points[i].getAxis_y(), bezier_points[i].getAxis_z());
	}
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}


void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'w':
		vertical = (vertical + 5) % 360;
		glutPostRedisplay();
		break;
	case 's':
		vertical = (vertical - 5) % 360;
		glutPostRedisplay();
		break;
	case 'd':
		horizontal = (horizontal + 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		horizontal = (horizontal - 5) % 360;
		glutPostRedisplay();
		break;
	case 'q':
		diagonal = (diagonal - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		diagonal = (diagonal + 5) % 360;
		glutPostRedisplay();
		break;
	case 27:                                       
		exit(0);
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(500, 150);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow("Rafael Pais Cardoso");

	

	/*
	pointsArray.push_back(OrderedPair(-0.8, -0.8, -0.2));
	pointsArray.push_back(OrderedPair(0.8, 0.3, 0.8));
	pointsArray.push_back(OrderedPair(0.4, 0.7, -0.6));
	pointsArray.push_back(OrderedPair(-0.4, 0.3, 1.0));
	pointsArray.push_back(OrderedPair(0.4, -0.9, 0.1));
	*/

	/*
	pointsArray.push_back(OrderedPair(-2.0, 1.0, 0.0));
	pointsArray.push_back(OrderedPair(-0.5, 0.5, -0.5));
	pointsArray.push_back(OrderedPair(0.4, -1.0, 1.0));
	pointsArray.push_back(OrderedPair(1.0, 0.5, -0.6));
	pointsArray.push_back(OrderedPair(1.5, -0.5, -1.6));
	*/

	/*
	pointsArray.push_back(OrderedPair(-1.0, 0.0, 0.0));
	pointsArray.push_back(OrderedPair(-0.3, 0.5, -0.5));
	pointsArray.push_back(OrderedPair(0.0, 0.5, 0.0));
	pointsArray.push_back(OrderedPair(0.3, -0.5, 0.5));
	pointsArray.push_back(OrderedPair(1.0, 0.0, 0.0));
	*/

	/*
	pointsArray.push_back(OrderedPair(-1.0, 0.0, -1.0));
	pointsArray.push_back(OrderedPair(-0.8, -0.5, -0.5));
	pointsArray.push_back(OrderedPair(-0.6, 0.5, 1.0));
	pointsArray.push_back(OrderedPair(0.3, -1.0, 0.5));
	pointsArray.push_back(OrderedPair(1.0, 1.0, -1.0));
	*/

	/*
	pointsArray.push_back(OrderedPair(-1.0, 0.0, -1.0));
	pointsArray.push_back(OrderedPair(-0.8, -0.5, -0.5));
	pointsArray.push_back(OrderedPair(-0.6, 0.5, 1.0));
	pointsArray.push_back(OrderedPair(0.3, -1.0, 0.5));
	pointsArray.push_back(OrderedPair(0.5, 0.0, 0.0));
	pointsArray.push_back(OrderedPair(0.85, 1.0, -0.8));
	pointsArray.push_back(OrderedPair(1.0, 1.0, -1.0));
	*/

	
	pointsArray.push_back(OrderedPair(-1.0, -1.0, -1.0));
	pointsArray.push_back(OrderedPair(-0.8, -0.5, 0.5));
	pointsArray.push_back(OrderedPair(-0.6, 0.5, 1.0));
	pointsArray.push_back(OrderedPair(0.0, -1.0, -1.0));
	pointsArray.push_back(OrderedPair(0.5, 0.0, 0.0));
	pointsArray.push_back(OrderedPair(0.85, 1.0, -0.8));
	pointsArray.push_back(OrderedPair(-0.8, 1.0, -0.8));
	pointsArray.push_back(OrderedPair(1.0, 1.0, -1.0));
	


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return EXIT_SUCCESS;
}