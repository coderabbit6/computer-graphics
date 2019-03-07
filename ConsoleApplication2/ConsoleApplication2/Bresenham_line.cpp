#include<Windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<GL/glut.h>
#include<math.h>
#include"Point.h"
const int screenWidth = 640;
const int screenHight = 480;
//struct Point
//{
//	double x, y;
//};

Point A = Point(220.0, 75.0);
Point B = Point(420.0, 75.0);
Point C = Point(420.0, 150.0);
Point D = Point(420.0, 350.0);
Point E = Point(370.0, 420.0);
Point F = Point(270.0, 420.0);
Point G = Point(220.0, 350.0);
Point H = Point(220.0, 150.0);
Point O = Point(320.0, 275.0);
double r = 75.0;


void myInit2() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(screenWidth), 0.0, GLdouble(screenHight));

}


void lineto(Point M,Point N) {
	Point p, t;
	if (fabs(M.x - N.x) < 1e-6) {//绘制垂线
		if (M.y > N.y) {
			t = M;
			M = N;
			N = t;
		}
		glBegin(GL_POINTS);
		for (p = M; p.y < N.y; p.y++) {
			glVertex2d(p.x, p.y);
		}
		glEnd();
		glFlush();
	}

	else {
		double k, d;          //k是直线斜率，d为中点误差项
		k = (N.y - M.y) / (N.x - M.x);
		if (k > 1.0)              //绘制k>1
		{
			if (M.y > N.y) {
				t = M;
				M = N;
				N = t;
			}
			d = 1 - 0.5 * k;
			glBegin(GL_POINTS);
			for (p = M; p.y < N.y; p.y++) {
				glVertex2d(p.x, p.y);
				if (d >= 0) {
					p.x++;
					d += 1 - k;
				}
				else d += 1;
			}
			glEnd();
			glFlush();
		}  
		if (0.0 <= k && k <= 1.0) {       //绘制0<=k<=1
			if (M.x > N.x) {
				t = M;
				M = N;
				N = t;
			}
			d = 0.5 - k;
			glBegin(GL_POINTS);
			for (p = M; p.x < N.x; p.x++) {
				glVertex2d(p.x, p.y);
				if (d < 0) {
					p.y++;
					d += 1 - k;
				}
				else
					d -= k;
			}
			glEnd();
			glFlush();
		}
		if (k >= -1.0 && k < 0.0) {      //绘制-1<=k<0
			if (M.x > N.x) {
				t = M;
				M = N;
				N = t;
			}
			d = -0.5 - k;
			glBegin(GL_POINTS);
			for (p = M; p.x < N.x; p.x++) {
				glVertex2d(p.x, p.y);
				if (d > 0) {
					p.y--;
					d -= 1 + k;
				}
				else d -= k;
			}
			glEnd();
			glFlush();
		}
		if (k < -1.0) {             //绘制k<-1
			if (M.y < N.y) {
				t = M;
				M = N;
				N = t;
			}
			d = -1 - 0.5 * k;
			glBegin(GL_POINTS);
			for (p = M; p.y > N.y; p.y--) {
				glVertex2d(p.x, p.y);
				if (d < 0) {
					p.x++;
					d -= 1 + k;
				}
				else d -= 1;
			}
		}
	}
}

void circle(Point o,double r) {
	Point p;
	o.y = o.y + r;
	double d;
	d = 1.25-r;
	glBegin(GL_POINTS);
	for (p = o; p.x < (o.x + sqrt(2)*r*0.5); p.x++) {
		glVertex2d(p.x, p.y);
		glVertex2d(640-p.x, p.y);
		glVertex2d(640-p.x, 550-p.y);
		glVertex2d(p.x, 550-p.y);
		glVertex2d(p.x+45,p.y-45);
		glVertex2d(395-p.x, p.y-45);
		glVertex2d(395 - p.x, 595-p.y);
		glVertex2d(p.x + 45, 595 - p.y);
		if (d >= 0) {
			p.y--;
			d += 2 * (p.x - p.y-45) + 5;
		}
		else d += 2 * (p.x-320) + 3;
	}

	glEnd();
	glBegin(GL_POINTS);
	glVertex2d(o.x, o.y);
	glEnd();
	glFlush();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	lineto(A, B);
	lineto(B, D);
	lineto(D, E);
	lineto(E, F);
	lineto(F, G);
	lineto(G, A);
	//lineto(C, H);
	lineto(D, G);
	circle(O,r);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (double i = 0; i <= 300; i++) {
		glVertex2d(20.0, i);
	}
	glEnd();
	glFlush();
}
int main(int args,char** argv) {
	glutInit(&args, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHight);
	glutInitWindowPosition(50, 150);
	glutCreateWindow("draw a line");
	glutDisplayFunc(draw);
	myInit2();
	glutMainLoop();
}


