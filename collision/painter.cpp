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
#define DEG2RAD(deg) (deg * PI / 180)

using namespace std;

class Draw{
	public:

		void drawBox(float len){

			glBegin(GL_QUADS);
		    	glColor3f(232.0/248, 170.0/248, 84.0/248);
			    glVertex3f(-len / 2, -len / 2, 0);
			    glVertex3f(len / 2, -len / 2, 0);
			    glVertex3f(len / 2, len / 2, 0);
			    glVertex3f(-len / 2, len / 2, 0);
	    	glEnd();

		    len=len+0.6f;
		    glBegin(GL_QUADS);
			    glColor3f(0/248, 0/248, 0/248);
			    glVertex3f(-len / 2, -len / 2, 0);
			    glVertex3f(len / 2, -len / 2, 0);
			    glColor3f(43.0/248, 29.0/248, 17.0/248);
			    glVertex3f(len / 2, len / 2, 0);
			    glVertex3f(-len / 2, len / 2, 0);

		    glEnd();
		}

		void drawPocket(float rad, float len, float x, float y, float z ) {
		   glTranslatef(x, y, z);	
		   glColor4f(0.0/248, 33.0/248, 0.0/248 , 0.9);
		   glBegin(GL_TRIANGLE_FAN);
		   for(float i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   }
		   glEnd();
		}

		void drawCenter(float rad){
		   glPointSize(2);
		   glColor3f(31.0/244,31.0/244,31.0/244);
		   glBegin(GL_POINTS);
		   for(float i=0 ; i<360 ; i=i+0.1) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   }
		   glEnd();
		}
};
