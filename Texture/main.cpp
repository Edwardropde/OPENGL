#include<bits/stdc++.h>
#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "BmpLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#define GL_CLAMP_TO_EDGE 0x812F

//GLUquadric *quad;
using namespace std;

double Txval=-1.5,Tyval=0,Tzval=-1.5;
double windowHeight=750, windowWidth=1100;
double Eyex=0, Eyey=15, Eyez=20, Eyex_tem, Eyey_tem, Eyez_tem;
double lookatx=0, lookaty=15, lookatz=0;
double headx=0, heady=1, headz=0;
double fovy=120;
double speed_turbine=1.5;
// rotation around the y-axis variable
///double dx;
//double dz;
double dx2_dz2;
double pitch_theta=.004;
double lookaty_tem, lookatz_tem;
double roll_value = 0.2, pi = acos(-1), cs_angle=cos(pi/180), sn_angle=sin(pi/180);
GLfloat dx, dy, dz, dxyz;
unsigned int ID;

// rotation about the z axis variablw
double lookatx_tem;

GLfloat alpha = 0.0, theta = 0.0, gama=0.0, axis_x=0.0, axis_y=0.0, axis_z=0, eyethetax=0, eyethetay=0, eyethetaz=0;
GLfloat turbine_theta=0;
GLboolean xRotate = false, yRotate = false, zRotate = false, eyerotatex=false, eyerotatey=false, eyerotatez=false;
GLboolean turbine_rotate = true;

double bus_switch=true;
double busx=-10, busy, busz=7;

const int L=20;
int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;
int wired=0;
int shcpt=1;
int animat = 0;
//const int L=20;
const int dgre=3;
int ncpt=L+1;
int clikd=0;
const int nt = 40;				//number of slices on x-direction
const int ntheta = 20;
GLfloat ctrlpoints[L+1][3] =
{
{7.625,5.4,0},
{7.325,4.775,0},
{7.225,4.05,0},
{6.975,3.4,0},
{6.675,2.85,0},
{6.275,2.15,0},
{5.85,1.725,0},
{4.85,1.15,0},
{3.975,0.9,0},
{3.325,0.85,0},
{2.9,0.375,0},
{2.775,-0.175,0},
{2.725,-0.7,0},
{3.225,-0.925,0},
{3.875,-0.9,0},
{5.175,-1.375,0},
{5.825,-1.975,0},
{6.5,-2.725,0},
{6.925,-3.925,0},
{7.325,-5.05,0},
{7.6,0.175,0},
};

//light
float spot_cut_off = 50;

// lighting variable

bool light_switch_0=true;

GLboolean left_light_on = true;
GLboolean spot_light_on = false;

GLboolean ambient_light_state = false;
GLboolean specular_light_state = true;
GLboolean diffuse_light_state = false;

const GLfloat ambient[] = {0.5, 1, 0.5, 1.0};
const GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
const GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
const GLfloat gray[] = {0.8, 0.8, 0.8, 1.0};
const GLfloat silver[] = {0.75, 0.75, 0.75, 1.0};
const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
const GLfloat lime[] = {0.0, 1.0, 0.0, 1.0};
const GLfloat green[] = {0.0, 0.8, 0.0, 1.0};
const GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
const GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
const GLfloat maroon[] = {0.8, 0.0, 0.0, 1.0};
const GLfloat woodColor[] = {0.56, 0.3, 0.2, 1.0};

static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 0.0, 0.0},
    {0.5, 0.5, 0.5}
};
static GLfloat v_cube[8][3]=
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}

};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};


static GLubyte quadIndices[1][4] =
{
    {0, 3, 2, 1}
};

static GLbyte q_Indices[6][4]=
{
    {3,1,5,7},
    {2,0,1,3},
    {7,5,4,6},
    {2,3,7,6},
    {1,0,5,4},
    {6,4,0,2},
};

