#include <gl/freeglut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void initGL(void)
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	initGL();
	glutMainLoop();
	return 0;
}