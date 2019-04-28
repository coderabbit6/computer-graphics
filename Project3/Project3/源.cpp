#define GLUT_DISABLE_ATEXIT_HACK 
#include<windows.h>

#include<GL/glut.h>

#include<GL/gl.h>

typedef float Color[3];

//获取像素点的颜色
void getpixel(GLint x, GLint y, Color color) {
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

//画点函数
void setpixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
//比较颜色是否相等
int compareColor(Color color1, Color color2) {
	if (color1[0] != color2[0] || color1[1] != color2[1] || color1[2] != color2[2]) { return 0; }
	else { return 1; }
}
//种子填充
void boundaryFill4(int x, int y, Color fillColor, Color boarderColor) {
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

void boundaryFill8(int x, int y, Color fillColor, Color boarderColor) {
	Color interiorColor, a, b, c, d;
	getpixel(x, y, interiorColor);
	getpixel(x + 1, y - 1, a);
	getpixel(x, y - 1, b);
	getpixel(x, y + 1, c);
	getpixel(x - 1, y, d);
	int i = 0;
	if (compareColor(a, boarderColor) == 1) i++;
	if (compareColor(b, boarderColor) == 1) i++;
	if (compareColor(c, boarderColor) == 1) i++;
	if (compareColor(d, boarderColor) == 1) i++;
	if (i <= 1) {
		if (compareColor(interiorColor, fillColor) == 0 && compareColor(interiorColor, boarderColor) == 0) {
			setpixel(x, y);
			boundaryFill8(x + 1, y, fillColor, boarderColor);
			boundaryFill8(x, y - 1, fillColor, boarderColor);
			boundaryFill8(x - 1, y, fillColor, boarderColor);
			boundaryFill8(x, y + 1, fillColor, boarderColor);
			boundaryFill8(x + 1, y - 1, fillColor, boarderColor);
			boundaryFill8(x - 1, y - 1, fillColor, boarderColor);
			boundaryFill8(x - 1, y + 1, fillColor, boarderColor);
			boundaryFill8(x + 1, y + 1, fillColor, boarderColor);
		}
	}
}

//////////////////////////////////////////////
void polygon()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);//以下5个gl函数画西
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

	glBegin(GL_LINE_LOOP);//以下2个gl函数画贝
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

	glFinish();
}

void display(void) {
	Color fillColor = { 1.0, 1.0, 0.0 };//填充颜色 蓝色
	Color boarderColor = { 0.0, 1.0, 0.0 };//边界颜色 绿色
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	glColor3fv(boarderColor);
	polygon();

	//boundaryFill4(222, 358, fillColor, boarderColor);
	boundaryFill4(300, 350, fillColor, boarderColor);
	boundaryFill4(300, 297, fillColor, boarderColor);


	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("BoundaryFill1");

	glClearColor(0, 0, 0, 0.0);
	glMatrixMode(GL_PROJECTION);//投影模型
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
