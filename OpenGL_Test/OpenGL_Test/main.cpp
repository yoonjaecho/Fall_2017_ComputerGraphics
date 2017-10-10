//
//  main.cpp
//  OpenGL_Test
//
//  Created by yoonjae Cho on 05/10/2017.
//  Copyright © 2017 yoonjae Cho. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>

using namespace std;

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    
    glutCreateWindow("OpenGL Drawing Example");
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    
    return 0;
}
