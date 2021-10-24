#include <gl/freeglut.h>
#include <bits/stdc++.h>

#define X 0
#define Y 1
#define Z 2

unsigned int num_points = 5;
double point[][3] = { {1.3, 1.3, 0.0}, {0.3, 1.3, 0.0}, {0.3, 0.3, 0.0}, {1.3, 0.3, 0.0}, {0.8, 0.8, 0.0} };

unsigned int window_width, window_height; // ウインドウサイズ用大域変数

// 必ず表示する範囲の大域変数
double init_left = -2.0;
double init_right = 2.0;
double init_bottom = -2.0;
double init_top = 2.0;

// 補正を加えたあとの表示範囲の大域変数
double left, right, bottom, top;

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, -100.0, 100.0); //表示範囲変更
	glViewport(0, 0, window_width, window_height);    // 投影によって得られた画像をウィンドウにはめ込む
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);                            // これから描く図形のタイプ：三角形の描画
	
	//glColor3f(0.1f, 0.1f, 0.1f); // 背景色	1
	//glVertex3f(left, top, 0.0f);
	//glVertex3f(right, top, 0.0f);
	//glVertex3f(left, bottom, 0.0f);

	//glColor3f(0.1f, 0.1f, 0.1f); // 背景色2
	//glVertex3f(right, top, 0.0f);
	//glVertex3f(left, bottom, 0.0f);
	//glVertex3f(right, bottom, 0.0f);


	glColor3f(1.0f, 0.0f, 0.0f);  // 着色 赤
	glVertex3dv(point[0]);        // glVertex3dv() 座標配列のポインタで指定
	glVertex3dv(point[1]);
	glVertex3dv(point[4]);

	glColor3f(0.0f, 1.0f, 0.0f);  // 緑
	glVertex3dv(point[1]);
	glVertex3dv(point[2]);
	glVertex3dv(point[4]);

	glColor3f(0.0f, 0.0f, 1.0f);  // 青
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

void resize(int width, int height) // 新しいサイズを取得し記録する
{
	double dx, dy, d_aspect, w_aspect, d;

	// ウインドウサイズの取得
	window_width  = width;
	window_height = height;

	// 表示範囲のアスペクト比とウィンドウのアスペクト比の比較
	dx = init_right - init_left;
	dy = init_top - init_bottom;
	d_aspect = dy / dx;
	w_aspect = (double)window_height / (double)window_width;

	// ウィンドウが表示範囲よりも縦長，表示範囲を縦に広げる
	if (w_aspect > d_aspect) {
		d = (dy * (w_aspect / d_aspect - 1.0)) * 0.5;
		left = init_left;
		right = init_right;
		bottom = init_bottom - d;
		top = init_top + d;
	} 
	// ウインドウが表示範囲よりも横長，表示範囲を横に広げる
	else {
		d = (dy * (d_aspect / w_aspect - 1.0)) * 0.5;
		left = init_left - d;
		right = init_right + d;
		bottom = init_bottom;
		top = init_top;
	}
}

int main(int argc, char* argv[])
{
	glutInitWindowPosition(128, 128); // ウインドウ位置指定（左上隅）
	glutInitWindowSize(768, 768);     // ウインドウサイズ指定
	glutInit(&argc, argv);            // glutライブラリの初期化
	glutInitDisplayMode(GLUT_RGBA);   // 表示に用いるフレームバッファの設定 GLUT_RGBA:ビットごとの論理和 GLUT_DEPTH:デプスバッファ処理に対応
	glutCreateWindow(argv[0]);        // OpenGLによる表示用ウインドウの生成 引数は名前
	glutDisplayFunc(display);         // 表示用コールバック関数の設定 
	glutReshapeFunc(resize);
	initGL();
	glutMainLoop();                   // イベントの発生を待ち続けるループ関数の一種 ユーザの強制終了まで待機し続ける

	return 0;
}