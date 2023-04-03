package com.park.native_learn;

public class NativeBridge {

    static {
       System.loadLibrary("native_learn");
    }

    public native String getInfoFromNative();

    public native int addCpp(int a, int b);
    public native int addInlineAsm(int a, int b);
    public native int addAsm(int a, int b);

}
