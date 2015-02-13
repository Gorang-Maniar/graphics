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

class CarromCoin{

	public:
		float value, posX, posY, rad, velX, velY, game;

		CarromCoin(){

			this->rad=0.1;
			this->velX = 0.00;
			this->velY = 0.00;
			this->posX = 0.0;
			this->posY = 0.0;
			this->game = 1;
		}

		void drawCoin(int color){
			if(color == 1)
				glColor3f(69.0/244,69.0/244,69.0/244);

			else if(color == 0)
				glColor3f(230.0/244,230.0/244,230.0/244);
			
			else if(color == 5)
				glColor3f(232.0/244,51.0/244,54.0/244);


		   	glBegin(GL_TRIANGLE_FAN);
		   	for(float i=0 ; i<360 ; i++) 
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   	glEnd();

		   	glPointSize(2);
		   	glColor3f(0.0,0.0,0.0);
		   	glBegin(GL_POINTS);
		   	for(float i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   	}
		   	glEnd();
		}


		void strike(){

			float len = 5.0f;

			if((pow(-len/2 + 0.2 - posX,2)+pow(-len/2 + 0.2 - posY,2) <= 0.02) || 
			   (pow(+len/2 - 0.2 - posX,2)+pow(+len/2 - 0.2 - posY,2) <= 0.02) ||
			   (pow(-len/2 + 0.2 - posX,2)+pow(+len/2 - 0.2 - posY,2) <= 0.02) ||
			   (pow(+len/2 - 0.2 - posX,2)+pow(-len/2 + 0.2 - posY,2) <= 0.02)){
				
				game = 0;
				posX = 4.0f;
				posY = 4.0f;
				velX = 0;
				velY = 0;
			}
			else{
				posX = posX + velX;
				posY = posY + velY;
			}
		}

		void check(){

			float len = 5.0f;

    		if(posX + rad > len/2 || posX - rad < -len/2)
        		velX *= -1;
    		if(posY + rad > len/2 || posY - rad < -len/2)
        		velY *= -1;

		}


		void deaccelerate(){

			if(abs(velX) < 0.001 && abs(velY) < 0.001){
				velX = 0;
				velY = 0;
			}

			velX = 0.979*velX;
			velY = 0.979*velY;
		}
};		