static GLfloat colors[6][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.5, 0.5, 0.0},
    {.2, 0.6, 0.6}
};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void drawpyramid()
{

    //glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);

    for (GLint i = 0; i <4; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
       // glColor3f(colors[4][0],colors[4][1],colors[4][2]);
       getNormal3p(v_pyramid[quadIndices[i][0]][0], v_pyramid[quadIndices[i][0]][1], v_pyramid[quadIndices[i][0]][2],
                    v_pyramid[quadIndices[i][1]][0], v_pyramid[quadIndices[i][1]][1], v_pyramid[quadIndices[i][1]][2],
                    v_pyramid[quadIndices[i][2]][0], v_pyramid[quadIndices[i][2]][1], v_pyramid[quadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
    }
    glEnd();


}

void light()
{
    const GLfloat *no_light = black;
    //left
    const GLfloat *left_light_ambient = ambient;
    const GLfloat *left_light_diffuse = green;
    const GLfloat *left_light_specular = green;
    //right
    const GLfloat *right_light_ambient = ambient;
    const GLfloat *right_light_diffuse = white;
    const GLfloat *right_light_specular = silver;
    //spot
    const GLfloat *spot_light_ambient = ambient;
    const GLfloat *spot_light_diffuse = maroon;
    const GLfloat *spot_light_specular = maroon;
    //light position
    const GLfloat left_light_position[] = {9, 40, -25, 1.0};       //light_left
    const GLfloat spot_light_position[] = {-5, 15, -20, 1};
    const GLfloat sun_position[]={-50,50,0};


    glEnable(GL_LIGHTING);

    //left light
    glEnable(GL_LIGHT0);

    if (left_light_on)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, white);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0, GL_SPECULAR, white);
        glLightfv(GL_LIGHT0, GL_POSITION, left_light_position);
    }
    else
    {
        //ambient, diffuse,specular
        if (ambient_light_state)
        {
            glLightfv(GL_LIGHT0, GL_AMBIENT, left_light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
        }
        else if (specular_light_state)
        {
            glLightfv(GL_LIGHT0, GL_SPECULAR, left_light_specular);
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
        }
        else if (diffuse_light_state)
        {
            glLightfv(GL_LIGHT0, GL_DIFFUSE, left_light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
        }
        else
        {
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
        }
    }


    //spot light
    glEnable(GL_LIGHT1);
    GLfloat spot_direction[] = {0, -1, 0, 1};
    if (spot_light_on)
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, spot_light_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, spot_light_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spot_light_specular);
        glLightfv(GL_LIGHT1, GL_POSITION, spot_light_position);

        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cut_off);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, no_light);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spot_light_ambient);
    }

    //sunlight
    //glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, white);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT2, GL_SPECULAR, white);
    glLightfv(GL_LIGHT2, GL_POSITION, sun_position);
}


void drawcube()
{
    //glColor3f(1,0,0);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[q_Indices[i][0]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_cube[q_Indices[i][1]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[q_Indices[i][2]][0]);
         glTexCoord2f(0,1);
        glVertex3fv(&v_cube[q_Indices[i][3]][0]);

        glTexCoord2f(1,1);
    }
    glEnd();
}


void square()
{


    glBegin(GL_QUADS);
    //glColor3f(0,0,1);
    glVertex3fv(&v_cube[q_Indices[1][0]][0]);
    glVertex3fv(&v_cube[q_Indices[1][1]][0]);
    glVertex3fv(&v_cube[q_Indices[1][2]][0]);
    glVertex3fv(&v_cube[q_Indices[1][3]][0]);
    glEnd();
}
void material_property(GLfloat R, GLfloat G, GLfloat B)
{
    GLfloat no_mat[] = { 1, 1, 1, 1.0 };
    GLfloat mat_ambient[] = { R, G, B, 1.0 };
    GLfloat mat_diffuse[] = { R, G, B, 1.0 };
    GLfloat mat_specular[] = { 1, 1.0, 1, 1.0 };
    GLfloat mat_shininess[] = {50};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
}

//base
void base()
{
    material_property(.23,.15,.12);
    //base
    glPushMatrix();
    glTranslatef(0,-.1,0);
    glScalef(300,.2,300);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
}

void turbine()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.93, 0.91, 0.86, 1.0 };
    GLfloat mat_diffuse[] = { 0.93, 0.91, 0.86, 1.0 };
    GLfloat mat_specular[] = { 1, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {50};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    //base

    glPushMatrix();
    glTranslatef(0,.25,0);
    glScalef(1,.5,1);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    // stick
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(.2,10,.2);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

     // stick
    glPushMatrix();
    glTranslatef(0,10,0);
    glScalef(1,.2,.2);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.5,10,0);
    glRotatef( turbine_theta,1, 0, 0 );
        glPushMatrix();
        glScalef(.1,.3,4);
        glTranslatef(-.5,-.5,-.5);
        drawcube();
        glPopMatrix();

        glPushMatrix();
        glScalef(.1,4,.3);
        glTranslatef(-.5,-.5,-.5);
        drawcube();
        glPopMatrix();
    glPopMatrix();


}

void cala()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.91, .52, 0.42, 1.0 };
    GLfloat mat_diffuse[] = { 0.91, .52, 0.42, 1.0 };
    GLfloat mat_specular[] = { 1, 1.0, 1, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glTranslatef(-.5,3,-.5);
    glScalef(4,4,4);
    drawpyramid();
    glPopMatrix();
}


