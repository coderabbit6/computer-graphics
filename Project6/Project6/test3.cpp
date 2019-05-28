#include<Windows.h>
#include<gl/GL.h>
#include<gl/Glu.h>
#include<gl/glut.h>
#include <math.h>
#include <string>
using namespace std;
GLfloat xangle = 15.0f;
GLfloat yangle = -15.0f;//旋转因子  
class Point2
{
public:
	Point2();
	Point2(float, float,float);
public:
	float x;
	float y;
	float z;
};

Point2::Point2() :x(0), y(0),z(0) {}
Point2::Point2(float xx, float yy,float zz) : x(xx), y(yy),z(zz) {}

class  Node
{
public:
	Point2 point;
	float direction;
	Node() {}
};

GLfloat PI = 3.14;
string way[3]; //提供三种生成规则 
string rule, temprule;

float len; //单步长
//float Alpha;
float Alphay;
float Alphaz;

int n;  ////迭代次数
Point2 pStart(-1,-25,-1); //start point
Node   stack[150];
int    stackpointer;


void LSystemRule()
{
	//初始化
	way[0] = "F[+F]F[-F]F";
	way[1] = "F[+F]F[-F[+F]]";
	way[2] = "FF-[--F+F+F]+[+F+F-F]";
	len = 0.1;
	Alphay = 25;
	Alphaz = 25;
	n = 6;

	stackpointer = 0;
	for (int i = 0; i < 150; i++)
	{
		stack[i].point.x = 0;
		stack[i].direction = 0;
	}
	rule = way[rand() % 3];
	for (int i = 1; i <= n; i++)
	{
		int curlen = temprule.length();
		int pos = 0, j = 0;
		while (j < curlen)
		{
			if (temprule[j] == 'F')
			{
				rule += way[rand() % 3];
				j++;
				pos = rule.length() - 1;
			}
			else
			{
				rule += temprule[j];
				pos++;
				j++;
			}
		}
		temprule = rule;
		//rule.empty();
		rule.clear();
	}
	rule = temprule;
}

void drawGrass()
{
	Node  Nextnode, Curnode;
	Curnode.point.x = pStart.x;
	Curnode.point.y = pStart.y;
	Curnode.point.z = pStart.z;
	Curnode.direction = 270;
	int length = rule.length();
	int  i = 0;
	glColor3f(0.0, 1.0, 0.0);


	while (i < length)
	{
		switch (rule[i])
		{
		case 'F':
			Nextnode.point.x = Curnode.point.x + len * cos(Curnode.direction * PI / 180);
			Nextnode.point.y = Curnode.point.y - len * sin(Curnode.direction * PI / 180);
			Nextnode.point.z = Curnode.point.z - len * cos(Curnode.direction * PI / 180) * sin(Curnode.direction * PI / 180);
			Nextnode.direction = Curnode.direction;
			glBegin(GL_LINES);
			glVertex3f(Curnode.point.x, Curnode.point.y,Curnode.point.z);
			glVertex3f(Nextnode.point.x, Nextnode.point.y, Nextnode.point.z);
			glEnd();
			Curnode = Nextnode;
			break;
		case '[':
			stack[stackpointer] = Curnode;
			stackpointer++;
			break;
		case ']':
			Curnode = stack[stackpointer - 1];
			stackpointer--;
			break;
		case '+':
			Curnode.direction = Curnode.direction + Alphay;
			break;
		case '-':
			Curnode.direction = Curnode.direction - Alphay;
			break;
		default:
			;
		}
		i++;
	}
	glPopMatrix();
}
int sh = 25;
void myInit() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-sh, sh, -sh, sh, -sh, sh);
	LSystemRule();
}
void  display()
{
	// Clear the color and depth buffers.  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glRotatef(xangle, 1.0, 0.0, 0.0);
	glRotatef(yangle, 0.0, -25.0, 0.0);
	/*glOrtho(-sh, sh, -sh, sh, -sh, sh);*/
	drawGrass();

	glFlush();
	glutSwapBuffers();
}

void mySpecialKey(int key, GLint x, GLint y)
{
	if (key == GLUT_KEY_RIGHT)
		yangle += 5.0;
	if (key == GLUT_KEY_LEFT)
		yangle -= 5.0;
	if (key == GLUT_KEY_UP)
		xangle += 5.0;
		//sh -= 0.1;
	if (key == GLUT_KEY_DOWN)
		xangle -= 5.0;
		//sh +=0.1;
	glutPostRedisplay();
}

int main(int args, char** argv) {

	glutInit(&args, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(640,480);

	glutInitWindowPosition(50, 150);

	glutCreateWindow("a function graphics");
	glutDisplayFunc(display);
	glutSpecialFunc(mySpecialKey);
	myInit();
	glutMainLoop();
	return 0;
}