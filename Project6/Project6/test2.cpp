#include<Windows.h>
#include<gl/GL.h>
#include<gl/Glu.h>
#include<gl/glut.h>

//--------------------------------
void axis(double length) {
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glEnd();
	glTranslated(0, 0, length - 0.2);
	glutWireCone(0.04, 0.2, 12, 9);
	glPopMatrix();
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0 * 64 / 48.0, 4.0 * 64 / 48, -4.0, 4.0, 0.0, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.0, 2.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glViewport(0, 0, 640, 480);
}
//---------------------------------

//void displayWire(void) {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-2.0)
//}
GLfloat alphaX = 0.0;
GLfloat alphaY = 0.0;
void mySpecialKey(int key, GLint x, GLint y)
{
	if (key == GLUT_KEY_RIGHT)
		alphaX += 5.0;
	if (key == GLUT_KEY_LEFT)
		alphaX -= 5.0;
	if (key == GLUT_KEY_UP)
		alphaY += 5.0;
	if (key == GLUT_KEY_DOWN)
		alphaY -= 5.0;
	glutPostRedisplay();
}
void displayWire()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //background is black
// draw three coordinate axes
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	//	glLoadIdentity();
	glRotated(alphaY, 0.0, 1.0, 0.0);
	glRotated(alphaX, 1.0, 0.0, 0.0);
	glScaled(1.5, 1.5, 1.5);

	glPushMatrix();
	glColor3d(0.0, 0.0, 1.0);
	axis(2.0); //z-axis
	glRasterPos3f(0.0, 0.0, 2.3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Z');

	glRotated(-90, 1.0, 0.0, 0.0);
	glColor3d(0.0, 1.0, 0.0);
	axis(2.0); //y-axis
	glRasterPos3f(0.0, 0.0, 2.3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');

	glColor3d(1.0, 0.0, 0.0);
	glRotated(90, 0.0, 1.0, 0.0);
	axis(2.0); //x-axis
	glRasterPos3f(0.0, 0.0, 2.3);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
	glPopMatrix();

	glColor3d(1.0, 1.0, 0.0);
	glScaled(1.5, 1.5, 1.5);

	glTranslated(0.0, 0.0, 0.0);
	glPushMatrix();			//big cube
	glTranslated(0.5, 0.5, 0.5);
	glutWireCube(1.0);
	glPopMatrix();

	glColor3d(1.0, 1.0, 1.0);
	glPushMatrix();			//cone
	glTranslated(1.0, 0.0, 1.0);
	glRotated(-90, 1, 0, 0);
	glutWireCone(0.25, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();			//sphere
	glTranslated(1.0, 1.0, 0.0);
	glutWireSphere(0.25, 10, 10); //
	glPopMatrix();

	glPushMatrix();			//teapot
	glTranslated(1.0, 1.0, 1.0);
	//glRotated(90, 0.0, 1.0, 0.0);
	glutSolidTeapot(0.25);
	glPopMatrix();
	glPushMatrix();			//torus
	glTranslated(0.0, 1.0, 0.0);
	glRotated(90, 1, 0, 0);
	glutWireTorus(0.1, 0.3, 10, 10);
	glPopMatrix();
	glPushMatrix();			//十二面体
	glTranslated(1.0, 0.0, 0.0);
	glScaled(0.15, 0.15, 0.15);
	glutWireDodecahedron();
	glPopMatrix();
	glPushMatrix();			//small cube
	glTranslated(0.0, 1.0, 1.0);
	glutSolidCube(0.25);
	glPopMatrix();

	glPushMatrix();			//cylinder 
	glRotated(-90.0, 1, 0, 0);
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.25, 0.25, 0.5, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transformation Test -wireFrame");

	glutDisplayFunc(displayWire);

	glutSpecialFunc(mySpecialKey);
	init();

	glutMainLoop();
}