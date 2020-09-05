/*
 * OpenGL: lighting and shading
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// define and initialize initial and final
// points for the position interpolation
GLfloat startEndPoints[2][3] =
{{-3.0, 1.0, 0.0}, {3.0, 1.0, 0.0}};

// center and radius of circular trajectory
GLfloat centerPoint[3] = {0.0, 0.0, -3.0};
GLfloat radius = 1.0;

// define and initialize initial and final
// points for the position interpolation
GLfloat startEndAngles[2][3] =
{{0.0, 60.0, 0.0}, {0.0, 0.0, 0.0}};

// define and initialize initial and final
// points for the position interpolation
// (alpha,beta,gamma) is equivalent to (180+alpha, -beta+180, 180+gamma)
GLfloat startEndAngles1[2][3] =
{{180.0, 120.0, 180.0}, {0.0, 0.0, 0.0}};
// number of steps for the interpolation
#define DELTA   (1.0/50.0)
//current step of the interpolation
static float currAlpha = 0;

// display routine
void display(void)
{
    int currInd;
    // number of slices and stacks of the glut sphere
    GLfloat nSlices=100.0, nStacks=100.0;
 // current position and angle.
    GLfloat currPos[3], currAngle[3], currAngle1[3], currPos2D[2];
    // current position and angle.
    GLfloat lightPos[4];
    // fourth homogeneous coordinate
    lightPos[3] = 1.0;

    // Material properties
    float matAmbAndDif[] = {1.0, 1.0, 0.0, 1.0};
    float matSpec[] = {0.0, 1.0, 0.0, 1.0};
    float matShine[] = {25.0};

     // update the position --> prende i valori della matrice startEndPoints e li carica nelle prime tre posizioni del vettore lightPos[4]
    for(currInd = 0; currInd < 3; currInd++) {
        lightPos[currInd] = (1-currAlpha)*startEndPoints[0][currInd] +
        currAlpha * startEndPoints[1][currInd];
        fprintf(stderr, "lightPos[%d]%f\n", currInd, lightPos[currInd]);
                        // interpolate first angle
        currAngle[currInd] = (1-currAlpha)*startEndAngles[0][currInd] +
            currAlpha * startEndAngles[1][currInd];

        fprintf(stderr, "currAngle[%d]%f\n", currInd, currAngle[currInd]);
                // interpolate second angle
        currAngle1[currInd] = (1-currAlpha)*startEndAngles1[0][currInd] +
            currAlpha * startEndAngles1[1][currInd];
        fprintf(stderr, "currAngle1[%d]%f\n", currInd, currAngle1[currInd]);
    }

    // position light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Push initial state on the stack
    glPushMatrix();

    // place objects in the scene
    glTranslatef(0.0, 0.0, -5.0);
    //glRotatef(90, 1.0, 0.0, 0.0);

    // Material properties of the box.
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    // let there be light
    glEnable(GL_LIGHT0);

    // draw sphere
    glutSolidSphere(1.0, nSlices, nStacks);


    gluLookAt(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
    // flush graphics objects immediately
    glFlush();

    // pop initial state from the stack
    glPopMatrix();
}

void init (void)
{
    GLenum glErr;

    // global ambient light
    float globAmb[] = {0.0, 0.0, 0.0, 1.0}; // RGB

    // Light property vectors.
    float lightAmb[] = {0.9, 0.0, 0.0, 1.0};
    float lightDif[] = {0.9, 0.0, 0.0, 1.0};
    float lightSpec[] = {0.0, 0.9, 0.0, 1.0};

    // select clearing color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1, 10.0);

    // ... it does not hurt to check that everything went OK
    if ((glErr=glGetError()) != 0) {
        printf("Errore = %d \n", glErr);
        exit(-1);
    }

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Turn on wireframe mode (only for debugging purposes)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);

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

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key) {
        case 27:
            // ESC
            exit(0);
            break;
        case '1':
            // Key 1
            // update alpha and display
            currAlpha += DELTA;
            if (currAlpha > 1.0) currAlpha = 0.0;
            glutPostRedisplay();
            break;

        default:
            // do nothing
            break;
    }
}
GLfloat angle = 0.0;
GLfloat rotation = 0.9;

GLfloat scale = 1.0;
GLfloat scroll = 0.0;
GLfloat maxScroll = 7.0;

void mouseInput(int button,int state,int x,int y) //da modificare
{
    fprintf(stderr, "mouseInput\n");
    fprintf(stderr, "button: %d\n", button);
    switch(button)
    {
    case 3:
        //SCROLL IN
        if(scroll < maxScroll)
        {
            glScalef(2.0, 2.0, 0.0);
            scroll += scale;
            fprintf(stderr, "scroll: %f\n", scroll);
            glutPostRedisplay();
        }


        break;

    case 4:
        //SCROLL OUT
        if(scroll > -maxScroll)
        {
            glScalef(0.5, 0.5, 0.0);
            scroll -= scale;
            fprintf(stderr, "scroll: %f\n", scroll);
            glutPostRedisplay();
        }


        break;

    case GLUT_LEFT_BUTTON:

        currAlpha += DELTA;

        fprintf(stderr, "currAlpha: %f\n", currAlpha);
        glutPostRedisplay();
        break;

        break;

    case GLUT_RIGHT_BUTTON:

        currAlpha -= DELTA;

        fprintf(stderr, "currAlpha: %f\n", currAlpha);
        glutPostRedisplay();
        break;

    default:
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow ("OpenGL Window");

    // keyboard handling function
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseInput);

    // Here we add support for GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    } else {
        printf("GLEW init success\n");
    };

    // Call initialization routines
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

