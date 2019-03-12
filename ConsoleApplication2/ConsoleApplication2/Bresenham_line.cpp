#include<Windows.h>
#include <windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<GL/glut.h>
#include<math.h>
#include"Point.h"
#include <time.h>
#include <stdio.h> 
#include <iostream>
#include <stdlib.h>
using namespace std;
//窗口大小
const int screenWidth = 640;
const int screenHight = 480;
#define MAX_CHAR 128
double pi = 3.1415926;

void run();
void drawString(const char* str);
Point A = Point(220.0, 75.0);
Point B = Point(420.0, 75.0);
Point C = Point(420.0, 150.0);
Point D = Point(420.0, 400.0);
Point E = Point(370.0, 470.0);
Point F = Point(270.0, 470.0);
Point G = Point(220.0, 400.0);
Point H = Point(220.0, 150.0);
Point O = Point(320.0, 275.0);
double r = 75.0;
Point m1 = Point(O.x-r/2.0,O.y+r/2*sqrt(3));
Point m2 = Point(O.x + r / 2.0, O.y + r / 2 * sqrt(3));
Point m3 = Point(O.x - r / 2.0, O.y - r / 2 * sqrt(3));
Point m4 = Point(O.x + r / 2.0, O.y - r / 2 * sqrt(3));
void lineto(Point M, Point N) {
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
			glEnd();
			glFlush();
		}
	}
}

//初始化
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(screenWidth), 0.0, GLdouble(screenHight)); //设置为左下角为为坐标原点
	//gluOrtho2D(-0.5* GLdouble(screenWidth), 0.5*GLdouble(screenWidth), -0.5 * GLdouble(screenHight), 0.5 * GLdouble(screenHight));

}
//画刻度
void drawgreed() {
	double x1, x2, y1, y2;
	double m = 3.141592 * 1 / 30;
	for (int i = 0; i <= 60; i++) {
		x1 = 320 + (r - 5) * sin(m * double(i));
		y1 = 275 + (r - 5) * cos(m * double(i));
		x2 = 320 + r * sin(m * double(i));
		y2 = 275 + r * cos(m * double(i));
		if (i % 5 == 0) {
			x1 = 320 + (r - 10) * sin(m * double(i));
			y1 = 275 + (r - 10) * cos(m * double(i));
		}
		
		Point p1 = Point(x1, y1);
		Point p2 = Point(x2, y2);
		lineto(p1,p2);
	}
}

//绘制钟的外圆
void circle(Point o,double r) {   //扫描转化法画圆
	//由于没有设置坐标系，圆的算法是根据圆心坐标重新推导的，没有参数化，只能在一个地方画圆。
	Point p = o;
	o.y = o.y + r;
	double d;
	d = 1.25-r;
	glBegin(GL_POINTS);
	glVertex2d(p.x, p.y);
	for (p = o; p.x < (o.x + sqrt(2)*r*0.5); p.x++) {
		glVertex2d(p.x, p.y);
		glVertex2d(640-p.x, p.y);
		glVertex2d(640-p.x, 550-p.y);
		glVertex2d(p.x, 550-p.y);
		glVertex2d(p.y+45,p.x-45);
		glVertex2d(p.y + 45, 595-p.x);
		glVertex2d(595 - p.y,595 - p.x);
		glVertex2d(595-p.y, p.x-45);
		if (d >= 0) {
			p.y--;
			d += 2 * (p.x - p.y-45) + 5;
		}
		else d += 2 * (p.x-320) + 3;
	}
	glEnd();

	//钟表上刻度的数字
	glRasterPos2f(312.0f, 332.0f);
	drawString("12");
	glRasterPos2f(375.0f, 270.0f);
	drawString("3");
	glRasterPos2f(316.0f, 209.0f);
	drawString("6");
	glRasterPos2f(255.0f, 270.0f);
	drawString("9");
	glFlush();
}

void drawString(const char* str) //屏幕显示字体

{

	static int isFirstCall = 1;

	static GLuint lists;



	if (isFirstCall) {

		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号

		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中

		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);

	}

	// 调用每个字符对应的显示列表，绘制每个字符

	for (; *str != '\0'; ++str) {

		glCallList(lists + *str);

	}

}

