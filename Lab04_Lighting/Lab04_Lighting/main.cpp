//
//  main.cpp
//  Lab04_Lighting
//
//  Created by yoonjae Cho on 24/10/2017.
//  Copyright © 2017 yoonjae Cho. All rights reserved.
//

#include <GLUT/glut.h>

void display() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    gluLookAt(50, 50, 50, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-300.0, 0.0, 0.0);  glVertex3f(300.0, 0.0, 0.0); // X
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -300.0, 0.0);  glVertex3f(0.0, 300.0, 0.0); // Y
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -300.0);  glVertex3f(0.0, 0.0, 300.0); // Z
    glEnd();
    glPopMatrix();

    // Light
    glPushMatrix();
    GLfloat diffuse0[4] = {1.0, 0.9, 0.6, 1.0};
    GLfloat ambient0[4] = {0.2, 0.2, 0.2, 1.0}; // 주변광
    GLfloat specular0[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat emission[4] = {(float)234/255, (float)239/255, (float)179/255, 1.0};
    GLfloat light0_pos[4] = {0.0, 0.0, 0.0, 1.0};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    
    glutSolidSphere(5, 100, 100);
    glPopMatrix();
    
    
    // Material 1
    glPushMatrix();
    GLfloat diffuse1[4] = {(float)234/255, (float)239/255, (float)179/255, 1.0};
    GLfloat ambient1[4] = {0.1, 0.1, 0.1, 1.0};
    GLfloat specular1[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat material_emission1[4] = {0.0, 0.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse1);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_emission1);

    glScalef(0.7, 0.7, 0.7);
    glTranslatef(30, 30, 0);

    glutSolidSphere(5, 100, 100);

    glPopMatrix();
    
    // Material 2
    glPushMatrix();
    GLfloat diffuse2[4] = {(float)234/255, (float)239/255, (float)179/255, 1.0};
    GLfloat ambient2[4] = {0.1, 0.1, 0.1, 1.0};
    GLfloat specular2[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat material_emission2[4] = {0.0, 0.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_emission2);

    glTranslatef(-10, 0, -10);
    glutSolidSphere(5, 100, 100);

    glPopMatrix();
    
    glFlush();
}

void reshape(int w, int h) {
    float ratio = w / (float) h;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 10, 100);
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Lab4_Lighting");
    
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
