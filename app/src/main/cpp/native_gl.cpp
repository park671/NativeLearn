//
// Created by youngpark on 2023/4/1.
//

#include "native_gl.h"
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <android/log.h>

unsigned int mProgramId, mPositionId, mColorId;

float triangleCoords[] = {
        0.0f, 1.0f, 0.0f, // 顶点
        -1.0f, -0.0f, 0.0f, // 左下角
        1.0f, -0.0f, 0.0f  // 右下角
};

float triangleCoords2[] = {
        0.0f, -1.0f, 0.0f, // 顶点
        -1.0f, -0.0f, 0.0f, // 左下角
        1.0f, -0.0f, 0.0f  // 右下角
};

float rectCoords[] = {
        -0.2f, 0.2f, 0.0f, // left top
        0.2f, 0.2f, 0.0f, // right top
        0.2f, -0.2f, 0.0f, // right bottom
        -0.2f, -0.2f, 0.0f, // left bottom
};

const char *VERTEX_SHADER = "attribute vec4 vPosition;"
                            "void main() {"
                            "  gl_Position = vPosition;"
                            "}\0";

const char *FRAGMENT_SHADER = "precision mediump float;"
                              "uniform vec4 vColor;"
                              "void main() {"
                              "gl_FragColor = vColor;"
                              "}\0";

float color[] = {0.0f, 1.0f, 0.f, 1.0f};
float color2[] = {1.0f, 0.0f, 0.f, 1.0f};
float yellow[] = {1.0f, 1.0f, 0.f, 1.0f};

const int COORDS_PER_VERTEX = 3;//每个顶点3个坐标xyz
const int VERTEX_STRID = COORDS_PER_VERTEX * 4;//每个顶点坐标占用4字节

unsigned int loadShader(const char * shaderCode, GLenum type) {
    int compiled;
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled) {
        __android_log_print(ANDROID_LOG_ERROR, "native_GL", "compile err");
        return 0;
    }
    return shader;
}

unsigned int loadProgram(const char *VShaderCode, const char *FShaderCode) {
    unsigned int iVshader, iFShader, iProgramId;
    int link;
    iVshader = loadShader(VShaderCode, GL_VERTEX_SHADER);
    iFShader = loadShader(FShaderCode, GL_FRAGMENT_SHADER);
    if(!(iVshader && iFShader)) {
        __android_log_print(ANDROID_LOG_ERROR, "native_GL", "shader err");
        return 0;
    }
    iProgramId = glCreateProgram();
    glAttachShader(iProgramId, iVshader);
    glAttachShader(iProgramId, iFShader);
    glLinkProgram(iProgramId);
    glGetProgramiv(iProgramId, GL_LINK_STATUS, &link);
    if(!link){
        __android_log_print(ANDROID_LOG_ERROR, "native_GL", "link err");
        return 0;
    }
    glDeleteShader(iVshader);
    glDeleteShader(iFShader);
    return iProgramId;
}

void init(){
    __android_log_print(ANDROID_LOG_DEBUG, "native_GL", "init");
    mProgramId = loadProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    mPositionId = glGetAttribLocation(mProgramId, "vPosition");
    mColorId = glGetUniformLocation(mProgramId, "vColor");
}

void onChange(int width, int height) {
    __android_log_print(ANDROID_LOG_DEBUG, "native_GL", "onChange");
    glViewport(0, 0, width, height);
}

void onDraw() {
    glClearColor(0.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mProgramId);
    glEnableVertexAttribArray(mPositionId);
    glVertexAttribPointer(mPositionId, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, VERTEX_STRID,
                          triangleCoords);
    glUniform4fv(mColorId, 1, color);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexAttribPointer(mPositionId, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, VERTEX_STRID,
                          triangleCoords2);
    glUniform4fv(mColorId, 1, color2);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glVertexAttribPointer(mPositionId, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, VERTEX_STRID,
                          rectCoords);
    glUniform4fv(mColorId, 1, yellow);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(mPositionId);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_park_native_1learn_opengl_GLNativeBridge_init(JNIEnv *env, jobject thiz, jobject gl10) {
    init();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_park_native_1learn_opengl_GLNativeBridge_onChange(JNIEnv *env, jobject thiz,
                                                           jobject gl10, jint width, jint height) {
    onChange(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_park_native_1learn_opengl_GLNativeBridge_onDrawFrame(JNIEnv *env, jobject thiz,
                                                              jobject gl10) {
    onDraw();
}