void fench()
{


    material_property(.44,.33,.22);


    for(GLfloat i=-1;i<=4;i+=.5)
    {
        glPushMatrix();
        glTranslatef(i,0,4);
        glScalef(.1,1,.1);
        drawcube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i,0,-1);
        glScalef(.1,1,.1);
        drawcube();
        glPopMatrix();
    }

    for(GLfloat i=-1;i<4;i+=.5)
    {
        glPushMatrix();
        glTranslatef(-1,0,i);
        glScalef(.1,1,.1);
        drawcube();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(4,0,i);
        glScalef(.1,1,.1);
        drawcube();
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(-1,0.3,4);
    glScalef(5,0.1,0.1);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.6,4);
    glScalef(5,.1,.1);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.3,-1);
    glScalef(5,.1,.1);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.6,-1);
    glScalef(5,.1,.1);
    drawcube();
    glPopMatrix();

    //left right
    glPushMatrix();
    glTranslatef(-1,.3,-1);
    glScalef(.1,.1,5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.6,-1);
    glScalef(.1,.1,5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,.3,-1);
    glScalef(.1,.1,5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,.6,-1);
    glScalef(.1,.1,5);
    drawcube();
    glPopMatrix();

}
void window_door()
{
    material_property(.79, .79, .8);

    //window
    glPushMatrix();
    glTranslatef(0,1,1.8);
    glScalef(.4,.4,.4);
    square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1,2.3);
    glScalef(.4,.4,.4);
    square();
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,1.5,1.8);
    glScalef(.4,.4,.4);
    square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.5,2.3);
    glScalef(.4,.4,.4);
    square();
    glPopMatrix();

    //door
    glPushMatrix();
    glTranslatef(0,.4,0.3);
    glScalef(1,2,.8);
    square();
    glPopMatrix();


}
void house()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.16, 0.40, 0.63, 1.0 };
    GLfloat mat_diffuse[] = { 0.16, 0.40, 0.63, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glTranslatef(Txval, Tyval,Tzval);
    glPushMatrix();
    glScalef(3,3,3);
    drawcube();
    glPopMatrix();

    cala();
    
    fench();
    glPushMatrix();
    glBegin(GL_POINT);
    glColor3f(0,1,0);
    glVertex3f(-2,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();

    window_door();
    glPopMatrix();
}

// beginning of bus design
void wheel()
{
    material_property(0,0,0);
    glPushMatrix(); //Wheel1
    glTranslatef(-1.5,1.65,.95);
    glScalef(.75,.75,0.75);
    glutSolidTorus(.2,.3,10,16);
    glPopMatrix();
    //back
    glPushMatrix(); //Wheel1
    glTranslatef(1,1.65,.95);
    glScalef(.75,.75,0.75);
    glutSolidTorus(.2,.3,10,16);
    glPopMatrix();

    glPushMatrix(); //Wheel1
    glTranslatef(-1.5,1.65,-.95);
    glScalef(.75,.75,0.75);
    glutSolidTorus(.2,.3,10,16);
    glPopMatrix();
    //back
    glPushMatrix(); //Wheel1
    glTranslatef(1,1.65,-.95);
    glScalef(.75,.75,0.75);
    glutSolidTorus(.2,.3,10,16);
    glPopMatrix();
}

void bus()
{
    GLfloat no_mat[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.91, .52, 0.42, 1.0 };
    GLfloat mat_diffuse[] = { 0.91, .52, 0.42, 1.0 };
    GLfloat mat_specular[] = { 1, 1.0, 1, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBindTexture(GL_TEXTURE_2D,1);

    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(5,2.7,2);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    //bus front side
    glBindTexture(GL_TEXTURE_2D,2);
    glPushMatrix();
    glTranslatef(-2.5,3,0);
    glScalef(.1,2.7,2);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,9);

    glPushMatrix();
    glTranslatef(0,4.4,0);
    glScalef(5,.1,2);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    wheel();
}

void road()
{
    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);

    glPushMatrix();
    glTranslatef(0,0,7);
    glScalef(120,.2,2.5);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    //Road x axis -1
    glPushMatrix();
    glTranslatef(0,0,-23);
    glScalef(120,.2,2.5);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    //Road x axis -2
    glPushMatrix();
    glTranslatef(0,0,-53);
    glScalef(120,.2,2.5);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    //Road x axis +1
    glPushMatrix();
    glTranslatef(0,0,37);
    glScalef(120,.2,2.5);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


}

