#include <gl/freeglut.h>


//void display(void)                       // イベントのたびにウインドウの中身を描きなおす関数
//{
//	glClear(GL_COLOR_BUFFER_BIT);        // ウインドウを背景色で染める関数
//	glFlush();                           // glClear()関数を確実に実行させるための「おまじない（？）」：強制実行
//}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);         // 色を白に設定
	glBegin(GL_LINES);                   // 間に挟まれた部分で線分を描く

	glVertex3f(  0.5f, 0.5f, 0.0f);      // (0.5, 0.5, 0.0)---(-0.5, 0.5, 0.0)を結ぶ線分の始点
	glVertex3f(- 0.5f, 0.5f, 0.0f);      // 終点

	glVertex3f(- 0.5f,   0.5f, 0.0f);
	glVertex3f(- 0.5f, - 0.5f, 0.0f);

	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);

	glEnd();
	glFlush();
}

void initGL(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // ウインドウの色(RGB), α値(透明度)
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);           // glutライブラリの初期化
	glutInitDisplayMode(GLUT_RGBA);  // 表示に用いるフレームバッファの設定 GLUT_RGBA:ビットごとの論理和 GLUT_DEPTH:デプスバッファ処理に対応
	glutCreateWindow(argv[0]);       // OpenGLによる表示用ウインドウの生成 引数は名前
	glutDisplayFunc(display);        // 表示用コールバック関数の設定 
	initGL();    
	glutMainLoop();					 // イベントの発生を待ち続けるループ関数の一種 ユーザの強制終了まで待機し続ける

	return 0;
}