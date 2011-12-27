#ifndef _CONFIG_H
#define _CONFIG_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define CUBE_SIZE     30
#define MOVE_SPEED    7
#define ZOOM_LEVEL    25

// Poor Man's enums
#define TOP_ORIENTATION   0x01
#define SIDE_ORIENTATION  0x02

#define RENDER_MODE       0x01
#define PICKING_MODE      0x02

// Materials
extern gfloat ledOnMaterial[];
extern gfloat ledOffMaterial[];
extern gfloat wireMaterial[];
extern gfloat innerWireMaterial[];
extern gfloat backgroundColor[];

// Movement
extern gfloat lookX, lookZ;
extern gfloat eyePos, eyeAngle;
extern gint ledOrientation;

// Objects
extern GLUquadricObj *quadric;
extern GdkGLConfig *glConfig;
extern GdkGLWindow *glWindow;
extern GdkGLContext *glContext;

// Dimensions, positions
extern gfloat light0Pos[];

// LED data
extern gint currentFrame[27];

#endif

