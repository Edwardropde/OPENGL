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

double val_tx=-1.5,val_ty=0,val_tz=-1.5;
double height_for_windows=750, width_for-windows=1100;
double Eyex=0, Eyey=15, Eyez=20, temxeye, temyeye, temzeye;
double atxlook=0, atylook=15, atzlook=0;
double xheadd=0, yheadd=1, zheadd=0;
double foovvyy=120;
double speed_windmill=1.5;
// rotation around the y-axis variable
///double dx;
//double dz;
double dxdz22;
double theta_pitch=.004;
double atylook_tem, atzlook_tem;
double value_roll = 0.2, pi = acos(-1), angle_cs=cos(pi/180), angle_sn=sin(pi/180);
GLfloat dx, dy, dz, dxyz;
unsigned int ID;

// rotation about the z axis variablw
double atxlook_tem;

GLfloat alpha = 0.0, theta = 0.0, gama=0.0, x_axis=0.0, y_axis=0.0, z_axis=0, tax_the_eye=0, tay_the_eye=0, taz_the_eye=0;
GLfloat windmill_theta=0;
GLboolean rotate_x = false, rotate_y = false, rotate_z = false, rotate_eye_x=false, rotate_eye_y=false, rotate_eye_z=false;
GLboolean windmill_rotate = true;

double switch_bus=true;
double x_bus=-10, y_bus, z_bus=7;

const int L=20;
int x_angle= 0, y_angle = 0, z_angle = 0;          //rotation angles
int window;
int wired=0;
int spt=1;
int anim = 0;
//const int L=20;
const int degree=3;
int ncptt=L+1;
int clicked=0;
const int nt = 40;				//number of slices on x-direction
const int nostthet = 20;
GLfloat controlpoints[L+1][3] =
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
float cutoff_spot = 50;

// lighting variable

bool switch_light=true;

GLboolean on_left_light = true;
GLboolean on_spot_light = false;

GLboolean state_light_ambient = false;
GLboolean state_light_specular = true;
GLboolean state_light_diffuse = false;

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

static GLfloat pyramid_vecval[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 0.0, 0.0},
    {0.5, 0.5, 0.5}
};
static GLfloat cube_vecval[8][3]=
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

static GLubyte pote_indic[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};


static GLubyte guad_indic[1][4] =
{
    {0, 3, 2, 1}
};

static GLbyte grid_indic[6][4]=
{
    {3,1,5,7},
    {2,0,1,3},
    {7,5,4,6},
    {2,3,7,6},
    {1,0,5,4},
    {6,4,0,2},
};

