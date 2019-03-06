#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<GL/glut.h>
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
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("hello cg");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}