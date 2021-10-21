#include <gl/freeglut.h>

#define X 0
#define Y 1
#define Z 2

unsigned int num_points = 5;
double point[][3] = { {1.3, 1.3, 0.0}, {0.3, 1.3, 0.0}, {0.3, 0.3, 0.0}, {1.3, 0.3, 0.0}, {0.8, 0.8, 0.0} };

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -100.0, 100.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);          // これから描く図形のタイプ：三角形の描画

	glColor3f(1.0f, 0.0f, 0.0f);    // 着色 赤
	glVertex3dv(point[0]);          // glVertex3dv() 座標配列のポインタで指定
	glVertex3dv(point[1]);
	glVertex3dv(point[4]);

	glColor3f(0.0f, 1.0f, 0.0f);    // 緑
	glVertex3dv(point[1]);
	glVertex3dv(point[2]);
	glVertex3dv(point[4]);

	glColor3f(0.0f, 0.0f, 1.0f);    // 青
	glVertex3dv(point[2]);
	glVertex3dv(point[3]);
	glVertex3dv(point[4]);

	glEnd();
	glFlush();
}

void initGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ウインドウの色(RGB), α値(透明度) 黒
}

int main(int argc, char* argv[])
{
	glutInitWindowPosition(128, 128); // ウインドウ位置指定（左上隅）
	glutInitWindowSize(768, 768);     // ウインドウサイズ指定
	glutInit(&argc, argv);            // glutライブラリの初期化
	glutInitDisplayMode(GLUT_RGBA);   // 表示に用いるフレームバッファの設定 GLUT_RGBA:ビットごとの論理和 GLUT_DEPTH:デプスバッファ処理に対応
	glutCreateWindow(argv[0]);        // OpenGLによる表示用ウインドウの生成 引数は名前
	glutDisplayFunc(display);         // 表示用コールバック関数の設定 
	initGL();
	glutMainLoop();                   // イベントの発生を待ち続けるループ関数の一種 ユーザの強制終了まで待機し続ける

	return 0;
}