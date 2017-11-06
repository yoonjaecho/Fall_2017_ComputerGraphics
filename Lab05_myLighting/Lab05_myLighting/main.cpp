//
//  main.cpp
//  Lab04_myLighting
//
//  Created by yoonjae Cho on 31/10/2017.
//  Copyright © 2017 yoonjae Cho. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "stdafx.h"

using namespace std;

struct Vertex {
    float x, y, z, w;
} L, N, V, R;

struct Light {
    Vertex ambient;
    Vertex diffuse;
    Vertex specular;
    Vertex attenuation;
};

// Max light size is 8
Light lights[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

void mySetLight(int ID, string prop, Vertex &coef);
void myAmbient(int ID, Vertex &coef);
void myDiffuse(int ID, Vertex &coef);
void mySpecular(int ID, Vertex &coef);
float myAttenuation(float ka, float kb, float kc, float dist);
Vertex myLighting(int ID);

float dotProduct(Vertex a, Vertex b);

int main(int argc, char * argv[]) {
    
    // Init value of Light, Normal, View vector
    L = {1, 1, 1, 0};
    N = {0, 1, 0, 0};
    V = {-1, -1, -1, 0};
    
    printf("* Input parameter\n\n");
    printf("Light : (%lf, %lf, %lf)\n", L.x, L.y, L.z);
    printf("Normal : (%lf, %lf, %lf)\n", N.x, N.y, N.z);
    printf("View : (%lf, %lf, %lf)\n", V.x, V.y, V.z);
    
    // Get Reflection vector from L, N
    float LN = 2 * dotProduct(L, N);
    R = {
        LN * N.x - L.x,
        LN * N.y - L.y,
        LN * N.z - L.z,
        LN * N.w - L.w
    };
    
    Vertex ambient0 = {0.2, 0.2, 0.2, 1.0};
    mySetLight(GL_LIGHT0, "AMB", ambient0);
    Vertex diffuse0 = {1.0, 0.9, 0.6, 1.0};
    mySetLight(GL_LIGHT0, "DIFF", diffuse0);
    Vertex specular0 = {1.0, 1.0, 1.0, 1.0};
    mySetLight(GL_LIGHT0, "SPEC", specular0);
    
    printf("LIGHT0 ambient : (%lf, %lf, %lf)\n", ambient0.x, ambient0.y, ambient0.z);
    printf("LIGHT0 diffuse : (%lf, %lf, %lf)\n", diffuse0.x, diffuse0.y, diffuse0.z);
    printf("LIGHT0 specular : (%lf, %lf, %lf)\n", specular0.x, specular0.y, specular0.z);
    
    Vertex result = myLighting(GL_LIGHT0);
    printf("\n* Result : %lf, %lf, %lf\n",
           result.x, result.y, result.z);
    
    return 0;
}

void mySetLight(int ID, string prop, Vertex &coef) {
    if(!prop.compare("AMB"))
        myAmbient(ID, coef);
    else if(!prop.compare("DIFF"))
        myDiffuse(ID, coef);
    else if(!prop.compare("SPEC"))
        mySpecular(ID, coef);
}

void myAmbient(int ID, Vertex &coef) {
    lights[ID].ambient = coef;
}

void myDiffuse(int ID, Vertex &coef) {
    float LN = dotProduct(L, N);
    printf("L * N : %lf\n", LN);
    coef.x *= LN; coef.y *= LN; coef.z *= LN; coef.w = 1;
    lights[ID].diffuse = coef;
}

void mySpecular(int ID, Vertex &coef) {
    float RVa = pow(dotProduct(R, V), 2); // alpha = 2
    printf("(R * V) ^ a : %lf\n", RVa);
    coef.x *= RVa; coef.y *= RVa; coef.z *= RVa; coef.w = 1;
    lights[ID].specular = coef;
}

float myAttenuation(float ka, float kb, float kc, float dist) {
    return 1 / (ka + kb * dist + kc * dist * dist);
}

Vertex myLighting(int ID) {
    Vertex result;
    
    // Distance term at diffuse & specular
    float distanceTerm = myAttenuation(0, 1, 1, 10);
    result.x = lights[ID].ambient.x +
               lights[ID].diffuse.x * distanceTerm +
               lights[ID].specular.x * distanceTerm;
    result.y = lights[ID].ambient.y +
               lights[ID].diffuse.y * distanceTerm +
               lights[ID].specular.y * distanceTerm;
    result.z = lights[ID].ambient.z +
               lights[ID].diffuse.z * distanceTerm +
               lights[ID].specular.z * distanceTerm;
    return result;
}

float dotProduct(Vertex a, Vertex b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
