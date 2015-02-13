#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<GL/glut.h>

using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI/180)
int score = 30;
int t=0;
class Draw{
	public:

		void Box(float len){

			glBegin(GL_QUADS);
			glColor3f(200.0/248, 150.0/248, 70.0/248);
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
			glColor3f(30.0/248, 25.0/248, 15.0/248);
			glVertex3f(len / 2, len / 2, 0);
			glVertex3f(-len / 2, len / 2, 0);

			glEnd();
		}

		void Pocket(float rad, float len, float x, float y, float z ) {
			glTranslatef(x, y, z);	
			glColor3f(0.0/248, 15.0/248, 0.0/248);
			glBegin(GL_TRIANGLE_FAN);
			for(float i=0 ; i<360 ; i++) {
				glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
			}
			glEnd();
		}

		void Center(float rad){
			glPointSize(2);
			glColor3f(31.0/244,31.0/244,31.0/244);
			glBegin(GL_POINTS);
			for(float i=0 ; i<360 ; i=i+0.1) {
				glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
			}
			glEnd();
		}
};

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

		void moveLeft(){

			if(posX > x1+0.29)
				posX = posX - 0.02;
		}

		void moveRight(){

			if(posX < x2-0.29)
				posX = posX + 0.02;
		}

		void moveUp(){

			if(posY < y2 -0.02)
				posY = posY + 0.02;
		}

		void moveDown(){

			if(posY > y1 + 0.02)
				posY = posY - 0.02;
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
			glColor3f(0/244, 82.0/244, 0/244);
			glBegin(GL_TRIANGLE_FAN);
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

		void stop(){
			velX = 0;
			velY = 0;
		}

		void setVelo(){

			velX = vel*sin(DEG2RAD(angle));
			velY = vel*cos(DEG2RAD(angle));
		}

		void dirLeft(){

			if(angle > -89)
				angle = angle - 1;
			setVelo();
			chooseDir();
		}

		void dirRight(){

			if(angle < 89 )
				angle = angle + 1;
			setVelo();
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

			/*glPushMatrix();
			glTranslatef(posX,posY,0);
			glRotatef(-angle,0,0,1);
			glBegin(GL_TRIANGLES);
			glVertex2f(0 , len+0.1);
			glVertex2f(-0.05,len-0.05);
			glVertex2f(0.05,len-0.05);

			glEnd();
			glPopMatrix();
*/
		}

		void increaseVelo(){

			if(vel < 0.4f)
				vel = vel + 0.05;
			setVelo();
			getVelo(); 
		}

		void decreaseVelo(){

			if(vel > 0.1f)
				vel = vel - 0.05;
			setVelo();
			getVelo();
		}

		void getVelo(){

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


		void strike(int j){

			float len = 5.0f;

			if((pow(-len/2 + 0.2 - posX,2)+pow(-len/2 + 0.2 - posY,2) <= 0.02) || 
					(pow(+len/2 - 0.2 - posX,2)+pow(+len/2 - 0.2 - posY,2) <= 0.02) ||
					(pow(-len/2 + 0.2 - posX,2)+pow(+len/2 - 0.2 - posY,2) <= 0.02) ||
					(pow(+len/2 - 0.2 - posX,2)+pow(-len/2 + 0.2 - posY,2) <= 0.02)){
				if(j%2==0){
					score -= 5;

				}
				else{
					score+=10;
				}
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

float len=5.0f;
float _angle = 0;
float originX = 0, originY = 0;
int flagStriker = 0;
int activeStriker = 1;
int coinActive = 0;
int i = 0, j = 0;
char s[50] = "score:";
Striker strik;
CarromCoin coinObject[19];

void handleKeypress1(unsigned char key, int x, int y); 
void handleKeypress2(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void initRendering();
void handleResize(int w, int h);
void rotate();
void drawScene();
void update(int value);
void rotateBox(int value);
void arrangeCoin();
void output(float x, float y, float r, float g, float b, char *string);

int main(int argc, char** argv)
{
	//glut initialize
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	int windowWidth = glutGet(GLUT_SCREEN_WIDTH);
	int windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0,0);

	//Create the window
	glutCreateWindow("My Carrom");
	initRendering();

	arrangeCoin();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutReshapeFunc(handleResize);
	glutMouseFunc(mouse);
//	print(1,1,"Score:");
	glutTimerFunc(10, update, 0); //Add a timer	
	glutMainLoop();
	return 0;
}
//called when key is pressed
void handleKeypress1(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;

		case 32: //SPACE key
			flagStriker = 1;
			activeStriker = 0;

			break;

		case 13: //Enter key	
			flagStriker = 0;
			break;

		case 'a':
			if(activeStriker == 1)
				strik.dirLeft();
			break;

		case 'd':
			if(activeStriker == 1)
				strik.dirRight();
			break;

		case 'w':
			if(activeStriker == 1)
				strik.increaseVelo();
			break;

		case 's':
			if(activeStriker == 1)
				strik.decreaseVelo();
			break;				
	}
}

void handleKeypress2(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT && activeStriker == 1)
		strik.moveLeft();
	if (key == GLUT_KEY_RIGHT && activeStriker == 1)
		strik.moveRight();
	if (key == GLUT_KEY_UP && activeStriker == 1)
		strik.moveUp();
	if (key == GLUT_KEY_DOWN && activeStriker == 1){
		strik.moveDown();
	}  
}

void mouse(int button, int state, int x, int y)
{
	// Wheel reports as button 3(scroll up) and button 4(scroll down)
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(activeStriker == 1)
			strik.dirLeft();
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		if(activeStriker == 1)
			strik.dirRight();
	}

	/*if(state == GLUT_DOWN){

	  flagStriker = 1;
	  activeStriker = 0;
	  }*/
	if (button == 3 ){
		if(activeStriker == 1)
			strik.increaseVelo();
	}

	if(button == 4 ){
		if(activeStriker == 1)
			strik.decreaseVelo();
	}
}

//Initializes rendering
void initRendering() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	glEnable(GL_COLOR_MATERIAL); //Enable color
	glClearColor(0.0/248, 33.0/248, 0.0/248,0.0f); //Change the background to green
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void rotate(){
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
}

//Draws the carrom board
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	void initiate();

	Draw drawObject;

	glTranslatef(originX, originY, -8.0f);

	if(activeStriker==1){

		glPushMatrix();
		strik.chooseDir();
		glPopMatrix();

		glPushMatrix();
		strik.getVelo();
		glPopMatrix();
	}


	strik.x1 = -len/2 + 0.5;
	strik.y1 = -len/2 + 0.5;
	strik.x2 = +len/2 - 0.5;
	strik.y2 = -len/2 + 0.65;

	glPushMatrix();
	glTranslatef(strik.posX, strik.posY , 0);
	strik.drawStriker();
	glPopMatrix();
	//////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(coinObject[0].posX, coinObject[0].posY,0);
	coinObject[0].drawCoin(5);
	glPopMatrix();

	int color;
	for (int i = 1; i < 7; ++i)
	{
		if( i % 2 == 0)
			color = 1;
		else
			color = 0;
		glPushMatrix();
		glTranslatef(coinObject[i].posX, coinObject[i].posY ,0);
		coinObject[i].drawCoin(color);
		glPopMatrix();
	}

	for (int i = 7; i < 19; ++i)
	{
		if( i % 2 == 0)
			color = 1;
		else
			color = 0;
		glPushMatrix();
		glTranslatef(coinObject[i].posX ,  coinObject[i].posY, 0);
		coinObject[i].drawCoin(color);
		glPopMatrix();
	}
	//////////////////////////////////////////////////////////////
	glPushMatrix();
	drawObject.Pocket(0.2f, len, -len/2 + 0.2,-len/2 + 0.2, 0);
	glPopMatrix();

	glPushMatrix();
	drawObject.Pocket(0.2f, len, -len/2 + 0.2,+len/2 - 0.2, 0);
	glPopMatrix();

	glPushMatrix();
	drawObject.Pocket(0.2f, len, +len/2 - 0.2,-len/2 + 0.2, 0);
	glPopMatrix();

	glPushMatrix();
	drawObject.Pocket(0.2f, len, +len/2 - 0.2,+len/2 - 0.2, 0);
	glPopMatrix();

	glPushMatrix();
	drawObject.Center(0.6f);
	glPopMatrix();

	/////////////////////////////////////////////////////////////////
	StartLine line1, line2, line3, line4;

	glPushMatrix();
	line1.x1=-len/2+0.5;
	line1.y1=-len/2+0.5;
	line1.x2=-len/2+0.5;
	line1.y2=+len/2-0.5;
	line1.drawLine();
	glPopMatrix();

	glPushMatrix();
	line2.x1=-len/2+0.5;
	line2.y1=-len/2+0.5;
	line2.x2=+len/2-0.5;
	line2.y2=-len/2+0.5;
	line2.drawLine();
	glPopMatrix();

	glPushMatrix();
	line3.x1=+len/2-0.5;
	line3.y1=+len/2-0.5;
	line3.x2=+len/2-0.5;
	line3.y2=-len/2+0.5;
	line3.drawLine();
	glPopMatrix();

	glPushMatrix();
	line4.x1=+len/2-0.5;
	line4.y1=+len/2-0.5;
	line4.x2=-len/2+0.5;
	line4.y2=+len/2-0.5;
	line4.drawLine();
	glPopMatrix();
	///////////////////////////////////////////////////////////////
	glPushMatrix();
	//glRotatef(_angle, 0.0f, 0.0f, 1.0f);
	drawObject.Box(len);
	if(coinActive==0){
	t += 1;
	}
	if(t%100==0){
		score-=1;
	}
	char buffer[100];
	sprintf(buffer, "Score: %d", score);
	output(4.0f,1.2f,1,1,1,buffer);	
	glPopMatrix();
	////////////////////////////////////////////////////////////////

	glutSwapBuffers();
}

