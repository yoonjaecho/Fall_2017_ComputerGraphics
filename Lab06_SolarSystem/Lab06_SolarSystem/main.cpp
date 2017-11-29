//
//  main.cpp
//  Lab06_SolarSystem
//
//  Created by yoonjae Cho on 14/11/2017.
//  Copyright © 2017 yoonjae Cho. All rights reserved.
//

#include <GLUT/glut.h>

float rotationOfSun = 0.0; // 자전
float rotationOfMercury = 0;
float rotationOfVenus = 0;
float rotationOfEarth = 0;
float rotationOfMars = 0;
float rotationOfJupiter = 0;
float rotationOfSaturn = 0;
float rotationOfUranus = 0;
float rotationOfNeptune = 0;

float revolutionOfMercury = 0; // 공전
float revolutionOfVenus = 0;
float revolutionOfEarth = 0;
float revolutionOfMars = 0;
float revolutionOfJupiter = 0;
float revolutionOfSaturn = 0;
float revolutionOfUranus = 0;
float revolutionOfNeptune = 0;

float revolutionOfEarthMoon = 0; // 위성 공전
float revolutionOfJupiterSatellite1 = 0;
float revolutionOfJupiterSatellite2 = 0;

GLfloat emission_material[] = {0.0, 0.0, 0.0, 1.0};

