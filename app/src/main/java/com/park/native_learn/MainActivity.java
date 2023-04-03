package com.park.native_learn;

import android.app.Activity;
import android.graphics.Canvas;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.Matrix;
import android.os.Bundle;
import android.widget.TextView;

import com.park.native_learn.opengl.MyGLRenderer;
import com.park.native_learn.opengl.MyGLView;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        NativeBridge nativeBridge = new NativeBridge();
        TextView textView = findViewById(R.id.textView);
        textView.setText(nativeBridge.getInfoFromNative());
        findViewById(R.id.addCppButton).setOnClickListener(v->{
            textView.setText("native cpp 1+2=" + nativeBridge.addCpp(1,2));
        });

        findViewById(R.id.addInlineAsmButton).setOnClickListener(v->{
            textView.setText("native inline assembly 2+3=" + nativeBridge.addInlineAsm(2,3));
        });

        findViewById(R.id.addAsmButton).setOnClickListener(v->{
            textView.setText("native assembly 3+4+100=" + nativeBridge.addAsm(3,4));
        });

        MyGLView myGLView = findViewById(R.id.glView);
        myGLView.setEGLContextClientVersion(2);
        myGLView.setRenderer(new MyGLRenderer());
        myGLView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

}