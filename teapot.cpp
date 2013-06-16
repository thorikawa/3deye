#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

/* 光源の定義 */
/*（光の方向，光の色） */
GLfloat lightpos[] = { -1.0, 3.0, 5.0, 0.0 };
GLfloat lightcolor[] = { 1.0, 1.0, 1.0, 1.0 };
/* ティーポットの材質色（緑っぽい） */
/* 物体色，鏡面反射色，鏡面反射の鋭さ */
GLfloat teapotColor[] = { 0.6, 0.8, 0.4, 1.0 };
GLfloat specularcolor[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat shininess[] = { 80 };

double angle = 0;

void draw(void) {
  int i, j, k;
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SPECULAR, specularcolor);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_DIFFUSE, teapotColor);
  glTranslated(-0., -2.00, -3.5);
  glutSolidSphere(0.1, 16, 16);
  glPopMatrix();
  
  glPushMatrix();
  /* ティーポットの反射特性の設定 */
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SPECULAR, specularcolor);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_DIFFUSE, teapotColor);
  /* ちょっと上に上がり，前に傾けてティーポットを描く */
  //glTranslated(0.0, 0.7, 0.0);
  //glRotated(-30, 0.0, 0.0, 1.0);
  glRotatef(angle, 0.0, 1.0, 0.0);
  glutSolidTeapot(0.5);
  
  glPopMatrix();
}

void display(void) {
  // 画面を消去する．奥行きバッファもクリア
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // カメラ画角等の設定
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50, 1.0, 1.0, 100.0);
  // カメラの位置，向きの設定
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.4, 0.0, 2.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
  // 光源位置の設定
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  draw();
  
  glutSwapBuffers();
}

void idle(void) {
  // printf("idle\n");
  // angle += 1.0;  //角度を更新
  glutPostRedisplay(); //再描
}

void keyboard (unsigned char key, int x, int y) {
  if (key == 'f') {
    glutEnterGameMode();
  } else if (key == 'g') {
    printf("leave game mode\n");
    glutLeaveGameMode();
  } else if (key == 27) {
    exit(-1);
  }
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutCreateWindow("title");
  glutInitWindowSize(800,600);
  glutInitWindowPosition(100,100);
  glutFullScreen();
  /* 隠面消去をデプスバッファで行うことと，
   　　　ダブルバッファリングを行うことを指定 */
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE
                      | GLUT_DEPTH);
  //glutGameModeString("800×600:32@60");
  //glutEnterGameMode();
  
  //glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  // 隠面消去を有効にする
  glEnable(GL_DEPTH_TEST);
  // 陰影付けを有効にする
  glEnable(GL_LIGHTING);
  // 光源０を有効にする
  glEnable(GL_LIGHT0);
  // 光源０の色を設定する
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightcolor);
  glutMainLoop();
  return 0;
}