static GLfloat coloring[6][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.5, 0.5, 0.0},
    {.2, 0.6, 0.6}
};
static void ret_3p_normal
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
void draw_pyramid()
{

    //glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);

    for (GLint i = 0; i <4; i++)
    {
        //glColor3f(coloring[i][0],coloring[i][1],coloring[i][2]);
        ret_3p_normal(pyramid_vecval[pote_indic[i][0]][0], pyramid_vecval[pote_indic[i][0]][1], pyramid_vecval[pote_indic[i][0]][2],
                    pyramid_vecval[pote_indic[i][1]][0], pyramid_vecval[pote_indic[i][1]][1], pyramid_vecval[pote_indic[i][1]][2],
                    pyramid_vecval[pote_indic[i][2]][0], pyramid_vecval[pote_indic[i][2]][1], pyramid_vecval[pote_indic[i][2]][2]);

        glVertex3fv(&pyramid_vecval[pote_indic[i][0]][0]);
        glVertex3fv(&pyramid_vecval[pote_indic[i][1]][0]);
        glVertex3fv(&pyramid_vecval[pote_indic[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
       // glColor3f(coloring[4][0],coloring[4][1],coloring[4][2]);
       ret_3p_normal(pyramid_vecval[guad_indic[i][0]][0], pyramid_vecval[guad_indic[i][0]][1], pyramid_vecval[guad_indic[i][0]][2],
                    pyramid_vecval[guad_indic[i][1]][0], pyramid_vecval[guad_indic[i][1]][1], pyramid_vecval[guad_indic[i][1]][2],
                    pyramid_vecval[guad_indic[i][2]][0], pyramid_vecval[guad_indic[i][2]][1], pyramid_vecval[guad_indic[i][2]][2]);
        glVertex3fv(&pyramid_vecval[guad_indic[i][0]][0]);
        glVertex3fv(&pyramid_vecval[guad_indic[i][1]][0]);
        glVertex3fv(&pyramid_vecval[guad_indic[i][2]][0]);
        glVertex3fv(&pyramid_vecval[guad_indic[i][3]][0]);
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

    if (on_left_light)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, white);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0, GL_SPECULAR, white);
        glLightfv(GL_LIGHT0, GL_POSITION, left_light_position);
    }
    else
    {
        //ambient, diffuse,specular
        if (state_light_ambient)
        {
            glLightfv(GL_LIGHT0, GL_AMBIENT, left_light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
        }
        else if (state_light_specular)
        {
            glLightfv(GL_LIGHT0, GL_SPECULAR, left_light_specular);
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
        }
        else if (state_light_diffuse)
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
    if (on_spot_light)
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, spot_light_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, spot_light_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spot_light_specular);
        glLightfv(GL_LIGHT1, GL_POSITION, spot_light_position);

        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff_spot);
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


void cube_draw()
{
    //glColor3f(1,0,0);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        //glColor3f(coloring[i][0],coloring[i][1],coloring[i][2]);
        ret_3p_normal(cube_vecval[guad_indic[i][0]][0], cube_vecval[guad_indic[i][0]][1], cube_vecval[guad_indic[i][0]][2],
                    cube_vecval[guad_indic[i][1]][0], cube_vecval[guad_indic[i][1]][1], cube_vecval[guad_indic[i][1]][2],
                    cube_vecval[guad_indic[i][2]][0], cube_vecval[guad_indic[i][2]][1], cube_vecval[guad_indic[i][2]][2]);
        glVertex3fv(&cube_vecval[grid_indic[i][0]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&cube_vecval[grid_indic[i][1]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube_vecval[grid_indic[i][2]][0]);
         glTexCoord2f(0,1);
        glVertex3fv(&cube_vecval[grid_indic[i][3]][0]);

        glTexCoord2f(1,1);
    }
    glEnd();
}


void square()
{


    glBegin(GL_QUADS);
    //glColor3f(0,0,1);
    glVertex3fv(&cube_vecval[grid_indic[1][0]][0]);
    glVertex3fv(&cube_vecval[grid_indic[1][1]][0]);
    glVertex3fv(&cube_vecval[grid_indic[1][2]][0]);
    glVertex3fv(&cube_vecval[grid_indic[1][3]][0]);
    glEnd();
}
void property_material(GLfloat R, GLfloat G, GLfloat B)
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
    property_material(.23,.15,.12);
    //base
    glPushMatrix();
    glTranslatef(0,-.1,0);
    glScalef(300,.2,300);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();
}

void windmill()
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
    cube_draw();
    glPopMatrix();

    // stick
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(.2,10,.2);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

     // stick
    glPushMatrix();
    glTranslatef(0,10,0);
    glScalef(1,.2,.2);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.5,10,0);
    glRotatef( windmill_theta,1, 0, 0 );
        glPushMatrix();
        glScalef(.1,.3,4);
        glTranslatef(-.5,-.5,-.5);
        cube_draw();
        glPopMatrix();

        glPushMatrix();
        glScalef(.1,4,.3);
        glTranslatef(-.5,-.5,-.5);
        cube_draw();
        glPopMatrix();
    glPopMatrix();


}

void c_a_l_a()
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
    draw_pyramid();
    glPopMatrix();
}


