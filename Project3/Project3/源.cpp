#include <gl\glut.h>  
#include <gl\GLU.h>
#include <gl\GL.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
//GLint * a, b[1];
const int Width = 600;
const int Height = 600;


typedef float Color[3];
//��ȡ���ص����ɫ
void getpixel(GLint x, GLint y, Color color)
{
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}
//����
void setpixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
//�Ƚ���ɫ�Ƿ����
int compareColor(Color color1, Color color2)
{
	if (color1[0] != color2[0] || color1[1] != color2[1] || color1[2] != color2[2]) { return 0; }
	else { return 1; }
}
//����ͨ�������
void boundaryFill4(int x, int y, Color fillColor, Color boarderColor)
{
	Color interiorColor;
	glColor3fv(fillColor);
	getpixel(x, y, interiorColor);
	if (compareColor(interiorColor, fillColor) == 0 && compareColor(interiorColor, boarderColor) == 0) {
		setpixel(x, y);
		boundaryFill4(x + 1, y, fillColor, boarderColor);
		boundaryFill4(x - 1, y, fillColor, boarderColor);
		boundaryFill4(x, y + 1, fillColor, boarderColor);
		boundaryFill4(x, y - 1, fillColor, boarderColor);
	}
}

void character()
{
	glClear(GL_COLOR_BUFFER_BIT);//���
	glColor3f(0.0f, 0.0f, 0.0f);//����������ɫΪ��ɫ
	glBegin(GL_LINE_LOOP);//����5��gl��������
	glVertex2i(200, 500); glVertex2i(200, 480);
	glVertex2i(240, 480); glVertex2i(240, 460);
	glVertex2i(180, 460); glVertex2i(180, 380);
	glVertex2i(420, 380); glVertex2i(420, 460);
	glVertex2i(360, 460); glVertex2i(360, 480);
	glVertex2i(400, 480); glVertex2i(400, 500);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2i(260, 480); glVertex2i(260, 460);
	glVertex2i(340, 460); glVertex2i(340, 480);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2i(200, 440); glVertex2i(200, 400);
	glVertex2i(240, 400); glVertex2i(240, 440);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2i(260, 440); glVertex2i(260, 400);
	glVertex2i(340, 400); glVertex2i(340, 440);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2i(360, 440); glVertex2i(360, 400);
	glVertex2i(400, 400); glVertex2i(400, 440);
	glEnd();

	glBegin(GL_LINE_LOOP);//����2��gl��������
	glVertex2i(220, 360); glVertex2i(220, 240);
	glVertex2i(240, 240); glVertex2i(240, 340);
	glVertex2i(360, 340); glVertex2i(360, 240);
	glVertex2i(380, 240); glVertex2i(380, 360);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2i(300, 300); glVertex2i(230, 200);
	glVertex2i(244, 186); glVertex2i(293, 256);
	glVertex2i(356, 186); glVertex2i(370, 200);
	glVertex2i(305, 272); glVertex2i(314, 286);
	glEnd();

	// ˢ��
	glFlush();
}

void myDisplay()
{
	Color fillColor = { 0.0, 0.0, 1.0 };//�����ɫ ��ɫ
	Color boarderColor = { 0.0, 0.0, 0.0 };//�߽���ɫ ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	glColor3fv(boarderColor);
	character();
	boundaryFill4(250, 490, fillColor, boarderColor);
	boundaryFill4(240, 250, fillColor, boarderColor);
	boundaryFill4(300, 297, fillColor, boarderColor);
	glFlush();
}

void init(void)
{
	gluOrtho2D(0.0, Width, 0.0, Height);//����һ��ͶӰƽ�棨����x������x������y������y��
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);// ���ô���Ϊ��ɫ
	glMatrixMode(GL_PROJECTION);
}
int main(int argc, char* argv[])
{
	//a = b;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//��ʼ��
	glutInitWindowSize(Width, Height);//���ô��ڵĿ��
	glutCreateWindow("��人��");//�������趨����
	init();
	glutDisplayFunc(&myDisplay);
	glutMainLoop(); // glut�¼�����ѭ��

	return 0;
}
