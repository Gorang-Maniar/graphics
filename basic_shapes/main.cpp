/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Color" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <iostream>
#include <stdlib.h>
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.1417

using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL); //Enable color
	glClearColor(0.7f, 0.9f, 1.0f, 1.0f); //Change the background to sky blue
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 30.0f;
float _cameraAngle = 0.0f;

void drawFilledCircle(float x, float y, float radius){
	
	int i;
	int triangleAmount = 40; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	float twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-_cameraAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);
	
	glPushMatrix();
	glTranslatef(-1.0f, -1.0f, 0.0f);
	glRotatef(_angle, 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_QUADS);
	
	//Trapezoid
	glColor3f(0.5f, 0.0f, 0.8f);
	glVertex3f(-0.7f, -0.5f, 0.0f);
	glColor3f(0.0f, 0.9f, 0.0f);
	glVertex3f(0.7f, -0.5f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.5f, 0.0f);
	glColor3f(0.0f, 0.65f, 0.65f);
	glVertex3f(-0.4f, 0.5f, 0.0f);
	
	glEnd();
	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f, 1.0f, 0.0f);
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glScalef(0.7f, 0.7f, 0.7f);
	
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.75f, 0.0f);
	
	//Pentagon
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	
	glEnd();
	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0f, 1.0f, 0.0f);
	glRotatef(_angle, 1.0f, 2.0f, 3.0f);
	
	glBegin(GL_TRIANGLES);
	
	//Triangle
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	
	glEnd();
	
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1.0f, -1.0f, 0.0f);
	glRotatef(_angle, 1.0f, 0.0f, 1.0f);
	
	drawFilledCircle(0.0f, 0.0f, 0.5f);
	
	glPopMatrix();
	glutSwapBuffers();
}

void update(int value) {
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Color - Basic Shapes");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}









