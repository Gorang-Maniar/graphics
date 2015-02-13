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

class StartLine{
	public:
		float x1,y1,x2,y2;

		void drawLine(){
			glColor3f(0,0,0);
			glBegin(GL_LINES);
				glVertex3f(x1, y1, 0);
				glVertex3f(x2, y2, 0);
			glEnd();

			float a1=(x1>0) ? x1-0.15 : x1 + 0.15;
			float b1=(y1>0) ? y1-0.15 : y1 + 0.15;
			float a2=(x2>0) ? x2-0.15 : x2 + 0.15;
			float b2=(y2>0) ? y2-0.15 : y2 + 0.15;

			glBegin(GL_LINES);
				glVertex3f(a1, b1, 0);
				glVertex3f(a2, b2, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(a1, b1, 0);
				glVertex3f(x1, y1, 0);
			glEnd();

			glBegin(GL_LINES);
				glVertex3f(a2, b2, 0);
				glVertex3f(x2, y2, 0);
			glEnd();

			//drawCircle(a1,(b1+y1)/2,0.05);

		}

		void drawCircle(float a, float b, float rad){

			glTranslatef(a,b,0);
			glColor3f(244.0/244, 0.0/244, 0.0/244);
		   	glBegin(GL_TRIANGLE_FAN);
		   	for(float i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   	}
		   	glEnd();
		}

};