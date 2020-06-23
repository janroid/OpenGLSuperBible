//
//  main.cpp
//  GLDemo
//
//  Created by janroid on 2020/6/23.
//  Copyright © 2020年 janroid. All rights reserved.
//
#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLUT/GLUT.h>

GLShaderManager shaderManager;
GLBatch triangleBatch;
GLfloat sVerits[]= {
    0.1f, 0.1f, 0.0f,
    -0.1f, 0.1f, 0.0f,
    -0.1f, -0.1f, 0.0f,
    0.1f, -0.1f, 0.0f
};

void ChangeSize(int w, int h){
    glViewport(0, 0, w, h);
}

void RenderRence(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat reds[] = {1.0f, 0.0f, 0.0f, 1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, reds);
    triangleBatch.Draw();
    glutSwapBuffers();
}

void SetupRC(){
    glClearColor(0.0f,0.0f, 1.0f, 1.0f);
    shaderManager.InitializeStockShaders();
    triangleBatch.Begin(GL_TRIANGLE_FAN,4);
    triangleBatch.CopyVertexData3f(sVerits);
    triangleBatch.End();
}

void move(int key){
    float offset = 0.01f;
    float subX = 0.0f;
    float subY = 0.0f;
    
    if(key == GLUT_KEY_UP)
        subY += offset;
    if(key == GLUT_KEY_DOWN)
        subY -= offset;
    if(key == GLUT_KEY_LEFT)
        subX -= offset;
    if(key == GLUT_KEY_RIGHT)
        subX += offset;
    
    sVerits[0] += subX;
    if(sVerits[0] >1.0f){
        sVerits[0] = 1.0f;
        subX = 0.0f;
    }
    
    sVerits[3] += subX;
    if(sVerits[3] < -1.0f){
        sVerits[3] = -1.0f;
        sVerits[0] -= subX;
        subX = 0.0f;
    }
    sVerits[6] += subX;
    sVerits[9] += subX;
    
    sVerits[1] += subY;
    if(sVerits[1] > 1.0f){
        sVerits[1] = 1.0f;
        subY = 0.0f;
    }
    sVerits[7] += subY;
    if(sVerits[7] < -1.0f){
        sVerits[7] = -1.0f;
        sVerits[1] -= subY;
        subY = 0.0f;
    }
    sVerits[4] += subY;
    sVerits[10] += subY;
    
    triangleBatch.CopyVertexData3f(sVerits);
    glutPostRedisplay();
    
}

void keyListener(int key, int x, int y){
    move(key);
}


int main(int argc, char *argv[]){
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("My First Window");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderRence);
    glutSpecialFunc(keyListener);
    GLenum err = glewInit();
    if(err != GLEW_OK){
        fprintf(stderr, "glew:init error!");
        return 1;
    }
    SetupRC();
    glutMainLoop();
    return 0;
}