void f_e_n_c_h()
{


    property_material(.44,.33,.22);


    for(GLfloat i=-1;i<=4;i+=.5)
    {
        glPushMatrix();
        glTranslatef(i,0,4);
        glScalef(.1,1,.1);
        cube_draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(i,0,-1);
        glScalef(.1,1,.1);
        cube_draw();
        glPopMatrix();
    }

    for(GLfloat i=-1;i<4;i+=.5)
    {
        glPushMatrix();
        glTranslatef(-1,0,i);
        glScalef(.1,1,.1);
        cube_draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(4,0,i);
        glScalef(.1,1,.1);
        cube_draw();
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(-1,0.3,4);
    glScalef(5,0.1,0.1);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.6,4);
    glScalef(5,.1,.1);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.3,-1);
    glScalef(5,.1,.1);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.6,-1);
    glScalef(5,.1,.1);
    cube_draw();
    glPopMatrix();

    //left right
    glPushMatrix();
    glTranslatef(-1,.3,-1);
    glScalef(.1,.1,5);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,.6,-1);
    glScalef(.1,.1,5);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,.3,-1);
    glScalef(.1,.1,5);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,.6,-1);
    glScalef(.1,.1,5);
    cube_draw();
    glPopMatrix();

}
void door_window()
{
    property_material(.79, .79, .8);

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


    glTranslatef(val_tx, val_ty,val_tz);
    glPushMatrix();
    glScalef(3,3,3);
    cube_draw();
    glPopMatrix();

    c_a_l_a();
    
    f_e_n_c_h();
    glPushMatrix();
    glBegin(GL_POINT);
    glColor3f(0,1,0);
    glVertex3f(-2,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();

    door_window();
    glPopMatrix();
}

// beginning of bus design
void wheel()
{
    property_material(0,0,0);
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
    cube_draw();
    glPopMatrix();

    //bus front side
    glBindTexture(GL_TEXTURE_2D,2);
    glPushMatrix();
    glTranslatef(-2.5,3,0);
    glScalef(.1,2.7,2);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,9);

    glPushMatrix();
    glTranslatef(0,4.4,0);
    glScalef(5,.1,2);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    wheel();
}

void road()
{
    property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);

    glPushMatrix();
    glTranslatef(0,0,7);
    glScalef(120,.2,2.5);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    //Road x axis -1
    glPushMatrix();
    glTranslatef(0,0,-23);
    glScalef(120,.2,2.5);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    //Road x axis -2
    glPushMatrix();
    glTranslatef(0,0,-53);
    glScalef(120,.2,2.5);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    //Road x axis +1
    glPushMatrix();
    glTranslatef(0,0,37);
    glScalef(120,.2,2.5);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


}

