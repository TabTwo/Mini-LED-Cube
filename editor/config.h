#ifndef _CONFIG_H
#define _CONFIG_H

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define CUBE_SIZE     30
#define MOVE_SPEED    7
#define ZOOM_LEVEL    25

// LEDCube constants
#define NOT_CONNECTED_ERROR    -1
#define DEVICE_NOT_FOUND_ERROR -2

#define SUCCESSFULLY_CONNECTED  1

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
extern GtkWidget *drawingArea;
extern GladeXML *xml;

// Dimensions, positions
extern gfloat light0Pos[];

// LED data
extern gint animation[32][28];
extern gint currentFrame;
extern gint animationLength;

// Connection
extern gboolean isCubeConnected;

#endif

