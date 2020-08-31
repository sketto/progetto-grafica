/*
* Draw a cube ... VBO
*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// define and initialize initial and final
// points for the position interpolation
GLfloat startEndPoints[2][3] =
{{-3.0, 1.0, 0.0}, {3.0, 1.0, 0.0}};

//current step of the interpolation
static float currAlpha = 0;

// display function
void display(void)
{

    int currInd;
    // current position and angle.
    GLfloat lightPos[4];
    // fourth homogeneous coordinate
    lightPos[3] = 1.0;

    // Material properties
    float matAmbAndDif[] = {1.0, 1.0, 0.0, 1.0};
    float matSpec[] = {0.0, 1.0, 0.0, 1.0};
    float matShine[] = {10.0};

    // update the position
    for(currInd = 0; currInd < 3; currInd++)
    {
        lightPos[currInd] = (1-currAlpha)*startEndPoints[0][currInd] +
                            currAlpha * startEndPoints[1][currInd];
    };

    // position light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glLoadIdentity();
//    gluLookAt(0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0);

    glPushMatrix(); //cubo interno
    glTranslatef(0.0, 0.0, 0.0);
    glutWireCube(0.1);

    glPushMatrix(); //cubo esterno
    glutWireCube(0.8);
    glTranslatef(0.0, 0.0, 0.0);


    // Material properties of the box.
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);


    // let there be light
    glEnable(GL_LIGHT0);

    //glPopMatrix();


    //glPopMatrix();
    //glPushMatrix();
   // glTranslatef(-0.0, 0.0, 0.0);

    glFlush();
    //glPopMatrix();

    //glutPostRedisplay();

    // flush graphics objects immediately
    //glFinish();

}

void init (void)
{
    // global ambient light
    float globAmb[] = {0.0, 0.0, 0.0, 1.0};

    // Light property vectors.
    float lightAmb[] = {0.0, 0.0, 0.0, 1.0};
    float lightDif[] = {0.0, 0.0, 0.0, 1.0};
    float lightSpec[] = {0.0, 0.0, 0.0, 1.0};
    //glClearColor(1.0, 0.0, 0.0, 0.0);

    glFrustum(-0.4, 0.4, -0.4, 0.4, 0.1, 4.0);

    // select clearing color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    // Turn on OpenGL lighting.
    //glEnable(GL_LIGHTING);

    // Set properties of light number 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

    // Global ambient light.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);

    // Enable two-sided lighting.
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    // Enable local viewpoint.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // set line width (IN PIXELS)
    glLineWidth(2);

    // set shading model
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);

}

GLfloat z = 0.0;
GLfloat x2 = 0.0;
GLfloat y2 = 0.0;
GLfloat speed = 0.2;
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    fprintf(stderr, "keyInput\n");
    switch(key)
    {
        case 27:
            // ESC
            exit(0);
            break;

        case '1':

            gluLookAt(0.0, 0.0, -0.1, 0.0, 0.0, -0.8, -3.0, 0.0, 0.0);
            glutPostRedisplay();
            break;

        case 's':

            glPopMatrix();
            glPushMatrix();

            glTranslatef(0.0, 0.0, z -= speed);
            fprintf(stderr, "z: %f\n", z);
            glutPostRedisplay();
            break;

        case 'w':

            glPopMatrix();
            glPushMatrix();

            glTranslatef(0.0, 0.0, z += speed);
            fprintf(stderr, "z: %f\n", z);
            glutPostRedisplay();
            break;

        case 'a':

            glPopMatrix();
            glPushMatrix();

            glTranslatef(x2 += speed, 0.0, 0.0);
            fprintf(stderr, "x: %f\n", x2);
            glutPostRedisplay();
            break;

        case 'd':

            glPopMatrix();
            glPushMatrix();

            glTranslatef(x2 -= speed, 0.0, 0.0);
            fprintf(stderr, "x: %f\n", x2);
            glutPostRedisplay();
            break;

        default:
            // do nothing
            break;
    }
}

GLfloat angle = 0.0;
GLfloat rotation = 1.2;

void mouseInput(int button,int state,int x,int y) //da modificare
{
    fprintf(stderr, "mouseInput\n");
	switch(button)
	{
        case GLUT_LEFT_BUTTON:

            glPopMatrix();
            glPushMatrix();
            glRotatef(angle += rotation, 0.0, 1.0, 0.0);
            fprintf(stderr, "angle: %f\n", angle);
            glutPostRedisplay();
    //		if(state==GLUT_DOWN)
    //			glutIdleFunc(spinDisplay);
    //            fprintf(stderr, "state==GLUT_DOWN");
            break;

        case GLUT_RIGHT_BUTTON:

            glPopMatrix();
            glPushMatrix();
            glRotatef(angle -= rotation, 0.0, 1.0, 0.0);
            fprintf(stderr, "angle: %f\n", angle);
            glutPostRedisplay();
    //		if(state==GLUT_DOWN)
    //			glutIdleFunc(spinDisplayReverse);
    //            fprintf(stderr, "state==GLUT_DOWN");
            break;

        default:
            break;
	}
}

void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        //doSomething();
        break;
    case GLUT_KEY_RIGHT:
        //doSomething();
        break;

    case GLUT_KEY_UP:

        glPopMatrix();
        glPushMatrix();

        glTranslatef(0.0, y2 -= speed, 0.0);
        fprintf(stderr, "y: %f\n", y2);
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:

        glPopMatrix();
        glPushMatrix();

        glTranslatef(0.0, y2 += speed, 0.0);
        fprintf(stderr, "y: %f\n", y2);
        glutPostRedisplay();
        break;
    }
}

// Window size and mode
int main(int argc, char** argv)
{
    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // set display mode
    // GLUT_SINGLE = single buffer window
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize (1024, 576);
    glutInitWindowPosition (100, 100);
    //glutCreateWindow ("Un saluto dal vostro spidey di quartiere!");
    glutCreateWindow("Progetto grafica computerizzata");

    // keyboard handling function
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(SpecialKeys);

    //glutMouseFunc(mouse(xpos, ypos));
    // Here we add support for GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    }
    else
    {
        printf("GLEW init success\n");
    };

    // Call initialization routinesx
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseInput);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

