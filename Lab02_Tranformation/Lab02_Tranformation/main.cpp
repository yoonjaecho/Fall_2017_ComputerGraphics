//
//  main.cpp
//  Lab02_Tranformation
//
//  Created by yoonjae Cho on 10/10/2017.
//  Copyright © 2017 yoonjae Cho. All rights reserved.
//

#include <GLUT/glut.h>

void display() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
    
    glutWireSphere(1, 15, 15);
    
    glRotatef(-45, 0, 0, 1);
    glTranslatef(0, 10, 0);
    glScalef(2, 2, 2);
    
    glutWireSphere(1, 15, 15);
    
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
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Lab2_Tranformation");
    
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
