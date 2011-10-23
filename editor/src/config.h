#ifndef _CONFIG_H
#define _CONFIG_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define CUBE_SIZE     30
#define MOVE_SPEED    7
#define ZOOM_LEVEL    25

#define PI            3.1415926535897932

#define TOP_ORIENTATION  1
#define SIDE_ORIENTATION 2

// Materials
extern float ledOnMaterial[];
extern float ledOffMaterial[];
extern float wireMaterial[];
extern float innerWireMaterial[];

// Movement
extern float lookX, lookZ;
extern float eyePos, eyeAngle;

// Objects
extern GLUquadricObj *quadric;

#endif