void playground()
{
    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();

    glScaled(10,.2,10);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void banner()
{

    //base
    material_property(.75,.44,.17);

    glPushMatrix();
    glTranslatef(0,.25,0);
    glScalef(1,.5,1);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    // stick
    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(.2,5,.2);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    //banner

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(0,6,0);
    glScalef(4,2.5,.1);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}



void building()
{
    material_property(1,1,1);

    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(5,.2,4);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    glTranslatef(0,3.5,0);
    glScalef(5,7,4);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void building_all()
{
    for(int i =12;i<35;i=i+8)
    {
        glPushMatrix();
        glTranslatef(i,0,11);
        glScalef(.75,1.25,.75);
        building();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
    }
}


void building2()
{
    material_property(1,1,1);

    glPushMatrix();
    glTranslatef(0,30,0);
    glScalef(5,.2,4);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(5,30,4);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void building3()
{
    material_property(1,1,1);

    glPushMatrix();
    glTranslatef(0,25,0);
    glScalef(6,.2,5);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,12.5,0);
    glScalef(6,25,5);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void bus_stopage()
{
    //base
    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(2.5,0,0);
    glScalef(7,0.5,5);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();

    //stand
     material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(2.5,3,-2.5);
    glScalef(7,8,.5);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();

     material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glPushMatrix();
    glTranslatef(2.5,7,-2.5);
    glRotatef(60,1,0,0);
    glTranslatef(0,3,0);
    glScalef(7,6,.5);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();

}

void cylinder_3D(GLdouble height,GLdouble rad ,GLdouble rad_2)
{


    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glRotatef(90, 1, 0, 0);

    gluCylinder(qobj,  rad, rad_2, height, 20, 20);
    gluDeleteQuadric(qobj);

}
void tree1()
{
    material_property(0,.3,0);
    glPushMatrix();
    glTranslatef(0,8,0);
    glRotatef(-90,1,0,0);
    glutSolidCone(4,7,15,15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,13,0);
    glRotatef(-90,1,0,0);
    glutSolidCone(3,6,15,15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,18,0);
    glRotatef(-90,1,0,0);
    glutSolidCone(2,4,15,15);
    glPopMatrix();

    material_property(.4,0.36,.31);
    //material_property(1,1,1);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(0,15,0);
    //glRotatef(-90,1,0,0);
    cylinder_3D(14,.5,1);
    glPopMatrix();



    glDisable(GL_TEXTURE_1D);
    //material_property(0,1,0);
}

void tree_all()
{
    for(int z=3;z>-22;z=z-5)
    {
        glPushMatrix();
        glTranslatef(-18,0,z);
        glScalef(.6,1,.6);
        tree1();
        glPopMatrix();
    }
}

void sky()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glPushMatrix();
    glTranslatef(0,200,-200);
    glScalef(500,500,100);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,200,0);
    glScalef(100,500,500);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200,200,0);
    glScalef(100,500,500);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,200,200);
    glScalef(500,500,100);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}
void BezierCurve ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[i][0];
        y+=coef*ctrlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}