void playground()
{
    property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();

    glScaled(10,.2,10);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void banner()
{

    //base
    property_material(.75,.44,.17);

    glPushMatrix();
    glTranslatef(0,.25,0);
    glScalef(1,.5,1);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    // stick
    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(.2,5,.2);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();
    //banner

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(0,6,0);
    glScalef(4,2.5,.1);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}



void building()
{
    property_material(1,1,1);

    glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(5,.2,4);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    glTranslatef(0,3.5,0);
    glScalef(5,7,4);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void all_building()
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


void second_building()
{
    property_material(1,1,1);

    glPushMatrix();
    glTranslatef(0,30,0);
    glScalef(5,.2,4);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(5,30,4);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void third_building()
{
    property_material(1,1,1);

    glPushMatrix();
    glTranslatef(0,25,0);
    glScalef(6,.2,5);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,14);
    glPushMatrix();
    glTranslatef(0,12.5,0);
    glScalef(6,25,5);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void busstop()
{
    //base
    property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(2.5,0,0);
    glScalef(7,0.5,5);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();

    //stand
     property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(2.5,3,-2.5);
    glScalef(7,8,.5);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();

     property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glPushMatrix();
    glTranslatef(2.5,7,-2.5);
    glRotatef(60,1,0,0);
    glTranslatef(0,3,0);
    glScalef(7,6,.5);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();

}

void 3D_cyl(GLdouble height,GLdouble rad ,GLdouble rad_2)
{


    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glRotatef(90, 1, 0, 0);

    gluCylinder(qobj,  rad, rad_2, height, 20, 20);
    gluDeleteQuadric(qobj);

}
void first_tree()
{
    property_material(0,.3,0);
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

    property_material(.4,0.36,.31);
    //property_material(1,1,1);

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,15);
    glPushMatrix();
    glTranslatef(0,15,0);
    //glRotatef(-90,1,0,0);
    3D_cyl(14,.5,1);
    glPopMatrix();



    glDisable(GL_TEXTURE_1D);
    //property_material(0,1,0);
}

void all_trees()
{
    for(int z=3;z>-22;z=z-5)
    {
        glPushMatrix();
        glTranslatef(-18,0,z);
        glScalef(.6,1,.6);
        first_tree();
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
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,200,0);
    glScalef(100,500,500);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-200,200,0);
    glScalef(100,500,500);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,200,200);
    glScalef(500,500,100);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
long long en_ce_aar(int n, int r)
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
void bezier_curve ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=en_ce_aar(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*controlpoints[i][0];
        y+=coef*controlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}
void table_bez()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = controlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*3.1416 / nostthet;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    bezier_curve( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for (i = 0; i < nt; ++i)  			//step through x
    {
        theta = 0;
        t+=dt;
        bezier_curve( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for (j = 0; j <= nostthet; ++j)
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
                ret_3p_normal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
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
    cube_draw();
    glPopMatrix();

    // leg base 1
    glPushMatrix();
    glTranslatef(length/2 -width/2,0,length/2-width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();
    // leg base 2
    glPushMatrix();
    glTranslatef(length/2 -width/2,0,- length/2 +width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();
    // leg base 3
    glPushMatrix();
    glTranslatef(-length/2 +width/2,0,+ length/2 -width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();
    // leg  base 4
    glPushMatrix();
    glTranslatef(-length/2 +width/2,0,- length/2 +width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();

    // upper  1
    glPushMatrix();
    glTranslatef(length/2 -width/2,length,length/2-width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();
    // upper 2
    glPushMatrix();
    glTranslatef(-length/2 -width/2,length,length/2+width/2);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();

    // upper close 1
    glPushMatrix();
    glTranslatef(0,length,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();
    // upper close 2
    glPushMatrix();
    glTranslatef(0,length+5,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();

    // upper close 3
    glPushMatrix();
    glTranslatef(0,length-5,length/2);
    glScalef(length,length/6,0);
    glTranslatef(-0.5,-0.5,-0.5);
    cube_draw();
    glPopMatrix();


}

void chair_table()
{
    // CURVED CHAIR TABLE PART
    glPushMatrix();
    property_material(0.5,0.4,0.3);
    glRotatef( 90, 0.0, 0.0, 1.0);
    //glRotatef( 180, 1.0, 0.0, 1.0);
    glTranslated(-22,0,0);
    glScalef(3,3,3);
    table_bez();
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
    property_material(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();

    glScaled(15,.2,15);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void the_roadlight()
{
    // base
    glPushMatrix();

    glPushMatrix();
    glTranslatef(80,30,0);
    glScalef(1,30,1);
    glTranslatef(-0.5,-0.5,-0.5);
    property_material(0.8,0.6,0.2);
    cube_draw();
    glPopMatrix();

    // light stand
    glPushMatrix();
    glTranslatef(85,42,0);
    glScalef(10,1,1);
    glTranslatef(-0.5,-0.5,-0.5);
    property_material(0.8,0.6,0.2);
    cube_draw();
    glPopMatrix();

    // Bulb line
    glPushMatrix();
    glTranslatef(85,38,0);
    glScalef(1,7,1);
    glTranslatef(-0.5,-0.5,-0.5);
    property_material(0.9,0.9,0.9);
    cube_draw();
    glPopMatrix();

    // texture light glutsolidshere


    glPushMatrix();
    glTranslatef(85,35,0);
    property_material(1,1,1);
    glutSolidSphere(2,16,16);
    glPopMatrix();

    glPopMatrix();

}

void the_light_function(float x, float y, float z)
{
    // Light Specification
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = {1, 1, 1, 1.0};
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };
    GLfloat light_position[] = { x, y, z, 1.0 };
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };

    glEnable( GL_LIGHT0);
    if (switch_light)
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


void light_for_road()
{
    for (int i=-20; i<=90; i=i+20)
    {
        glPushMatrix();
        the_light_function(125,20,-i);
        glTranslatef(-45,-20,-i);
        the_roadlight();
        glPopMatrix();
    }
}


void block22_grass()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,12);
    glPushMatrix();
    glScalef(30,1,30);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void block21_swimming_pool()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,13);
    glPushMatrix();
    glScalef(30,1,30);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void tree_pool_area()
{
    for(int z=-25;z>-55;z-=8)
    {
        glPushMatrix();
        glTranslatef(-25,0,z);
        glScalef(.5,.8,.5);
        first_tree();
         glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(-20,0,0);
    for(int z=-25;z>-55;z-=8)
    {
        glPushMatrix();
        glTranslatef(-30,0,z);
        glScalef(.5,.8,.5);
        first_tree();
         glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-33,0,-25);
    glScalef(.5,.8,.5);
    first_tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-41,0,-25);
    glScalef(.5,.8,.5);
    first_tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-33,0,-49);
    glScalef(.5,.8,.5);
    first_tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-41,0,-49);
    glScalef(.5,.8,.5);
    first_tree();
    glPopMatrix();
}

void animation_for_bus()
{
    if(x_bus<=70)
    {

        x_bus +=0.2;
    }
    if(x_bus>=70)
    {
        x_bus = -70;

    }

    glutPostRedisplay();

}
void movement_bus()
{
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(x_bus,-2.8,7);
        glScalef(2,2,1);
        bus();
        if (switch_bus)
        {

            animation_for_bus();
        }

        glPopMatrix();
}

void moon_sun()
{

    // moon 1
    property_material(.97,0.16,0.05);
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
    property_material(.78,.46,.29);
    cube_draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //leaf

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,17);

    glPushMatrix();
    glTranslatef(160,50,-60);
    glScalef(8,12,8);
    glTranslatef(-0.5,-0.5,-0.5);
     property_material(1,1,1);
    cube_draw();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void park_having_tree()
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

void bus_park_area()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);
    glPushMatrix();
    glScalef(20,1,15);
    glTranslatef(-.5,-.5,-.5);
    cube_draw();
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
    cube_draw();
    glPopMatrix();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int ftm=8;
    //glFrustum(-ftm, ftm, -ftm, ftm, 3, 300);
    gluPerspective(foovvyy,1,3,400);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(Eyex,Eyey,Eyez, atxlook,atylook, atzlook, xheadd, yheadd, zheadd);
    glViewport(0, 0, width_for-windows, height_for_windows);
    glRotatef( alpha,x_axis, y_axis, z_axis );
    glRotatef( theta, x_axis, y_axis, z_axis );
    glRotatef(gama, x_axis, y_axis, z_axis);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(x_bus,-1,7);
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
    all_building();

    glPushMatrix();
    glTranslatef(25,0,2.5);
    busstop();
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
    //windmill();
    glPopMatrix();

    glPushMatrix();
    all_trees();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-38,0,-8);
    glScalef(2.5,1,2.5);
    playground();
    glPopMatrix();

    //building block 2
    glPushMatrix();
    glTranslatef(-28,0,3);
    second_building();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-48,0,3);
    second_building();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,-22);
        glPushMatrix();
        glTranslatef(-28,0,3);
        second_building();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-48,0,3);
        second_building();
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

    light_for_road();

    glPushMatrix();
    glTranslatef(-8,0,-38);
    glScalef(.9,1,.9);
    block22_grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-38,0,-38);
    glScalef(.8,1,.8);
    block21_swimming_pool();
    glPopMatrix();

    tree_pool_area();

    // building block 3
    glPushMatrix();
    glTranslatef(2,0,-49);
    third_building();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,0,-49);
    third_building();
    glPopMatrix();


    movement_bus();

    moon_sun();

    glPushMatrix();
    glTranslatef(-25,0,15);
    glScalef(.4,.4,.4);
    park_having_tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6,0,-13);
    bus_park_area();
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
    property_material(.78,.47,.29);
    glTranslatef(21,3,-10);
    glScalef(1,.2,1);
    glutSolidSphere(3,15,20);
    glPopMatrix();

    glPushMatrix();
    property_material(.9,.9,.9);
    glTranslatef(21,4.6,-10);

    glutSolidTeapot(1);
    glPopMatrix();

     glPushMatrix();
    glTranslatef(22,0,-38);
    glScalef(.9,1,.9);
    block22_grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(22,0,-44);
    glScalef(3,3,3);
    windmill();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(22,0,-38);
    glScalef(3,3,3);
    windmill();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(22,0,-32);
    glScalef(3,3,3);
    windmill();
    glPopMatrix();

    //sea();

    glFlush();
    glutSwapBuffers();


}
void y1_pitch(){
    GLfloat ty, tz;

    ty = atylook - Eyey;
    tz = atzlook - Eyez;

    dy = ty*angle_cs-tz*angle_sn;
    dz = ty*angle_sn+tz*angle_cs;

    atylook = dy + Eyey;
    atzlook = dz + Eyez;

}
void y2_pitch(){
    GLfloat ty, tz;

    ty = atylook - Eyey;
    tz = atzlook - Eyez;

    dy = ty*angle_cs+tz*angle_sn;
    dz = -ty*angle_sn+tz*angle_cs;

    atylook = dy + Eyey;
    atzlook = dz + Eyez;

}

