#include <gl/freeglut.h>

void display(void)                       // ウインドウの中身を描きなおす関数
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void initGL(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // ウインドウの色(RGB), α値(透明度)
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);        // 表示用コールバック関数の設定
	initGL();
	glutMainLoop();
	return 0;
}