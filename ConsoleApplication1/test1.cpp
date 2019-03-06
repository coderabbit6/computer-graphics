#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<GL/glut.h>
#include<math.h>
const int screenWidth = 640;
const int screenHight = 480;
GLdouble A, B, C, D;
void myInit2() {
	glClearColor(1.0, 1.0, 1.0,0.0);
	glColor3f(0.0,0.0,0.0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,GLdouble(screenWidth),0.0,GLdouble(screenHight));

	A = screenWidth / 4.0;
	B = 0.0;
	C = D = screenHight / 2.0;
}

void myDisplay2() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (GLdouble x = 0; x < 4.0; x += 0.001) {
		GLdouble func = exp(-x) * cos(2 * 3.14159265 * x);
		glVertex2d(A * x + B, C * func + D);
	}
	glEnd();
	glFlush();
}

void myInit() {
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0, 0, 0);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glVertex2d(100,50);
	glVertex2d(100,150);
	glVertex2d(150, 70);
	for (double i = 0; i < 100; i++) {
		glVertex2d(300, i);
	}
	glEnd();
	glFlush();
}



void main(int args, char** argv) {
	glutInit(&args, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHight);
	glutInitWindowPosition(50, 150);
	//glutCreateWindow("hello cg");
	//glutDisplayFunc(myDisplay);
	//myInit();
	glutCreateWindow("a function graphics");
	glutDisplayFunc(myDisplay2);
	myInit2();
	glutMainLoop();
}