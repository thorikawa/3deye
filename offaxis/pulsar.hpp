#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <glut.h>
#include "glcv.hpp"

typedef struct {
    double x,y,z;
} XYZ;
typedef struct {
    double r,g,b;
} COLOUR;
typedef struct {
    unsigned char r,g,b,a;
} PIXELA;
typedef struct {
    XYZ vp;              /* View position           */
    XYZ vd;              /* View direction vector   */
    XYZ vu;              /* View up direction       */
    XYZ pr;              /* Point to rotate about   */
    double focallength;  /* Focal Length along vd   */
    double aperture;     /* Camera aperture         */
    double eyesep;       /* Eye separation          */
    int screenwidth,screenheight;
} CAMERA;

int start (int argc, char *argv[]);
void Display(void);
void CreateEnvironment(void);
void MakeGeometry(void);
void MakeLighting(void);
void HandleKeyboard(unsigned char key,int x, int y);
void HandleSpecialKeyboard(int key,int x, int y);
void HandleMouse(int,int,int,int);
void HandleMainMenu(int);
void HandleSpeedMenu(int);
void HandleSpinMenu(int);
void HandleVisibility(int vis);
void HandleReshape(int,int);
void HandleMouseMotion(int,int);
void HandlePassiveMotion(int,int);
void HandleIdle(void);
void GiveUsage(char *);
void RotateCamera(int,int,int);
void TranslateCamera(int,int);
void CameraHome(int);
void Normalise(XYZ *);
XYZ  CalcNormal(XYZ,XYZ,XYZ);
