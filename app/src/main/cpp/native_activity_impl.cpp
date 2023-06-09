//
// Created by youngpark on 2023/4/2.
//
#include "android_app_glue/android_native_app_glue.h"
#include <android/log.h>
#include <EGL/egl.h>
#include "native_gl.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))

/*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
const EGLint surface_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
};

const EGLint context_attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                     EGL_NONE };

EGLint format;
EGLint height, width;
EGLint major, minor;

EGLSurface surface;
EGLContext context;
EGLDisplay eglDisplay;

void initEGL(android_app *app){
    //初始化EGL
    EGLint configCount;
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(eglDisplay, &major, &minor);
    eglChooseConfig(eglDisplay, surface_attribs, nullptr, 0, &configCount);
    if(configCount == 0) {
        return;
    }
    EGLConfig *config = (EGLConfig *)malloc(configCount * sizeof (EGLConfig));
    eglChooseConfig(eglDisplay, surface_attribs, config, configCount, &configCount);



    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(eglDisplay, config[0], EGL_NATIVE_VISUAL_ID, &format);
    surface = eglCreateWindowSurface(eglDisplay, config[0], app->window, nullptr);
    context = eglCreateContext(eglDisplay, config[0], nullptr, context_attrib_list);
    eglMakeCurrent(eglDisplay, surface, surface, context);

    eglQuerySurface(eglDisplay, surface, EGL_WIDTH, &width);
    eglQuerySurface(eglDisplay, surface, EGL_HEIGHT, &height);

}


void handle_app_cmd(struct android_app* app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            initEGL(app);
//            void *(*init)(void) = nullptr;
//            void* fileHandle = dlopen("/data/data/com.park.native_learn/lib/libnative_gl.so", RTLD_LAZY);
//            init = (void *(*)(void))dlsym(fileHandle, "init");
//            init();
            init();
            onChange(width, height);
            onDraw();
            eglSwapBuffers(eglDisplay, surface);
            break;
    }
}

void android_main(struct android_app* app) {
    LOGI("native_activity", "main start");
    app->onAppCmd = handle_app_cmd;
    int events;
    android_poll_source *source;
    while(true) {
        int indent = ALooper_pollAll(-1, nullptr, &events, (void **)(&source));
        if(source != nullptr) {
            source->process(app, source);
        }
        if(indent == LOOPER_ID_USER) {

        }
        if(app->destroyRequested) {
            return;
        }
    }
}