GLfloat ambient0[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse0[] = {1.0, 0.9, 0.6, 1.0};
GLfloat specular0[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light0_pos[] = {0.0, 0.0, 0.0, 1.0};

GLfloat ambient1[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse1[] = {1.0, 0.8, 0.0, 1.0};
GLfloat specular1[] = {0.2, 0.4, 0.7, 1.0};
GLfloat shine = 100.0;

GLfloat ambient2[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse2[] = {0.8, 0.8, 0.3, 1.0};
GLfloat specular2[] = {0.1, 0.2, 0.3, 1.0};

GLfloat ambient3[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse3[] = {0.3, 0.4, 0.9, 1.0};
GLfloat specular3[] = {0.1, 0.2, 0.3, 1.0};

GLfloat ambient4[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse4[] = {0.8, 0.6, 0.9, 1.0};
GLfloat specular4[] = {0.1, 0.2, 0.3, 1.0};

GLfloat ambient5[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse5[] = {(float)209/255, (float)162/255, (float)52/255, 1.0};
GLfloat specular5[] = {0.1, 0.4, 0.3, 1.0};

GLfloat ambient6[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse6[] = {(float)229/255, (float)213/255, (float)36/255, 1.0};
GLfloat specular6[] = {0.1, 0.2, 0.3, 1.0};

GLfloat ambient7[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse7[] = {(float)24/255, (float)203/255, (float)226/255, 1.0};
GLfloat specular7[] = {0.1, 0.2, 0.3, 1.0};

GLfloat ambient8[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuse8[] = {(float)5/255, (float)156/255, (float)175/255, 1.0};
GLfloat specular8[] = {0.1, 0.2, 0.3, 1.0};

float camera_pos[3] = {0, 25, 25};

void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void idle();

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Lab 06 Solar System");
    
    glClearColor(0, 0, 0, 0);
    glColor3f(1.0, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2], 0, 0, 0, 0, 1, 0);
    
    // 태양
    glPushMatrix();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    
        GLfloat emission_light[] = {1.0, 0.3, 0.0, 1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission_light);
    
        glScalef(2, 2, 2);
        glRotated(rotationOfSun, 0, 0, 1);
        glutSolidSphere(1, 100, 100);
    glPopMatrix();
    
    // 수성
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);
    
        glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
    
        glRotatef(revolutionOfMercury, 0, 1, 0);
        glTranslatef(0, 0, 5);
        glRotatef(rotationOfMercury, 0, 0, 1);
    
        glutSolidSphere(0.5, 100, 100);
    glPopMatrix();
    
    // 금성
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);
    
        glRotatef(revolutionOfVenus, 0, 1, 0);
        glTranslatef(0, 0, 5.5);
        glRotatef(rotationOfVenus, 0, 0, 1);
    
        glutSolidSphere(0.43, 100, 100);
    glPopMatrix();
    
    // 지구
    glPushMatrix();
        glRotatef(revolutionOfEarth, 0, 1, 0);
        glTranslatef(0, 0, 6.5);

        // 위성
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
            glMaterialf(GL_FRONT, GL_SHININESS, shine);
            glRotatef(revolutionOfEarthMoon, 0, 1, 1);
            glTranslatef(1.0, 0, 0);
            glRotatef(6, 0, 1, 0);
            glutSolidSphere(0.15, 100, 100);
        glPopMatrix();

        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular3);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);

        glRotatef(rotationOfEarth, 0, 0, 1);
        glutSolidSphere(0.4, 100, 100);
    glPopMatrix();
    
    // 화성
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient4);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse4);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular4);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);

        glRotatef(revolutionOfMars, 0, 1, 0);
        glTranslatef(0, 0, 7);
        glRotatef(rotationOfMars, 0, 0, 1);
        glutSolidSphere(0.38, 100, 100);
    glPopMatrix();
    
    // 목성
    glPushMatrix();
        glRotatef(revolutionOfJupiter, 0, 1, 0);
        glTranslatef(0, 0, 9);
    
        // 위성 1
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
            glMaterialf(GL_FRONT, GL_SHININESS, shine);
            glRotatef(revolutionOfJupiterSatellite1, 0, 1, 1);
            glTranslatef(1.0, 0, 0);
            glRotatef(6, 0, 1, 0);
            glutSolidSphere(0.11, 100, 100);
        glPopMatrix();
    
        // 위성 2
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient4);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse4);
            glMaterialfv(GL_FRONT, GL_SPECULAR, specular4);
            glMaterialf(GL_FRONT, GL_SHININESS, shine);
            glRotatef(revolutionOfJupiterSatellite2, 0, 1, 1);
            glTranslatef(1.0, 1.0, 0);
            glRotatef(6, 0, 1, 0);
            glutSolidSphere(0.08, 100, 100);
        glPopMatrix();
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient5);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse5);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular5);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);
    
        glRotatef(rotationOfJupiter, 0, 0, 1);
        glutSolidSphere(0.7, 100, 100);
    glPopMatrix();
    
    
    // 토성
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient6);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse6);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular6);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);
    
        glRotatef(revolutionOfSaturn, 0, 1, 0);
        glTranslatef(0, 0, 11);
        glRotatef(-30, 0, 1, 0);
        glRotatef(rotationOfSaturn, 0, 0, 1);
    
        GLUquadricObj *obj = gluNewQuadric();
        gluDisk(obj, 1.0, 1.5, 100, 40);
    
        glutSolidSphere(0.7, 100, 100);
    glPopMatrix();
    
    // 천왕성
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient7);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse7);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular7);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);
    
        glRotatef(revolutionOfUranus, 0, 1, 0);
        glTranslatef(0, 0, 12);
        glRotatef(rotationOfUranus, 0, 0, 1);
        glutSolidSphere(0.3, 100, 100);
    glPopMatrix();
    
    // 명왕성
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient8);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse8);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular8);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);
    
        glRotatef(revolutionOfNeptune, 0, 1, 0);
        glTranslatef(0, 0, 13);
        glRotatef(rotationOfNeptune, 0, 0, 1);
        glutSolidSphere(0.3, 100, 100);
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int w, int h){
    float ratio = w/(float)h;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 10, 100);
}