//填充外围修饰座钟
void rim() {
	glColor3f(0.411, 0.4110, 0.4110);//设置成银灰色

	//外围填充
	for (int i = 0; i < 90; i++) {
		m1 = Point(O.x - r * cos(pi / 180 * i), O.y + r * sin(pi / 180 * i));
		m2 = Point(O.x + r * cos(pi / 180 * i), O.y + r * sin(pi / 180 * i));
		m3 = Point(O.x - r * cos(pi / 180 * i), O.y - r * sin(pi / 180 * i));
		m4 = Point(O.x + r * cos(pi / 180 * i), O.y - r * sin(pi / 180 * i));
		lineto(m1, G);
		lineto(m2, D);
		lineto(m3, H);
		lineto(m4, C);
	}
}

//绘制钟摆
void pendulum(double x,double y) {
	
	Point d = Point(320, 200);
	Point d1 = Point(x, y);
	glColor3f(0.0, 0.0, 0.0);

	//画出当前摆
	lineto(d,d1);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 100; i++) {
		
		glVertex2d(d1.x + 10 * sin(i*pi / 50.0),d1.y+10*cos(i*pi/50.0));
		
	}
	glEnd();
	glFlush();


	Sleep(50);

	//清除原来的摆
	glColor3f(1.0, 1.0, 1.0);
	lineto(d, d1);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 100; i++) {

		glVertex2d(d1.x + 10 * sin(i * pi / 50.0), d1.y + 10 * cos(i * pi / 50.0));

	}
	glEnd();
	glFlush();
}

//运行时钟
void run() {
	int count = 0;   //钟摆标记
	double h, n, s;  //时针，分针，秒针
	while (true)    //一直运行
	{
		SYSTEMTIME sys;           //获取系统时间
		GetLocalTime(&sys);
		h = sys.wHour;
		n = sys.wMinute;
		s = sys.wSecond;
		double x_s, y_s;//秒针
		double x_m, y_m;//分针
		double x_h, y_h;//时针
		double m = 3.141592 * 1 / 30;  //时钟上一个刻度所对应的弧度

		//秒针，分针，时针尾端坐标
		x_s = 320 + (r - 19) * sin(m * double(s));
		y_s = 275 + (r - 19) * cos(m * double(s));
		x_m = 320 + (r - 25) * sin(m * double(n));
		y_m = 275 + (r - 25) * cos(m * double(n));
		x_h = 320 + (r - 45) * sin(m * double(h)+1/12.0*m*double(n));
		y_h = 275 + (r - 45) * cos(m * double(h)+1 / 12.0 * m * double(n));
		Point P = Point(x_s, y_s);
		Point P1 = Point(x_m, y_m);
		Point P2 = Point(x_h, y_h);

		//秒针为红色，1.5像素
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(1.5);
		lineto(O, P);
		//分针，时针分别为2，3像素像素
		glColor3f(0.0, 0.0, 0.0);
		glPointSize(2.0);
		lineto(O, P1);
		glPointSize(3.0);
		lineto(O, P2);
		

		//Sleep(1000);
		//根据摆确定时间
		//钟摆运动
		for (double i = 0; i < 1; i+=0.05) {
			
			double x = 320 + 4.5*(50 * i - 50 * i * i);  //模拟自由落体，右侧
			double y = 200 - sqrt(10000 - pow((x-320),2)); 
			double x1 = 320 - 4.5*(50 * i - 50 * i * i); //左侧
			if (count % 2 == 1) {  //右侧摆
				pendulum(x, y);
			}
			else pendulum(x1, y);  //左侧摆
		}
		count++; //标记变化

		//清除原来的指针，用白色覆盖
		glColor3f(1.0, 1.0, 1.0);
		glPointSize(1.5);
		lineto(O, P);
		glPointSize(2.0);
		lineto(O, P1);
		glPointSize(3.0);
		lineto(O, P2);
		
	}
}

//主绘图函数
void draw() {                   //绘图主函数
	glClear(GL_COLOR_BUFFER_BIT);       //清屏
	glColor3f(0.0, 0.0, 0.0);           //设置绘图颜色

	//画出座钟边框
	lineto(A, B);
	lineto(B, D);
	lineto(D, E);
	lineto(E, F);
	lineto(F, G);
	lineto(G, A);
	lineto(D, G);
	rim();


	circle(O, r);     //画出座钟

	drawgreed();     //画出钟摆

	run();           //时间流逝，指针运行
}

//主函数
int main(int args,char** argv) {
	glutInit(&args, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHight);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("a desk clock");
	glutDisplayFunc(draw);
	myInit();
	glutMainLoop();
}