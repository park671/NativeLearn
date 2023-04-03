package com.park.native_learn.opengl;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLRenderer implements GLSurfaceView.Renderer {

    GLNativeBridge glNativeBridge = new GLNativeBridge();
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        glNativeBridge.init(gl);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        glNativeBridge.onChange(gl, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        glNativeBridge.onDrawFrame(gl);
    }
}