void keyboard_func( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case '0':
        on_left_light = !on_left_light;
        state_light_ambient = false;
        state_light_specular = false;
        state_light_diffuse = false;
        break;
    case '1':
        on_spot_light = !on_spot_light;
        break;
    case 'p':
        cutoff_spot = cutoff_spot + 10;
        break;
    case 'n':
        cutoff_spot = cutoff_spot - 10;
        break;
    case 'a':
        state_light_ambient = !state_light_ambient;
        break;
    case 's':
        state_light_specular = !state_light_specular;
        break;
    case 'd':
        state_light_diffuse = !state_light_diffuse;
        break;

    case 'x':
    case 'X':
        rotate_x = !rotate_x;
        rotate_y = false;
        rotate_z = false;
        x_axis=1.0;
        y_axis=0.0;
        z_axis=0.0;
        break;

    case 'y':
    case 'Y':
        rotate_y = !rotate_y;
        rotate_x = false;
        rotate_z = false;
        x_axis=0.0;
        y_axis=1.0;
        z_axis=0;
        break;
    case 'z':
    case 'Z':
        rotate_z = !rotate_z;
        rotate_x = false;
        rotate_y = false;
        x_axis=0.0;
        y_axis=0.0;
        z_axis=1;
        break;

    case '+':
        Eyey-=1;
        atylook-=1;
        break;

    case '-':
        Eyey+=1;
        atylook+=1;
        break;
    case 'q':
        val_tx+=1;
        break;
    case 'A':
        val_tx-=1;
        break;
    case 'w':
        val_ty+=1;
        break;
    case 'S':
        val_ty-=1;
        break;
    case 'e':
        val_tz+=1;
        break;
    case 'D':
        val_tz-=1;
        break;
    case 'r':
        rotate_eye_x= !rotate_eye_x;
        break;
    case 'P':
        rotate_eye_y= !rotate_eye_y;
        break;
    case 'i':
        rotate_eye_z= !rotate_eye_z;
        break;
    // Rotation around the y-axis for 2 and 8
    case '2':
        y2_pitch();
        break;
    case '8':
        y1_pitch();
        break;
    // Rotation around the z-axis for 4 and 6
    case '4':
        atxlook_tem=atxlook;
        atxlook=atxlook*cos(.03)+atzlook*sin(.03)-Eyex*cos(.03)-Eyez*sin(.03)+Eyex;
        atylook=atylook;
        atzlook=-atxlook_tem*sin(.03)+atzlook*cos(.03)+Eyex*sin(.03)-Eyez*cos(.03)+Eyez;
        break;
    case '6':
        atxlook_tem=atxlook;
        atxlook=atxlook*cos(.04)-atzlook*sin(.04)-Eyex*cos(.04)+Eyez*sin(.04)+Eyex;
        atylook=atylook;
        atzlook=atxlook_tem*sin(.04)+atzlook*cos(.04)-Eyex*sin(.04)-Eyez*cos(.04)+Eyez;
        break;
    // Rotation around the x-axis for 7 and 9
    case '7':
        xheadd += 0.03;
        yheadd = sqrt(1 - xheadd*yheadd);
        break;
    case '9':
        xheadd -= 0.03;
        yheadd = sqrt(1 - xheadd*yheadd);
        break;
    case 't':

        windmill_rotate=!windmill_rotate;
        break;
    case 'f':
        speed_windmill+=0.1;
        break;
    case 'l':
        speed_windmill-=0.1;
        break;
    // ariel eye view
    case 'b':
        atxlook = Eyex;
        atylook = Eyey-10;
        atzlook= Eyez-5;
        //zheadd=1;
        //yheadd=0;
        break;
    case '3':
        switch_light =! switch_light;
        break;
        // key for bus movement
    case 'm':
        switch_bus=!switch_bus;
        break;
    case 'o':
        foovvyy+=2;
        break;
    case '.':
        foovvyy-=2;
        break;

    case 27:	// Esc Key
        exit(1);
    }
    glutPostRedisplay();
}

