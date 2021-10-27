#include <gl/freeglut.h>
#include <bits/stdc++.h>

#define X 0
#define Y 1
#define Z 2


// 大域変数
unsigned int num_points = 8;
double point[][3] = { {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, -1.0, 1.0}, { 1.0, -1.0, 1.0} };

unsigned int window_width, window_height; // ウインドウサイズ用

// 必ず表示する範囲
double init_left = -2.0;
double init_right = 2.0;
double init_bottom = -2.0;
double init_top = 2.0;

// 補正を加えたあとの表示範囲
double left, right, bottom, top;

// カメラ
double eyes[3] = { 2.0, 1.0, 1.0 };
double center[3] = { 0.0, 0.0, 0.0 };
double up[3] = { 0.0, 0.0, 1.0 };

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, -100.0, 100.0); //表示範囲変更
	glViewport(0, 0, window_width, window_height);    // 投影によって得られた画像をウィンドウにはめ込む
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyes[X], eyes[Y], eyes[Z], center[X], center[Y], center[Z], up[X], up[Y], up[Z]);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);                            // これから描く図形のタイプ

	glVertex3dv(point[0]);
	glVertex3dv(point[1]);

	glVertex3dv(point[1]);
	glVertex3dv(point[2]);

	glVertex3dv(point[2]);
	glVertex3dv(point[3]);

	glVertex3dv(point[3]);
	glVertex3dv(point[0]);

	glVertex3dv(point[4]);
	glVertex3dv(point[5]);

	glVertex3dv(point[5]);
	glVertex3dv(point[6]);

	glVertex3dv(point[6]);
	glVertex3dv(point[7]);

	glVertex3dv(point[7]);
	glVertex3dv(point[4]);

	glVertex3dv(point[0]);
	glVertex3dv(point[4]);

	glVertex3dv(point[1]);
	glVertex3dv(point[5]);
	
	glVertex3dv(point[2]);
	glVertex3dv(point[6]);

	glVertex3dv(point[3]);
	glVertex3dv(point[7]);

	glEnd();
	glFlush();
}

void initGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ウインドウの色(RGB), α値(透明度) 黒
}

void resize(int width, int height) // 新しいサイズを取得し記録する
{
	unsigned int i;
	double dx, dy, d_aspect, w_aspect, d;
	double margin;

	// ウインドウサイズの取得
	window_width = width;
	window_height = height;

	// 座標の範囲の読み取り
	init_left = init_bottom = 10000.0;
	init_right = init_top = -10000.0;
	for (i = 0; i < num_points; i++) {
		if (point[i][X] < init_left)
			init_left = point[i][X];
		if (point[i][X] > init_right)
			init_right = point[i][X];
		if (point[i][Y] < init_bottom)
			init_bottom = point[i][Y];
		if (point[i][Y] > init_top)
			init_top = point[i][Y];
	}

	// 周囲を5%だけ広げる
	margin = (init_right - init_left) * 0.05;
	init_left -= margin;
	init_right += margin;
	init_bottom -= margin;
	init_top += margin;

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