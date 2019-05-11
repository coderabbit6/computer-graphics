#include<Windows.h>
#include<iostream>
#include<math.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<gl/GLUT.h>
const GLfloat pi = 3.14159;
//set window
void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

//set viewport
void setViewport(GLint left, GLint right, GLint bottom, GLint top) {
	glViewport(left, bottom,right-left, top-bottom);
}

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float cx = 220, cy = 220;
	float H, W = 200, aspect = 1;
	setViewport(100,340, 100, 340);
	setWindow(0, 400, 0, 400);
	//自动裁剪
	for (int i = 0; i <= 1000; i++)
	{
		
		    Sleep(100);
			glClearColor(1.0, 1.0, 1.0, 0.0);
		    //glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_STRIP);
			for (float x = 0; x < 240.0; x++) {
				glVertex2f(x, x);
			}
			for (float x = 0; x < 240.0; x++) {
				glVertex2f(x, -x + 400);
			}
			for (float x = 0; x < 240.0; x++) {
				glVertex2f(x, 100/(x+2));
			}
			glEnd();
			glFlush();
			W *= 0.99;
			H = W * aspect;
			setWindow(cx-W,cx+W,cy-H,cy+H);
			//glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_STRIP);
			for (float x = 0; x < 240.0; x++) {
				glVertex2f(x, x);
			}
			for (float x = 0; x < 240.0; x++) {
				glVertex2f(x, -x+400);
			}
			for (float x = 0; x < 240.0; x++) {
				glVertex2f(x, 100 / (x+2));
			}
			glEnd();
			glutSwapBuffers();
		
	}
}

void mydisplay1() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int R = 20;
	GLdouble t = pi / 3.0;
	float cx = 220, cy = 220;
	float H = 200, W = 200, aspect = 1;
	//setViewport(100, 340, 100, 340);
	setWindow(cx - W, cx + W, cy - H, cy + H);
	//自动裁剪
	double a = 1.1;
	for (int k = 0; k <= 1000; k++)
	{
		a +=0.1;
		Sleep(50);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		W *= 0.99;
		H = W * aspect;
		setWindow(cx - W, cx + W, cy - H, cy + H);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_STRIP);
		for (double j = 0; j <= 10*pi; j+=0.01) {
			glVertex2f(cx+5*j*cos(j*a),cy+5*j*sin(j*a));
		}
		glEnd();
		glFlush();
		//glutSwapBuffers();

	}
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0);
	
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("the test");
	glutDisplayFunc(mydisplay1);
	myInit();
	//setWindow(-5.0, 5.0, -0.3, 1.0);
	//setViewport(0, 640, 0, 480);
	glutMainLoop();
}