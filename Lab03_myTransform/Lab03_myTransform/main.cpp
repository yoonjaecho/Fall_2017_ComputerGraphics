//
//  main.cpp
//  Lab03_myTransform
//
//  Created by yoonjae Cho on 17/10/2017.
//  Copyright © 2017 yoonjae Cho. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "stdafx.h"

using namespace std;

struct Matrix {
    string state;
    vector<vector<float>> form;
};
vector<Matrix> stack;

int MATRIX_MODE = GL_DEFAULT_MODE;

void mySetMatrixMode(int mode);
void myLoadIdentity();
void myPushMatrix();
void myPopMatrix();
void myMatrixMul(Matrix &matrix);
void myRunMatrix(float x, float y, float z);
void myTranslateX(float dist);
void myTranslateY(float dist);
void myTranslateZ(float dist);
void myRotateX(float degree);
void myRotateY(float degree);
void myRotateZ(float degree);
void myScaleX(float scale);
void myScaleY(float scale);
void myScaleZ(float scale);

void showStack();

int main(int argc, const char * argv[]) {
    mySetMatrixMode(GL_MODELVIEW);
    
    myLoadIdentity();
    myPushMatrix();
    showStack();
    
    myScaleX(10);
    myPushMatrix();
    showStack();
    
    myRotateZ(-90);
    myTranslateY(10);
    myRotateZ(90);
    myRunMatrix(0, 0, 0);
    showStack();
    
    myPopMatrix();
    myPopMatrix();
    showStack();
    return 0;
}

void mySetMatrixMode(int mode) {
    MATRIX_MODE = mode;
    stack.clear();
}

void myLoadIdentity() {
    cout << "Called myLoadIdentity" << endl;
    vector<vector<float>> identity = {
        {1.0, 0, 0, 0},
        {0, 1.0, 0, 0},
        {0, 0, 1.0, 0},
        {0, 0, 0, 1.0}
    };
    
    stack.push_back({"I", identity});
}

void myPushMatrix() {
    cout << "Called myPushMatrix" << endl;
    stack.push_back(STACK_TOP);
}

void myPopMatrix() {
    cout << "Called myPopMatrix" << endl;
    stack.pop_back();
}

void myMatrixMul(Matrix &matrix) {
    vector<vector<float>> newTop(MATRIX_SIZE, vector<float>(MATRIX_SIZE, 0));
    
    for(int i=0; i<MATRIX_SIZE; i++)
        for(int j=0; j<MATRIX_SIZE; j++)
            for(int k=0; k<MATRIX_SIZE; k++)
                newTop[i][j] += STACK_TOP.form[i][k] * matrix.form[k][j];
    
    STACK_TOP.state += "*" + matrix.state;
    STACK_TOP.form = newTop;
}

void myRunMatrix(float x, float y, float z) {
    vector<vector<float>> vertex = {
        {x}, {y}, {z}, {1}
    }, result(MATRIX_SIZE, vector<float>(VECTOR_DIM, 0));
    
    for(int i=0; i<MATRIX_SIZE; i++)
        for(int j=0; j<VECTOR_DIM; j++)
            for(int k=0; k<MATRIX_SIZE; k++)
                result[i][j] += STACK_TOP.form[i][k] * vertex[k][j];
    
    cout << "(" << x << ", " << y << ", " << z << ") -> ";
    cout << "(" << result[0][0] << ", " << result[1][0] << ", " << result[2][0] << ")\n" << endl;
}

void myTranslateX(float dist) {
    cout << "Called myTranslateX" << endl;
    vector<vector<float>> mat = {
        {1.0, 0, 0, dist},
        {0, 1.0, 0, 0},
        {0, 0, 1.0, 0},
        {0, 0, 0, 1.0}
    };
    Matrix transX = {"Tx(" + to_string((int)dist) + ")", mat};
    myMatrixMul(transX);
}