void tableBezier()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*3.1416 / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                getNormal3p(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}
void chair()
{

    float length=20;
    float width=1;

    //base seat
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(length,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();

    // leg base 1
    glPushMatrix();
    glTranslatef(length/2 -width/2,0,length/2-width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();
    // leg base 2
    glPushMatrix();
    glTranslatef(length/2 -width/2,0,- length/2 +width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();
    // leg base 3
    glPushMatrix();
    glTranslatef(-length/2 +width/2,0,+ length/2 -width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();
    // leg  base 4
    glPushMatrix();
    glTranslatef(-length/2 +width/2,0,- length/2 +width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();

    // upper  1
    glPushMatrix();
    glTranslatef(length/2 -width/2,length,length/2-width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();
    // upper 2
    glPushMatrix();
    glTranslatef(-length/2 -width/2,length,length/2+width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();

    // upper close 1
    glPushMatrix();
    glTranslatef(0,length,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();
    // upper close 2
    glPushMatrix();
    glTranslatef(0,length+5,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();

    // upper close 3
    glPushMatrix();
    glTranslatef(0,length-5,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    drawcube();
    glPopMatrix();


}

void chair_table()
{
    // CURVED CHAIR TABLE PART
    glPushMatrix();
    material_property(0.5,0.4,0.3);
    glRotatef( 90, 0.0, 0.0, 1.0);
    //glRotatef( 180, 1.0, 0.0, 1.0);
    glTranslated(-22,0,0);
    glScalef(3,3,3);
    tableBezier();
    glPopMatrix();

     // 1st chair
    glPushMatrix();
    glTranslatef(0,-5,-20);
    glRotatef(180,0,1,0);
    glScalef(0.5,0.5,0.5);
    chair();
    glPopMatrix();

    //2nd chair
    glPushMatrix();

    glTranslatef(0,-5,20);
    //glRotatef(180,0,1,0);
    glScalef(0.5,0.5,0.5);
    chair();
    glPopMatrix();

    //3rd chair
    glPushMatrix();
    glTranslatef(-22,-5,0);
    glRotatef(-90,0,1,0);
    glScalef(0.5,0.5,0.5);
    chair();
    glPopMatrix();
    //4th chair
    glPushMatrix();
    glTranslatef(22,-5,0);
    glRotatef(90,0,1,0);
    glScalef(0.5,0.5,0.5);
    chair();
    glPopMatrix();


}

void tiles()
{
    material_property(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();

    glScaled(15,.2,15);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void road_light()
{
    // base
    glPushMatrix();

    glPushMatrix();
    glTranslatef(80,30,0);
    glScalef(1,30,1);
    glTranslatef(-0.5,-0.5,-0.5);
    material_property(0.8,0.6,0.2);
    drawcube();
    glPopMatrix();

    // light stand
    glPushMatrix();
    glTranslatef(85,42,0);
    glScalef(10,1,1);
    glTranslatef(-0.5,-0.5,-0.5);
    material_property(0.8,0.6,0.2);
    drawcube();
    glPopMatrix();

    // Bulb line
    glPushMatrix();
    glTranslatef(85,38,0);
    glScalef(1,7,1);
    glTranslatef(-0.5,-0.5,-0.5);
    material_property(0.9,0.9,0.9);
    drawcube();
    glPopMatrix();

    // texture light glutsolidshere


    glPushMatrix();
    glTranslatef(85,35,0);
    material_property(1,1,1);
    glutSolidSphere(2,16,16);
    glPopMatrix();

    glPopMatrix();

}

void light_function_0(float x, float y, float z)
{
    // Light Specification
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {1, 1, 1, 1.0};
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };
    GLfloat light_position[] = { x, y, z, 1.0 };
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };

    glEnable( GL_LIGHT0);
    if (light_switch_0)
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);

        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
        //glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);

    }
    else
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);

    }


    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

}


void roadlight()
{
        for (int i=-20; i<=90; i=i+20)
    {
        glPushMatrix();
        light_function_0(125,20,-i);
        glTranslatef(-45,-20,-i);
        road_light();
        glPopMatrix();
    }
}


void grass_block22()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glPushMatrix();
    glScalef(30,1,30);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void swimming_pool_block21()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glPushMatrix();
    glScalef(30,1,30);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void tree_around_pool()
{
    for(int z=-25;z>-55;z-=8)
    {
        glPushMatrix();
        glTranslatef(-25,0,z);
        glScalef(.5,.8,.5);
        tree1();
         glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(-20,0,0);
        for(int z=-25;z>-55;z-=8)
    {
        glPushMatrix();
        glTranslatef(-30,0,z);
        glScalef(.5,.8,.5);
        tree1();
         glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-33,0,-25);
    glScalef(.5,.8,.5);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-41,0,-25);
    glScalef(.5,.8,.5);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-33,0,-49);
    glScalef(.5,.8,.5);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-41,0,-49);
    glScalef(.5,.8,.5);
    tree1();
    glPopMatrix();
}

void bus_animation()
{
    if(busx<=70)
    {

        busx +=0.2;
    }
    if(busx>=70)
    {
        busx = -70;

    }

    glutPostRedisplay();

}
void busmove()
{
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(busx,-2.8,7);
        glScalef(2,2,1);
        bus();
        if (bus_switch)
        {

            bus_animation();
        }

        glPopMatrix();
}

void sun_moon()
{

    // moon 1
    material_property(.97,0.16,0.05);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);

    glPushMatrix();
    glTranslatef(0,70,-100);
    glScalef(3,3,3);
    glutSolidSphere(2,16,16);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void park()
{
// wood
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);

    glPushMatrix();
    glTranslatef(160,30,-60);
    glScalef(2,30,2);
    glTranslatef(-0.5,-0.5,-0.5);
    material_property(.78,.46,.29);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //leaf

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);

    glPushMatrix();
    glTranslatef(160,50,-60);
    glScalef(8,12,8);
    glTranslatef(-0.5,-0.5,-0.5);
     material_property(1,1,1);
    drawcube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void park_with_tree()
{
    // park tree 1
    for (int i=10; i<=100; i+=20)
    {
        glPushMatrix();
        glTranslatef(i,-20,0);
        park();
        glPopMatrix();

    }

    // park tree 2
    for (int i=10; i<=100; i+=20)
    {
        glPushMatrix();
        glTranslatef(i,-20,15);
        park();
        glPopMatrix();

    }

    // park tree 3
    for (int i=10; i<=100; i+=20)
    {
        glPushMatrix();
        glTranslatef(i,-20,-15);
        park();
        glPopMatrix();

    }

        for (int i=10; i<=100; i+=20)
    {
        glPushMatrix();
        glTranslatef(i,-20,30);
        park();
        glPopMatrix();

    }

}

void parking_zone()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);
    glPushMatrix();
    glScalef(20,1,15);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void sea()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19);
    glPushMatrix();
    glTranslatef(0,0,-120);
    glScalef(300,2,100);
    glTranslatef(-.5,-.5,-.5);
    drawcube();
    glPopMatrix();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int ftm=8;
    //glFrustum(-ftm, ftm, -ftm, ftm, 3, 300);
    gluPerspective(fovy,1,3,400);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(Eyex,Eyey,Eyez, lookatx,lookaty, lookatz, headx, heady, headz);
    glViewport(0, 0, windowWidth, windowHeight);
    glRotatef( alpha,axis_x, axis_y, axis_z );
    glRotatef( theta, axis_x, axis_y, axis_z );
    glRotatef(gama, axis_x, axis_y, axis_z);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(busx,-1,7);
    glScalef(2,2,1);
    //bus();
    glPopMatrix();
    road();
    glPushMatrix();
    glTranslatef(0,0,-22);
    glRotatef(90,0,1,0);
    road();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,-.5);
    playground();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12,0,4);
    glScalef(2,2,2);
    banner();
    glPopMatrix();
    //trees();
    building_all();

    glPushMatrix();
    glTranslatef(25,0,2.5);
    bus_stopage();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,2,2);
    house();
    glPopMatrix();
    base();

    glPushMatrix();
    glTranslatef(4.5,0,4.5);
    //glScalef(.5,.5,.5);
    //turbine();
    glPopMatrix();

    glPushMatrix();
    tree_all();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38,0,-8);
    glScalef(2.5,1,2.5);
    playground();
    glPopMatrix();

    //building block 2
    glPushMatrix();
    glTranslatef(-28,0,3);
    building2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-48,0,3);
    building2();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,-22);
        glPushMatrix();
        glTranslatef(-28,0,3);
        building2();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-48,0,3);
        building2();
        glPopMatrix();
    glPopMatrix();
    // building block 2 end

    sky();

    glPushMatrix();
    glTranslatef(21,3,-10);
    glScalef(0.25,0.25,0.25);
    chair_table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22,0,-12);
    glScalef(1.6,1,1.2);
    tiles();
    glPopMatrix();

    roadlight();

    glPushMatrix();
    glTranslatef(-8,0,-38);
    glScalef(.9,1,.9);
    grass_block22();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-38,0,-38);
    glScalef(.8,1,.8);
    swimming_pool_block21();
    glPopMatrix();

    tree_around_pool();

    // building block 3
    glPushMatrix();
    glTranslatef(2,0,-49);
    building3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,0,-49);
    building3();
    glPopMatrix();


    busmove();

    sun_moon();

    glPushMatrix();
    glTranslatef(-25,0,15);
    glScalef(.4,.4,.4);
    park_with_tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6,0,-13);
    parking_zone();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-16);
    glRotatef(90,0,1,0);
    bus();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-5,0,-16);
    glRotatef(90,0,1,0);
    bus();
    glPopMatrix();

    glPushMatrix();
    material_property(.78,.47,.29);
    glTranslatef(21,3,-10);
    glScalef(1,.2,1);
    glutSolidSphere(3,15,20);
    glPopMatrix();

    glPushMatrix();
    material_property(.9,.9,.9);
    glTranslatef(21,4.6,-10);

    glutSolidTeapot(1);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(22,0,-38);
    glScalef(.9,1,.9);
    grass_block22();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22,0,-44);
    glScalef(3,3,3);
    turbine();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(22,0,-38);
    glScalef(3,3,3);
    turbine();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(22,0,-32);
    glScalef(3,3,3);
    turbine();
    glPopMatrix();

    //sea();

    glFlush();
    glutSwapBuffers();


}
void Pitch_y1(){
    GLfloat ty, tz;

    ty = lookaty - Eyey;
    tz = lookatz - Eyez;

    dy = ty*cs_angle-tz*sn_angle;
    dz = ty*sn_angle+tz*cs_angle;

    lookaty = dy + Eyey;
    lookatz = dz + Eyez;

}
void Pitch_y2(){
    GLfloat ty, tz;

    ty = lookaty - Eyey;
    tz = lookatz - Eyez;

    dy = ty*cs_angle+tz*sn_angle;
    dz = -ty*sn_angle+tz*cs_angle;

    lookaty = dy + Eyey;
    lookatz = dz + Eyez;

}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case '0':
        left_light_on = !left_light_on;
        ambient_light_state = false;
        specular_light_state = false;
        diffuse_light_state = false;
        break;
    case '1':
        spot_light_on = !spot_light_on;
        break;
    case 'p':
        spot_cut_off = spot_cut_off + 10;
        break;
    case 'n':
        spot_cut_off = spot_cut_off - 10;
        break;
    case 'a':
        ambient_light_state = !ambient_light_state;
        break;
    case 's':
        specular_light_state = !specular_light_state;
        break;
    case 'd':
        diffuse_light_state = !diffuse_light_state;
        break;

    case 'x':
    case 'X':
        xRotate = !xRotate;
        yRotate = false;
        zRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        break;

    case 'y':
    case 'Y':
        yRotate = !yRotate;
        xRotate = false;
        zRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0;
        break;
    case 'z':
    case 'Z':
        zRotate = !zRotate;
        xRotate = false;
        yRotate = false;
        axis_x=0.0;
        axis_y=0.0;
        axis_z=1;
        break;

    case '+':
        Eyey-=1;
        lookaty-=1;
        break;

    case '-':
        Eyey+=1;
        lookaty+=1;
        break;
    case 'q':
        Txval+=1;
        break;
    case 'A':
        Txval-=1;
        break;
    case 'w':
        Tyval+=1;
        break;
    case 'S':
        Tyval-=1;
        break;
    case 'e':
        Tzval+=1;
        break;
    case 'D':
        Tzval-=1;
        break;
    case 'r':
        eyerotatex= !eyerotatex;
        break;
    case 'P':
        eyerotatey= !eyerotatey;
        break;
    case 'i':
        eyerotatez= !eyerotatez;
        break;
    // Rotation around the y-axis for 2 and 8
    case '2':
        Pitch_y2();
        break;
    case '8':
        Pitch_y1();
        break;
    // Rotation around the z-axis for 4 and 6
    case '4':
        lookatx_tem=lookatx;
        lookatx=lookatx*cos(.03)+lookatz*sin(.03)-Eyex*cos(.03)-Eyez*sin(.03)+Eyex;
        lookaty=lookaty;
        lookatz=-lookatx_tem*sin(.03)+lookatz*cos(.03)+Eyex*sin(.03)-Eyez*cos(.03)+Eyez;
        break;
    case '6':
        lookatx_tem=lookatx;
        lookatx=lookatx*cos(.04)-lookatz*sin(.04)-Eyex*cos(.04)+Eyez*sin(.04)+Eyex;
        lookaty=lookaty;
        lookatz=lookatx_tem*sin(.04)+lookatz*cos(.04)-Eyex*sin(.04)-Eyez*cos(.04)+Eyez;
        break;
    // Rotation around the x-axis for 7 and 9
    case '7':
        headx += 0.03;
        heady = sqrt(1 - headx*heady);
        break;
    case '9':
        headx -= 0.03;
        heady = sqrt(1 - headx*heady);
        break;
    case 't':

        turbine_rotate=!turbine_rotate;
        break;
    case 'f':
        speed_turbine+=0.1;
        break;
    case 'l':
        speed_turbine-=0.1;
        break;
    // ariel eye view
    case 'b':
        lookatx = Eyex;
        lookaty = Eyey-10;
        lookatz= Eyez-5;
        //headz=1;
        //heady=0;
        break;
    case '3':
        light_switch_0 =! light_switch_0;
        break;
        // key for bus movement
    case 'm':
        bus_switch=!bus_switch;
        break;
    case 'o':
        fovy+=2;
        break;
    case '.':
        fovy-=2;
        break;

    case 27:	// Esc Key
        exit(1);
    }
    glutPostRedisplay();
}

