#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <opencv2/opencv.hpp>

GLfloat lightpos[] = { -1.0, 3.0, 5.0, 0.0 };
GLfloat lightcolor[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat teapotColor[] = { 0.6, 0.8, 0.4, 1.0 };
GLfloat specularcolor[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat shininess[] = { 80 };

#define WIDTH 800
#define HEIGHT 600

double angle = 0;
double eyepos = 0;

void screenshot (const char* filename) {
  cv::Mat img(HEIGHT, WIDTH, CV_8UC3);
  cv::Mat flipped(HEIGHT, WIDTH, CV_8UC3);
  glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);
  glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
  glReadPixels(0, 0, img.cols, img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);
  cv::flip(img, flipped, 0);
  imwrite(filename, flipped);
}

void drawSolidShape (double a, double b, double c, double x, double y, double z) {
  GLdouble vertex[][3] = {
    { -a/2.0, -b/2.0, -c/2.0 },
    {  a/2.0, -b/2.0, -c/2.0 },
    {  a/2.0,  b/2.0, -c/2.0 },
    { -a/2.0,  b/2.0, -c/2.0 },
    { -a/2.0, -b/2.0,  c/2.0 },
    {  a/2.0, -b/2.0,  c/2.0 },
    {  a/2.0,  b/2.0,  c/2.0 },
    { -a/2.0,  b/2.0,  c/2.0 }
  };
  int face[][4] = {
    { 3, 2, 1, 0 },
    { 1, 2, 6, 5 },
    { 4, 5, 6, 7 },
    { 0, 4, 7, 3 },
    { 0, 1, 5, 4 },
    { 2, 3, 7, 6 }
  };
  GLdouble normal[][3] = {
    { 0.0, 0.0, -1.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    {-1.0, 0.0, 0.0 },
    { 0.0,-1.0, 0.0 },
    { 0.0, 1.0, 0.0 }
  };
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SPECULAR, specularcolor);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT_AND_BACK,
               GL_DIFFUSE, teapotColor);
  glTranslated( x, y, z);
  glBegin(GL_QUADS);
  for (int j = 0; j < 6; ++j) {
    glNormal3dv(normal[j]);
    for (int i = 0; i < 4; ++i) {
      glVertex3dv(vertex[face[j][i]]);
    }
  }
  glEnd();
  glPopMatrix();
}

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
  glRotatef(-10, 0.0, 1.0, 0.0);
  drawSolidShape(0.3, 0.3, 2.3, -0.4, 0, 0);
  drawSolidShape(0.3, 0.3, 2.3, 0.0, 0, 0);
  drawSolidShape(0.3, 0.3, 2.3, 0.4, 0, 0);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-100, 0.0, 1.0, 0.0);
  drawSolidShape(0.1, 0.1, 3.3, -0.4, 0, 0);
  drawSolidShape(0.1, 0.1, 3.3, 0.0, 0, 0);
  drawSolidShape(0.1, 0.1, 3.3, 0.4, 0, 0);
  drawSolidShape(0.1, 0.1, 3.3, 0.8, 0, 0);
  glPopMatrix();
}

int frame = 0;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50, 1.0, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  char filename[256];
  if (frame == 0) {
    gluLookAt(eyepos-0.1, 1.0, 2.0,
              -0.1, 0.0, 0.0,
              0.0, 1.0, 0.0);
    sprintf(filename, "playland_r.jpg");
  } else if (frame == 1) {
    gluLookAt(-eyepos-0.1, 1.0, 2.0,
              -0.1, 0.0, 0.0,
              0.0, 1.0, 0.0);
    sprintf(filename, "playland_l.jpg");
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