void update(int value) {

	for(i=0 ; i < 19; i++){

		for(j = i+1; j<19 ; j++){

			if((sqrt(pow(coinObject[i].posX-coinObject[j].posX, 2)+pow(coinObject[i].posY-coinObject[j].posY, 2)) <= coinObject[i].rad + coinObject[j].rad) 
					&& coinObject[i].game ==1 && coinObject[j].game ==1 ){

				if((coinObject[i].posX - coinObject[j].posX)*(coinObject[i].velX - coinObject[j].velX) +
						(coinObject[i].posY - coinObject[j].posY)*(coinObject[i].velY - coinObject[j].velY) < 0){
					float z1,z2,q1,q2,q11,q22,z;

					z1=coinObject[j].posX - coinObject[i].posX;
					z2=coinObject[j].posY - coinObject[i].posY;

					z=sqrt(z1*z1+z2*z2); // |z|

					q1=(z1*coinObject[i].velX + z2*coinObject[i].velY)/z;
					q2=(z1*coinObject[j].velX + z2*coinObject[j].velY)/z;

					// q1 = projection of v1 along z = v1.z/|z| = component of v1 along the direction of z
					// q2 = projection of v2 along z = v2.z/|z| = component of v2 along the direction of z

					float temp;
					temp =q1;
					q1 = q2;
					q2 = temp;

					// Interchange the velocities along the line fo collision

					q11=(z2*coinObject[i].velX - z1*coinObject[i].velY)/z;
					q22=(z2*coinObject[j].velX - z1*coinObject[j].velY)/z;

					coinObject[i].velX=((q1*z1+q11*z2)/z);
					coinObject[i].velY=((q1*z2-q11*z1)/z);
					coinObject[j].velX=((q2*z1+q22*z2)/z);
					coinObject[j].velY=((q2*z2-q22*z1)/z);
				}
			}

			if((sqrt(pow(coinObject[i].posX-coinObject[j].posX, 2)) + sqrt(pow(coinObject[i].posY-coinObject[j].posY, 2)) > coinObject[i].rad + coinObject[j].rad)){

				coinObject[i].check();
				coinObject[j].check();	
			}		
		}
		//coinObject[i].strike();
	}

	for(j=0; j < 19 ; j++){

		if(sqrt(pow(strik.posX-coinObject[j].posX, 2)+pow(strik.posY-coinObject[j].posY, 2)) <= strik.rad + coinObject[j].rad 
				&& coinObject[j].game == 1 && strik.game == 1){

			if((strik.posX - coinObject[j].posX)*(strik.velX - coinObject[j].velX) +
					(strik.posY - coinObject[j].posY)*(strik.velY - coinObject[j].velY) < 0){

				float z1,z2,q1,q2,q11,q22,z;

				z1=coinObject[j].posX - strik.posX;
				z2=coinObject[j].posY - strik.posY;

				z=sqrt(z1*z1+z2*z2); // |z|

				q1=(z1*strik.velX + z2*strik.velY)/z;
				q2=(z1*coinObject[j].velX + z2*coinObject[j].velY)/z;

				// q1 = projection of v1 along z = v1.z/|z| = component of v1 along the direction of z
				// q2 = projection of v2 along z = v2.z/|z| = component of v2 along the direction of z

				float temp;
				temp =q1;
				q1 = q2;
				q2 = temp;

				// Interchange the velocities along the line fo collision

				q11=(z2*strik.velX - z1*strik.velY)/z;
				q22=(z2*coinObject[j].velX - z1*coinObject[j].velY)/z;

				strik.velX=((q1*z1+q11*z2)/z);
				strik.velY=((q1*z2-q11*z1)/z);
				coinObject[j].velX=((q2*z1+q22*z2)/z);
				coinObject[j].velY=((q2*z2-q22*z1)/z);
			}
		}

		if(sqrt(pow(strik.posX-coinObject[j].posX, 2)) + pow(strik.posY-coinObject[j].posY, 2) > strik.rad + coinObject[j].rad){

			strik.check();
			coinObject[j].check();	
		}

		coinObject[j].strike(j);
		output(3.2f,1.2f,1,1,1,s);
		//output(5.2f,1.1f,0,0,0,(char*)score);
		coinObject[j].deaccelerate();

	}

	for (i = 0; i < 19; i++)
	{
		if(coinObject[i].velX != 0 && coinObject[i].velY !=0){
			coinActive = 1;
			break; 
		}
		coinActive = 0;

	}		

	if(flagStriker == 1)
		strik.strike();


	if(flagStriker == 1)
		strik.deaccelerate();

	if(strik.velX == 0  && strik.velY==0  && activeStriker == 0 && coinActive == 0){
		strik.reset();
		flagStriker = 0;
		activeStriker = 1;
		strik.drawStriker();
	}

	glutPostRedisplay();

	glutTimerFunc(10, update, 0);
}

/*void rotateBox(int value) {

	if(_angle==90){
		_angle=0;
		return ;
	}
	_angle += 2.0f;
	if (_angle > 90) {
		_angle -= 90;
	}
	glutPostRedisplay();
	glutTimerFunc(10, rotateBox, 0);
}
*/
void arrangeCoin(){

	coinObject[0].posX = 0;
	coinObject[0].posY = 0;

	for ( i = 1; i < 7; i++){
		coinObject[i].posX = 0.235 * cos(DEG2RAD(i*60));
		coinObject[i].posY = 0.235 * sin(DEG2RAD(i*60));		
	}


	for ( i = 7; i < 19; i++){
		coinObject[i].posX = 0.5 * cos(DEG2RAD((i-7)*30));
		coinObject[i].posY = 0.5 * sin(DEG2RAD((i-7)*30));
	}
}
void output(float x, float y, float r, float g, float b, char *string)
{
glColor3f(r, g, b);
glRasterPos2f(x, y);
int len, i;
len = (int)strlen(string);


for (i = 0; i < len; i++) {
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
}
}