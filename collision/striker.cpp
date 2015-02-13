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

class Striker{

	public:
		float posX , posY , rad, vel, velX, velY, x1, y1, x2, y2, angle, game;

		Striker() {

			this->posX=0;
			this->posY=-1.92; 
			this->velX = 0.0f;
			this->velY = 0.2f;
			this->angle = 0.0f;
			this->vel = sqrt(this->velX*this->velX+this->velY*this->velY);
			this->rad = 0.14;
			this->game = 1;
		}

		void reset(){

			posX=0;
			posY=-1.92; 
			velX = 0.0f;
			velY = 0.2f;
			angle = 0.0f;
			vel = 0.2;
			rad = 0.14;
		}

		void drawStriker(){
			glColor3f(11.0/244, 14.0/244, 82.0/244);
		   	glBegin(GL_TRIANGLE_FAN);
		   	for(float i=0 ; i<360 ; i++) {
		       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		   	}
		   	glEnd();
 
		}

		void moveLeft(){

			if(posX > x1+0.29)
				posX = posX - 0.01;
		}

		void moveRight(){

			if(posX < x2-0.29)
				posX = posX + 0.01;
		}

		void moveUp(){

			if(posY < y2 -0.02)
				posY = posY + 0.01;
		}

		void moveDown(){

			if(posY > y1 + 0.02)
				posY = posY - 0.01;
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

		void stop(){
			velX = 0;
			velY = 0;
		}

		void setVel(){

			velX = vel*sin(DEG2RAD(angle));
			velY = vel*cos(DEG2RAD(angle));
		}

		void dirLeft(){

			if(angle > -89)
				angle = angle - 1;
			setVel();
			chooseDir();
		}

		void dirRight(){

			if(angle < 89 )
				angle = angle + 1;
			setVel();
			chooseDir();
		}

		void chooseDir(){

			float len = 0.5f;
			glLineWidth(2);
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINES);
				glVertex2f(posX,posY);
				glVertex2f(posX + len*sin(DEG2RAD(angle)), posY + len*cos(DEG2RAD(angle)));
			glEnd();

			
			//glTranslatef(posX + len*sin(DEG2RAD(angle)), posY + len*cos(DEG2RAD(angle))+1,0);
			
			glPushMatrix();
			glTranslatef(posX,posY,0);
			glRotatef(-angle,0,0,1);
			glBegin(GL_TRIANGLES);
				glVertex2f(0 , len+0.1);
				glVertex2f(-0.05,len-0.05);
				glVertex2f(0.05,len-0.05);

			glEnd();
			glPopMatrix();

		}

		void increaseVel(){

			if(vel < 0.4f)
				vel = vel + 0.05;
			setVel();
			getVel(); 
		}

		void decreaseVel(){

			if(vel > 0.1f)
				vel = vel - 0.05;
			setVel();
			getVel();
		}

		void getVel(){

			float len = 10.0f;
			glLineWidth(2);
			glBegin(GL_LINES);
				glVertex2f(3.45,-2.0);
				glVertex2f(3.45,2.0);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(3.45,2.0);
				glVertex2f(3.65,2.0);
			glEnd();
				
			glColor3f(1.0, 1-vel/0.4, 0.0);
			glBegin(GL_QUADS);
				glVertex2f(3.45,-2.0);
				glVertex2f(3.45,-2.0+vel*len);
				glVertex2f(3.65,-2.0+vel*len);
				glVertex2f(3.65,-2.0);
			glEnd();

			glColor3f(0,0,0);
			glBegin(GL_LINES);
				glVertex2f(3.65,-2.0);
				glVertex2f(3.65,2.0);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(3.45,-2.01);
				glVertex2f(3.65,-2.01);
			glEnd();

			glBegin(GL_QUADS);
				glColor4f(0,0,0,0.3);
				glVertex2f(3.65,-2.0);
				glVertex2f(3.65,2.0);
				glVertex2f(3.45,2.0);
				glVertex2f(3.45,-2.0);
			glEnd();

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