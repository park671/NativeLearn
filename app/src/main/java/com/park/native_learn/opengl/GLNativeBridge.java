package com.park.native_learn.opengl;

import javax.microedition.khronos.opengles.GL10;

public class GLNativeBridge {

    static {
        System.loadLibrary("native_gl");
    }

    public native void init(GL10 gl10);

    public native void onChange(GL10 gl10, int width, int height);

    public native void onDrawFrame(GL10 gl10);

}