void key_special(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        temxeye = Eyex+ ((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));
        temzeye = Eyez+ ((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));

        atxlook_tem=atxlook-Eyex;
        atzlook_tem=atzlook-Eyez;

        atylook_tem=atxlook_tem;
        atxlook_tem=atxlook_tem*((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))+atzlook_tem*((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))+1;
        atzlook_tem=-atylook_tem*((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))+atzlook_tem*((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));

        atylook_tem=atxlook_tem;
        atxlook_tem = atxlook_tem*((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))-atzlook_tem*((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));
        atzlook_tem = atylook_tem*((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))+atzlook_tem*((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));

        atzlook=Eyez+atzlook_tem;
        atxlook=Eyex+atxlook_tem;

        Eyex=temxeye;
        Eyez=temzeye;
        break;
    case GLUT_KEY_DOWN:
        temxeye = Eyex- ((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));
        temzeye = Eyez- ((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));

        atxlook_tem=atxlook-Eyex;
        atzlook_tem=atzlook-Eyez;

        atylook_tem=atxlook_tem;
        atxlook_tem=atxlook_tem*((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))+atzlook_tem*((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))-1;
        atzlook_tem=-atylook_tem*((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))+atzlook_tem*((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));

        atylook_tem=atxlook_tem;
        atxlook_tem = atxlook_tem*((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))-atzlook_tem*((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));
        atzlook_tem = atylook_tem*((atzlook-Eyez)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)))+atzlook_tem*((atxlook-Eyex)/sqrt(pow((atxlook-Eyex),2)+pow((atzlook-Eyez),2)));

        atzlook=Eyez+atzlook_tem;
        atxlook=Eyex+atxlook_tem;

        Eyex=temxeye;
        Eyez=temzeye;
        break;
    case GLUT_KEY_LEFT:
        Eyex-=1;
        atxlook-=1;
        break;
    case GLUT_KEY_RIGHT:
        Eyex+=1;
        atxlook+=1;
        break;
    }

    glutPostRedisplay();
}