void idle(){
    rotationOfSun += 0.09;
    rotationOfSun = rotationOfSun >= 360? rotationOfSun - 360 : rotationOfSun;
    
    // 자전
    rotationOfMercury += 0.059; // 59일
    rotationOfMercury = rotationOfMercury >= 360? rotationOfMercury - 360 : rotationOfMercury;
    rotationOfVenus -= 0.243;
    rotationOfVenus = rotationOfVenus >= 360? rotationOfVenus - 360 : rotationOfVenus;
    rotationOfEarth += 0.001;
    rotationOfEarth = rotationOfEarth >= 360? rotationOfEarth - 360 : rotationOfEarth;
    rotationOfMars += 0.00103;
    rotationOfMars = rotationOfMars >= 360? rotationOfMars - 360 : rotationOfMars;
    rotationOfJupiter += 0.00041;
    rotationOfJupiter = rotationOfJupiter >= 360? rotationOfJupiter - 360 : rotationOfJupiter;
    rotationOfSaturn += 0.00044;
    rotationOfSaturn = rotationOfSaturn >= 360? rotationOfSaturn - 360 : rotationOfSaturn;
    rotationOfUranus += 0.00065;
    rotationOfUranus = rotationOfUranus >= 360? rotationOfUranus - 360 : rotationOfUranus;
    rotationOfNeptune += 0.00077;
    rotationOfNeptune = rotationOfNeptune >= 360? rotationOfNeptune - 360 : rotationOfNeptune;
    
    // 공전
    revolutionOfMercury += 2.4; // 0.24년
    revolutionOfMercury = revolutionOfMercury >= 360? revolutionOfMercury - 360 : revolutionOfMercury;
    revolutionOfVenus += 6.2;
    revolutionOfVenus = revolutionOfVenus >= 360? revolutionOfVenus - 360 : revolutionOfVenus;
    revolutionOfEarth += 0.1;
    revolutionOfEarth = revolutionOfEarth >= 360? revolutionOfEarth - 360 : revolutionOfEarth;
    revolutionOfMars += 0.188;
    revolutionOfMars = revolutionOfMars >= 360? revolutionOfMars - 360 : revolutionOfMars;
    revolutionOfJupiter += (11.86 / 365) * 0.1; // 11.86일
    revolutionOfJupiter = revolutionOfJupiter >= 360? revolutionOfJupiter - 360 : revolutionOfJupiter;
    revolutionOfSaturn += (29.46 / 365) * 0.1;
    revolutionOfSaturn = revolutionOfSaturn >= 360? revolutionOfSaturn - 360 : revolutionOfSaturn;
    revolutionOfUranus += (84.02 / 365) * 0.1;
    revolutionOfUranus = revolutionOfUranus >= 360? revolutionOfUranus - 360 : revolutionOfUranus;
    revolutionOfNeptune += (164.77 / 365) * 0.1;
    revolutionOfNeptune = revolutionOfNeptune >= 360? revolutionOfNeptune - 360 : revolutionOfNeptune;
    
    // 위성 공전
    revolutionOfEarthMoon += 4.14;
    revolutionOfEarthMoon = revolutionOfEarthMoon >= 360? revolutionOfEarthMoon - 360 : revolutionOfEarthMoon;
    revolutionOfJupiterSatellite1 += 4.14;
    revolutionOfJupiterSatellite1 = revolutionOfJupiterSatellite1 >= 360? revolutionOfJupiterSatellite1 - 360 : revolutionOfJupiterSatellite1;
    revolutionOfJupiterSatellite2 += 4.14;
    revolutionOfJupiterSatellite2 = revolutionOfJupiterSatellite2 >= 360? revolutionOfJupiterSatellite2 - 360 : revolutionOfJupiterSatellite2;
    
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Zoom in
            camera_pos[2] += 10;
            break;
            
        case 'a':
            camera_pos[0] -= 1;
            camera_pos[1] -= 1;
            break;
            
        case 's': // Zoom out
            camera_pos[2] -= 10;
            break;
            
        case 'd':
            camera_pos[0] += 1;
            camera_pos[1] += 1;
            break;
            
        default:
            break;
    }
    
    glutPostRedisplay();
}
