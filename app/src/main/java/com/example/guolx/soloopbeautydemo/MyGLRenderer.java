package com.example.guolx.soloopbeautydemo;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES20.GL_COLOR_BUFFER_BIT;
import static android.opengl.GLES20.glClear;
import static android.opengl.GLES20.glClearColor;
import static android.opengl.GLES20.glViewport;

public class MyGLRenderer implements GLSurfaceView.Renderer {
    private Triangle mTriangle;
    private Square   mSquare;

    private Context mContext;

    public MyGLRenderer(Context context) {
        mContext = context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //mTriangle = new Triangle();
        mSquare = new Square();
//        BitmapFactory.Options options = new BitmapFactory.Options();
//        options.inScaled = false;
//        int imageId = mContext.getResources().getIdentifier("test", "drawable", mContext.getPackageName());
//        Bitmap bitmap = BitmapFactory.decodeResource(mContext.getResources(), imageId);

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        glClear(GL_COLOR_BUFFER_BIT);
        //mTriangle.draw();
        mSquare.draw();
    }
}
