#include <gl/freeglut.h>

#define X 0
#define Y 1
#define Z 2

unsigned int num_points = 5;
double point[][3] = { {0.5, 0.5, 0.0}, {-0.5, 0.5, 0.0}, {-0.5, -0.5, 0.0}, {0.5, -0.5, 0.0}, {0.0, 0.0, 0.0} };

void display(void)
{
	unsigned int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);                   // これから描く図形のタイプ：点群の描画

	for (i = 0; i < num_points; i++)
		glVertex3d(point[i][X], point[i][Y], point[i][Z]);
	glEnd();
	glFlush();
}

void initGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ウインドウの色(RGB), α値(透明度) 黒
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);           // glutライブラリの初期化
	glutInitDisplayMode(GLUT_RGBA);  // 表示に用いるフレームバッファの設定 GLUT_RGBA:ビットごとの論理和 GLUT_DEPTH:デプスバッファ処理に対応
	glutCreateWindow(argv[0]);       // OpenGLによる表示用ウインドウの生成 引数は名前
	glutDisplayFunc(display);        // 表示用コールバック関数の設定 
	initGL();
	glutMainLoop();                  // イベントの発生を待ち続けるループ関数の一種 ユーザの強制終了まで待機し続ける

	return 0;
}