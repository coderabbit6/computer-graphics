#define GLUT_DISABLE_ATEXIT_HACK 
#include<windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include <windows.h>

// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#define MAX_CHAR       128
void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// �����ַ��ĸ���
	// �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
	// ����һ���ֽ���һ���ַ�
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	// ������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// �������ַ�
	for (i = 0; i < len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// ����������ʱ��Դ
	free(wstring);
	glDeleteLists(list, 1);
}

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
						// Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

typedef float Color[3];

//��ȡ���ص����ɫ
void getpixel(GLint x, GLint y, Color color) {
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

//���㺯��
void setpixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
//�Ƚ���ɫ�Ƿ����
int compareColor(Color color1, Color color2) {
	if (color1[0] != color2[0] || color1[1] != color2[1] || color1[2] != color2[2]) { return 0; }
	else { return 1; }
}
//�������
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





void display1() {
	glClear(GL_COLOR_BUFFER_BIT);
	Color fillColor = { 1.0, 1.0, 0.0 };//�����ɫ ��ɫ
	Color boarderColor = { 0.0, 0.0, 0.0 };//�߽���ɫ ��ɫ
	//selectFont(350, ANSI_CHARSET, "Comic Sans MS");
	selectFont(350, ANSI_CHARSET, "����");

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);
	//glBegin(GL_POINTS);
	//for (double i = 0; i < 355; i++) {
	//	glVertex2d(295, i);
	//}
	//glEnd();
	glRasterPos2f(150.0f, 200.0f);
	//drawString("song");
	drawCNString("��");
	glFlush();
	boundaryFill4(250, 265, fillColor, boarderColor);
	boundaryFill4(275, 375, fillColor, boarderColor);
	boundaryFill4(295, 355, fillColor, boarderColor);
	//glFlush();
	glutSwapBuffers();
}
void display2() {
	glClear(GL_COLOR_BUFFER_BIT);
	Color fillColor = { 1.0, 1.0, 0.0 };//�����ɫ ��ɫ
	Color boarderColor = { 0.0, 0.0, 0.0 };//�߽���ɫ ��ɫ
	selectFont(350, ANSI_CHARSET, "����");

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);
	/*glBegin(GL_POINTS);
	for (double i = 0; i < 420; i++) {
		glVertex2d(265, i);
	}
	glEnd();*/
	glRasterPos2f(100.0f, 150.0f);
	//drawString("song");
	drawCNString("��");
	glFlush();
	boundaryFill4(250, 265, fillColor, boarderColor);
	boundaryFill4(265, 410, fillColor, boarderColor);
	boundaryFill4(295, 370, fillColor, boarderColor);
	//glFlush();
	glutSwapBuffers();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("BoundaryFill1");

	glClearColor(0, 0, 0, 0.0);
	glMatrixMode(GL_PROJECTION);//ͶӰģ��
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

	glutDisplayFunc(display2);
	glutMainLoop();
	return 0;
}