void myTranslateY(float dist) {
    cout << "Called myTranslateY" << endl;
    vector<vector<float>> mat = {
        {1.0, 0, 0, 0},
        {0, 1.0, 0, dist},
        {0, 0, 1.0, 0},
        {0, 0, 0, 1.0}
    };
    Matrix transY = {"Ty(" + to_string((int)dist) + ")", mat};
    myMatrixMul(transY);
}

void myTranslateZ(float dist) {
    cout << "Called myTranslateZ" << endl;
    vector<vector<float>> mat = {
        {1.0, 0, 0, 0},
        {0, 1.0, 0, 0},
        {0, 0, 1.0, dist},
        {0, 0, 0, 1.0}
    };
    Matrix transZ = {"Tz(" + to_string((int)dist) + ")", mat};
    myMatrixMul(transZ);
}

void myRotateX(float degree) {
    cout << "Called myRotateX" << endl;
    vector<vector<float>> mat = {
        {1.0, 0, 0, 0},
        {0, cos(degree/180 * PI), -sin(degree/180 * PI), 0},
        {0, sin(degree/180 * PI), cos(degree/180 * PI), 0},
        {0, 0, 0, 1.0}
    };
    Matrix rotateX = {"Rx(" + to_string((int)degree) + ")", mat};
    myMatrixMul(rotateX);
}

void myRotateY(float degree) {
    cout << "Called myRotateY" << endl;
    vector<vector<float>> mat = {
        {cos(degree/180 * PI), 0, sin(degree/180 * PI), 0},
        {0, 1.0, 0, 0},
        {-sin(degree/180 * PI), 0, cos(degree/180 * PI), 0},
        {0, 0, 0, 1.0}
    };
    Matrix rotateY = {"Ry(" + to_string((int)degree) + ")", mat};
    myMatrixMul(rotateY);
}

void myRotateZ(float degree) {
    cout << "Called myRotateZ" << endl;
    vector<vector<float>> mat = {
        {cos(degree/180 * PI), -sin(degree/180 * PI), 0, 0},
        {sin(degree/180 * PI), cos(degree/180 * PI), 0, 0},
        {0, 0, 1.0, 0},
        {0, 0, 0, 1.0}
    };
    Matrix rotateZ = {"Rz(" + to_string((int)degree) + ")", mat};
    myMatrixMul(rotateZ);
}

void myScaleX(float scale) {
    cout << "Called myScaleX" << endl;
    vector<vector<float>> mat = {
        {scale, 0, 0, 0},
        {0, 1.0, 0, 0},
        {0, 0, 1.0, 0},
        {0, 0, 0, 1.0}
    };
    Matrix scaleX = {"Sx(" + to_string((int)scale) + ")", mat};
    myMatrixMul(scaleX);
}

void myScaleY(float scale) {
    cout << "Called myScaleY" << endl;
    vector<vector<float>> mat = {
        {1.0, 0, 0, 0},
        {0, scale, 0, 0},
        {0, 0, 1.0, 0},
        {0, 0, 0, 1.0}
    };
    Matrix scaleY = {"Sy(" + to_string((int)scale) + ")", mat};
    myMatrixMul(scaleY);
}

void myScaleZ(float scale) {
    cout << "Called myScaleZ" << endl;
    vector<vector<float>> mat = {
        {1.0, 0, 0, 0},
        {0, 1.0, 0, 0},
        {0, 0, scale, 0},
        {0, 0, 0, 1.0}
    };
    Matrix scaleZ = {"Sz(" + to_string((int)scale) + ")", mat};
    myMatrixMul(scaleZ);
}

void showStack() {
    puts("-----Stack Top------");
    for(int sp=(int)stack.size()-1; sp>=0; sp--) {
        cout << "Matrix : " << stack[sp].state << endl;
        for(int i=0; i<MATRIX_SIZE; i++) {
            for(int j=0; j<MATRIX_SIZE; j++) {
                cout << stack[sp].form[i][j] << " ";
            }
            puts("");
        }
        puts("--------------------");
    }
    puts("");
}
