#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <opencv2/opencv.hpp>

/* 光源の定義 */
/*（光の方向，光の色） */
GLfloat lightpos[] = { -1.0, 3.0, 5.0, 0.0 };
GLfloat lightcolor[] = { 1.0, 1.0, 1.0, 1.0 };
/* ティーポットの材質色（緑っぽい） */
/* 物体色，鏡面反射色，鏡面反射の鋭さ */
GLfloat teapotColor[] = { 0.6, 0.8, 0.4, 1.0 };
GLfloat specularcolor[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat shininess[] = { 80 };

#define WIDTH 800
#define HEIGHT 600

double angle = 0;
double eyepos = 0;
int frame = 0;

void draw(void) {
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SPECULAR, specularcolor);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_DIFFUSE, teapotColor);
  glTranslated(-0., -0.60, 0);
  glutSolidSphere(0.1, 16, 16);
  glPopMatrix();
  
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SPECULAR, specularcolor);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_DIFFUSE, teapotColor);
  glRotatef(angle, 0.0, 1.0, 0.0);
  glutSolidTeapot(0.5);
  glPopMatrix();
}

void screenshot (const char* filename) {
  cv::Mat img(HEIGHT, WIDTH, CV_8UC3);
  cv::Mat flipped(HEIGHT, WIDTH, CV_8UC3);
  glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);
  glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
  glReadPixels(0, 0, img.cols, img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);
  cv::flip(img, flipped, 0);
  imwrite(filename, flipped);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50, 1.0, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  char filename[256];
  if (frame == 0) {
    gluLookAt(eyepos, 0.0, 2.0,
              0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    sprintf(filename, "right.jpg");
  } else if (frame == 1) {
    gluLookAt(-eyepos, 0.0, 2.0,
              0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    sprintf(filename, "left.jpg");
  } else {
    exit(-1);
  }
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  draw();
  glutSwapBuffers();

  screenshot(filename);
  
  frame++;
}

void idle(void) {
  glutPostRedisplay();
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
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow("title");
  //glutFullScreen();
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE
                      | GLUT_DEPTH);
  if (argc > 1) {
    printf("%s\n", argv[1]);
    eyepos = atof(argv[1]);
  }

  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightcolor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightcolor);
  glutMainLoop();
  return 0;
}
