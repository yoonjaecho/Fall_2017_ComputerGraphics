//
//  main.cpp
//  Lab07_TexturedSolarSystem
//
//  Created by yoonjae Cho on 21/11/2017.
//  Copyright © 2017 yoonjae Cho. All rights reserved.
//

#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>

using namespace std;

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

float camera_pos[3] = {0, 25, 25};

const int numberOfTexture = 12;

unsigned int ids[numberOfTexture];
GLuint tex[numberOfTexture];
GLUquadricObj *objs[numberOfTexture];

void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void idle();

void loadAllTexture();
GLuint loadRawTexture(const char * filename, int width, int height);

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Lab 07 Textured Solar System");
    
    glClearColor(0, 0, 0, 0);
    glColor3f(1.0, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    loadAllTexture();
    
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
    glEnable(GL_TEXTURE_2D);
    
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
    
        GLfloat emission_light[] = {1.0, 0.2, 0.0, 1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission_light);
    
        glScalef(2, 2, 2);
        glRotated(rotationOfSun, 0, 0, 1);
    
        glBindTexture(GL_TEXTURE_2D, tex[0]);
        gluSphere(objs[0], 2, 100, 100);
    glPopMatrix();
    
    
    // 수성
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, emission_material);
    
        glRotatef(revolutionOfMercury, 0, 1, 0);
        glTranslatef(0, 0, 5);
        glRotatef(rotationOfMercury, 0, 0, 1);
    
        glBindTexture(GL_TEXTURE_2D, tex[1]);
        gluSphere(objs[1], 0.5, 100, 100);
    glPopMatrix();
    
    // 금성
    glPushMatrix();
        glRotatef(revolutionOfVenus, 0, 1, 0);
        glTranslatef(0, 0, 5.5);
        glRotatef(rotationOfVenus, 0, 0, 1);
    
        glBindTexture(GL_TEXTURE_2D, tex[2]);
        gluSphere(objs[2], 0.43, 100, 100);
    glPopMatrix();
    
    // 지구
    glPushMatrix();
        glRotatef(revolutionOfEarth, 0, 1, 0);
        glTranslatef(0, 0, 6.5);
    
        // 위성
        glPushMatrix();
            glRotatef(revolutionOfEarthMoon, 0, 1, 1);
            glTranslatef(1.0, 0, 0);
            glRotatef(6, 0, 1, 0);
            glBindTexture(GL_TEXTURE_2D, tex[4]);
            gluSphere(objs[4], 0.15, 100, 100);
        glPopMatrix();

        glRotatef(rotationOfEarth, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, tex[3]);
        gluSphere(objs[3], 0.4, 100, 100);
    glPopMatrix();
    
    // 화성
    glPushMatrix();
        glRotatef(revolutionOfMars, 0, 1, 0);
        glTranslatef(0, 0, 7);
        glRotatef(rotationOfMars, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, tex[5]);
        gluSphere(objs[5], 0.38, 100, 100);
    glPopMatrix();
    
    // 목성
    glPushMatrix();
        glRotatef(revolutionOfJupiter, 0, 1, 0);
        glTranslatef(0, 0, 9);
    
        // 위성 1
        glPushMatrix();
            glRotatef(revolutionOfJupiterSatellite1, 0, 1, 1);
            glTranslatef(1.0, 0, 0);
            glRotatef(6, 0, 1, 0);
            glBindTexture(GL_TEXTURE_2D, tex[7]);
            gluSphere(objs[7], 0.11, 100, 100);
        glPopMatrix();
    
        // 위성 2
        glPushMatrix();
            glRotatef(revolutionOfJupiterSatellite2, 0, 1, 1);
            glTranslatef(1.0, 1.0, 0);
            glRotatef(6, 0, 1, 0);
            glBindTexture(GL_TEXTURE_2D, tex[8]);
            gluSphere(objs[8], 0.08, 100, 100);
        glPopMatrix();
    
        glRotatef(rotationOfJupiter, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, tex[6]);
        gluSphere(objs[6], 0.7, 100, 100);
    glPopMatrix();
    
    
    // 토성
    glPushMatrix();
        glRotatef(revolutionOfSaturn, 0, 1, 0);
        glTranslatef(0, 0, 11);
        glRotatef(-30, 0, 1, 0);
        glRotatef(rotationOfSaturn, 0, 0, 1);
    
        GLUquadricObj *obj = gluNewQuadric();
        gluDisk(obj, 1.0, 1.5, 100, 40);
    
        glBindTexture(GL_TEXTURE_2D, tex[9]);
        gluSphere(objs[9], 0.7, 100, 100);
    glPopMatrix();
    
    // 천왕성
    glPushMatrix();
        glRotatef(revolutionOfUranus, 0, 1, 0);
        glTranslatef(0, 0, 12);
        glRotatef(rotationOfUranus, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, tex[10]);
        gluSphere(objs[10], 0.3, 100, 100);
    glPopMatrix();
    
    // 명왕성
    glPushMatrix();
        glRotatef(revolutionOfNeptune, 0, 1, 0);
        glTranslatef(0, 0, 13);
        glRotatef(rotationOfNeptune, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, tex[11]);
        gluSphere(objs[11], 0.3, 100, 100);
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

void loadAllTexture() {
    for(int i = 0; i <= numberOfTexture; i++) {
        objs[i] = gluNewQuadric();
        gluQuadricTexture(objs[i], GL_TRUE);
    }
    
    tex[0] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/sun.bmp", 1024, 512);
    tex[1] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/mercury.bmp", 1024, 512);
    tex[2] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/venus.bmp", 2500, 1250);
    tex[3] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/earth.bmp", 2048, 1024);
    tex[4] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/moon.bmp", 1024, 512);
    tex[5] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/mars.bmp", 1960, 988);
    tex[6] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/jupiter.bmp", 1024, 512);
    tex[7] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/europa.bmp", 1024, 512);
    tex[8] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/callisto.bmp", 2048, 1024);
    tex[9] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/saturn.bmp", 1024, 512);
    tex[10] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/uranus.bmp", 1024, 512);
    tex[11] = loadRawTexture("/Users/yoonjaecho/Desktop/Fall_2017_ComputerGraphics/Lab07_TexturedSolarSystem/Lab07_TexturedSolarSystem/res/neptune.bmp", 1024, 512);
}

GLuint loadRawTexture(const char * filename, int width, int height) {
    GLuint text;
    unsigned char * data;
    FILE * file;
    
    // open texture data
    file = fopen(filename, "rb");
    if(file == 0) {
        puts("FILE LOAD ERROR");
        return 0;
    }
    
    // allocate buffer
    data = (unsigned char *)malloc(width * height * 3);
    
    // read texture data
    fread(data, width * height * 3, 1, file);
    fclose(file);
    
    for(int i = 0; i < width * height ; ++i) {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];
        data[index] = R;
        data[index + 2] = B;
    }
    
    glGenTextures(1, &text);
    glBindTexture(GL_TEXTURE_2D, text);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    // free buffer
    free(data);
    return text;
}