void Specialkey(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        Eyex_tem = Eyex+ ((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));
        Eyez_tem = Eyez+ ((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));

        lookatx_tem=lookatx-Eyex;
        lookatz_tem=lookatz-Eyez;

        lookaty_tem=lookatx_tem;
        lookatx_tem=lookatx_tem*((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))+lookatz_tem*((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))+1;
        lookatz_tem=-lookaty_tem*((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))+lookatz_tem*((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));

        lookaty_tem=lookatx_tem;
        lookatx_tem = lookatx_tem*((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))-lookatz_tem*((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));
        lookatz_tem = lookaty_tem*((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))+lookatz_tem*((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));

        lookatz=Eyez+lookatz_tem;
        lookatx=Eyex+lookatx_tem;

        Eyex=Eyex_tem;
        Eyez=Eyez_tem;
        break;
    case GLUT_KEY_DOWN:
        Eyex_tem = Eyex- ((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));
        Eyez_tem = Eyez- ((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));

        lookatx_tem=lookatx-Eyex;
        lookatz_tem=lookatz-Eyez;

        lookaty_tem=lookatx_tem;
        lookatx_tem=lookatx_tem*((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))+lookatz_tem*((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))-1;
        lookatz_tem=-lookaty_tem*((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))+lookatz_tem*((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));

        lookaty_tem=lookatx_tem;
        lookatx_tem = lookatx_tem*((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))-lookatz_tem*((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));
        lookatz_tem = lookaty_tem*((lookatz-Eyez)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)))+lookatz_tem*((lookatx-Eyex)/sqrt(pow((lookatx-Eyex),2)+pow((lookatz-Eyez),2)));

        lookatz=Eyez+lookatz_tem;
        lookatx=Eyex+lookatx_tem;

        Eyex=Eyex_tem;
        Eyez=Eyez_tem;
        break;
    case GLUT_KEY_LEFT:
        Eyex-=1;
        lookatx-=1;
        break;
    case GLUT_KEY_RIGHT:
        Eyex+=1;
        lookatx+=1;
        break;
    }

    glutPostRedisplay();
}