void the_animation()
{
    if (rotate_x == true)
    {
        theta += 0.3;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (rotate_y == true)
    {
        alpha += 0.3;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (rotate_z == true)
    {
        gama += 0.3;
        if(alpha > 360.0)
            gama -= 360.0*floor(gama/360.0);
    }
    if(rotate_eye_x==true)
    {

        tax_the_eye -= 0.0000002;
        if(tax_the_eye > 360.0)
            tax_the_eye -= 360.0*floor(tax_the_eye/360.0);
        Eyex=Eyex;
        Eyey=Eyey*cos(tax_the_eye)-Eyez*sin(tax_the_eye);
        Eyez=Eyey*sin(tax_the_eye)+Eyez*cos(tax_the_eye);

    }
    if(rotate_eye_y==true)
    {

        tay_the_eye -= 0.0000002;
        if(tay_the_eye > 360.0)
            tay_the_eye -= 360.0*floor(tay_the_eye/360.0);
        Eyex=Eyex*cos(tay_the_eye)+Eyez*sin(tay_the_eye);
        Eyey=Eyey;
        Eyez=-Eyex*sin(tay_the_eye)+Eyez*cos(tay_the_eye);

    }
    if(rotate_eye_z==true)
    {

        taz_the_eye -= 0.00000002;
        if(taz_the_eye > 360.0)
            taz_the_eye -= 360.0*floor(taz_the_eye/360.0);
        Eyex=Eyex*cos(taz_the_eye)-Eyey*sin(taz_the_eye);
        Eyey=-Eyex*sin(taz_the_eye)+Eyey*cos(taz_the_eye);
        Eyez=Eyez;
    }

    if(windmill_rotate==true)
    {
        windmill_theta += speed_windmill;
        if(windmill_theta > 360.0)
            windmill_theta -= 360.0*floor(windmill_theta/360.0);
    }


    light();
    // bus();

    glutPostRedisplay();

}

void texture_load(const char*filename, int rep = 1)
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

    cout << "Press 't' to start the windmill" << endl;
    cout << "Press 'f' to speed up the windmill" << endl;
    cout << "Press 'l' to speed down the windmill" << endl;

    cout << "Press 'm' to move or run the bus" << endl;

}

void texture_call()
{
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\bus7.bmp",1);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\bus7.bmp",2);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\road.bmp",3);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\grass3.bmp",4);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\signboard4.bmp",5);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\building8.bmp",6);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\brick3.bmp",7);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\roof.bmp",8);
    /* texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\bus_top.bmp",9); */
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\building7.bmp",9);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\sky.bmp",10);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\brick4.bmp",11);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\grass.bmp",12);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\water1.bmp",13);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\building5.bmp",14);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\wood3.bmp",15);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\sun3.bmp",16);
     texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\leaf3.bmp",17);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\parking_lot.bmp",18);
    texture_load("H:\\4th year 2nd term\\CSE 4208 Computer Graphics Lab\\project\\Texture\\images\\water2.bmp",19);
}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(400,50);
    glutInitWindowSize(width_for-windows, height_for_windows);
    glutCreateWindow("3D City view");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light();
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glutKeyboardFunc(keyboard_func);
    glutSpecialFunc(key_special);
    texture_call();
    glutDisplayFunc(display);
    glutIdleFunc(the_animation);
    instruction();
    glutMainLoop();

    return 0;
}

