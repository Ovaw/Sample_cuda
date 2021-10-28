#include <gl/freeglut.h>
#include <bits/stdc++.h>
#include <math.h>

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
double eye[3] = { 2.0, 1.0, 1.0 };
double center[3] = { 0.0, 0.0, 0.0 };
double up[3] = { 0.0, 0.0, 1.0 };

// 2本のベクトルvec0とvec1の内積
double dot(double vec0[], double vec1[])
// double vec0[];
// double vec1[];
{
	return(vec0[X] * vec1[X] + vec0[Y] * vec1[Y] + vec0[Z] * vec1[Z]);
}

// 2本のベクトルvec0とvec1の外積
void cross(double vec0[], double vec1[], double vec2[])
// double vec0[]
// double vec1[]
// double vec2[]
{
	vec2[X] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
	vec2[Y] = vec0[Z] * vec1[X] - vec0[X] * vec1[Z];
	vec2[Z] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];
}

// ベクトルの正規化
void normVec(double vec[])
// double vec[]; 注意！このベクトルは破壊的に変更される
{
	double norm;
	norm = sqrt(vec[X] * vec[X] + vec[Y] * vec[Y] + vec[Z] * vec[Z]);
	vec[X] /= norm;
	vec[Y] /= norm;
	vec[Z] /= norm;
}

void defineViewMatrix(void)
{
	unsigned int i, j;
	double x_axis[3], y_axis[3], z_axis[3], vec[3];
	double left, right, bottom, top, farVal, nearVal, margin;
	double dx, dy, d_aspect, w_aspect, d;

	// 視点を原点とする座標系の定義
	for (i = 0; i < 3; i++)
		z_axis[i] = eye[i] - center[i];
	normVec(z_axis);
	cross(up, z_axis, x_axis);
	normVec(x_axis);
	cross(z_axis, x_axis, y_axis);

	// left, right, bottom, top, nearVal, farValの決定
	left = bottom = farVal = 10000.0;
	right = top = nearVal = -10000.0;
	for (i = 0; i < num_points; i++) {
		for (j = 0; j < 3; j++)
			vec[j] = point[i][j] - eye[j];
		if (dot(x_axis, vec) < left)
			left = dot(x_axis, vec);
		if (dot(x_axis, vec) > right)
			right = dot(x_axis, vec);
		if (dot(y_axis, vec) < bottom)
			bottom = dot(y_axis, vec);
		if (dot(y_axis, vec) > top)
			top = dot(y_axis, vec);
		if (dot(z_axis, vec) < farVal)
			farVal = dot(z_axis, vec);
		if (dot(z_axis, vec) > nearVal)
			nearVal = dot(z_axis, vec);
	}

	// 図形の周囲に5%ほど余裕を与える
	margin = (right - left) * 0.05;
	left -= margin;
	right += margin;
	margin = (top - bottom) * 0.05;
	bottom -= margin;
	top += margin;
	margin = (nearVal - farVal) * 0.05;
	farVal -= margin;
	nearVal += margin;

	// 表示範囲のアスペクト比とウインドウのアスペクト比の比較
	dx = right - left;
	dy = top - bottom;
	d_aspect = dy / dx;
	w_aspect = (double)window_height / (double)window_width;

	// ウィンドウが表示範囲よりも縦長．範囲表示を縦に広げる
	if (w_aspect > d_aspect) {
		d = (dy * (w_aspect / d_aspect - 1.0)) * 0.5;
		bottom -= d;
		top += d;
	}

	// ウィンドウが表示範囲よりも横長．表示範囲を横に広げる
	else {
		d = (dx * (d_aspect / w_aspect - 1.0)) * 0.5;
		left -= d;
		right+= d;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, - nearVal, - farVal); //表示範囲変更
	glViewport(0, 0, window_width, window_height);    // 投影によって得られた画像をウィンドウにはめ込む
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[X], eye[Y], eye[Z], center[X], center[Y], center[Z], up[X], up[Y], up[Z]);
}

void display(void)
{
	// 正射影の定義
	defineViewMatrix();

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
	// ウインドウサイズの取得
	window_width = width;
	window_height = height;
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