void animate()
{
    if (xRotate == true)
    {
        theta += 0.3;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (yRotate == true)
    {
        alpha += 0.3;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (zRotate == true)
    {
        gama += 0.3;
        if(alpha > 360.0)
            gama -= 360.0*floor(gama/360.0);
    }
    if(eyerotatex==true)
    {

        eyethetax -= 0.0000002;
        if(eyethetax > 360.0)
            eyethetax -= 360.0*floor(eyethetax/360.0);
        Eyex=Eyex;
        Eyey=Eyey*cos(eyethetax)-Eyez*sin(eyethetax);
        Eyez=Eyey*sin(eyethetax)+Eyez*cos(eyethetax);

    }
    if(eyerotatey==true)
    {

        eyethetay -= 0.0000002;
        if(eyethetay > 360.0)
            eyethetay -= 360.0*floor(eyethetay/360.0);
        Eyex=Eyex*cos(eyethetay)+Eyez*sin(eyethetay);
        Eyey=Eyey;
        Eyez=-Eyex*sin(eyethetay)+Eyez*cos(eyethetay);

    }
    if(eyerotatez==true)
    {

        eyethetaz -= 0.00000002;
        if(eyethetaz > 360.0)
            eyethetaz -= 360.0*floor(eyethetaz/360.0);
        Eyex=Eyex*cos(eyethetaz)-Eyey*sin(eyethetaz);
        Eyey=-Eyex*sin(eyethetaz)+Eyey*cos(eyethetaz);
        Eyez=Eyez;
    }

    if(turbine_rotate==true)
    {
        turbine_theta += speed_turbine;
        if(turbine_theta > 360.0)
            turbine_theta -= 360.0*floor(turbine_theta/360.0);
    }


    light();
    // bus();

    glutPostRedisplay();

}

void LoadTexture(const char*filename, int rep = 1)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if(rep)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void instruction()
{
    cout << "Welcome to the town " << endl;
    cout << "Designed by: ..." << endl;
    //cout << "Roll: 1707085" << endl;
    cout << "Department of .... "<<endl;
    cout << "Institution "<<endl;
    cout << "Press 'Esc' or 'q' to terminate the project \n" << endl;

    cout<<"------------------Camera control---------------------"<<endl;
    cout << "Press '4 and 6 to yaw effect to rotate right " << endl;
    cout << "press '7 and 9 to Roll effect"<<endl;
    cout << "press '2' and 8 to Roll effect"<<endl;

    cout << "Press 'x' to rotate around x axis " << endl;
    cout << "Press 'y' to rotate around y axis " << endl;
    cout << "Press 'z' to rotate around z axis " << endl;

    cout << "Press '-' to move eye position up  " << endl;
    cout << "Press '+' to move eye position Down  " << endl;
    cout << "Press 'left' to move eye position Left  " << endl;
    cout << "Press 'Right' to move eye position Right  " << endl;
    cout << "Press 'Up' to move eye position in forward direction  " << endl;
    cout << "Press 'Down' to move eye position backward \n " << endl;


    cout<< "----------------Light control instruction----------------"<<endl;

    cout << "Press '0' to switch on & off  Normal Light: Like Toggle" << endl;
    cout << "Press '1' to switch on & off  spot light: Like Toggle" << endl;
    cout << "Press '3' to switch on & off  Road light" << endl;
    cout << "Press 'p' to increase the brightness of spot light" << endl;
    cout << "Press 'n' to decrease the brightness of spot light" << endl;

    cout << "Press 'a' to toggle the ambient light" << endl;
    cout << "Press 's' to toggle the specular light" << endl;
    cout << "Press 'd' to toggle the diffuse light \n" << endl;


    cout<<"----------------bus and terbine control--------------------"<<endl;

    cout << "Press 't' to start the turbine" << endl;
    cout << "Press 'f' to speed up the turbine" << endl;
    cout << "Press 'l' to speed down the turbine" << endl;

    cout << "Press 'm' to move or run the bus" << endl;

}

void call_all_texture()
{
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\bus7.bmp",1);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\bus7.bmp",2);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\road.bmp",3);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\grass3.bmp",4);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\signboard4.bmp",5);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\building8.bmp",6);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\brick3.bmp",7);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\roof.bmp",8);
    /* LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\bus_top.bmp",9); */
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\building7.bmp",9);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\sky.bmp",10);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\brick4.bmp",11);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\grass.bmp",12);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\water1.bmp",13);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\building5.bmp",14);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\wood3.bmp",15);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\sun3.bmp",16);
     LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\leaf3.bmp",17);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\parking_lot.bmp",18);
    LoadTexture("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\water2.bmp",19);
}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(400,50);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D City view");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light();
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(Specialkey);
    call_all_texture();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    instruction();
    glutMainLoop();

    return 0;
}

