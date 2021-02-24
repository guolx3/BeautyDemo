package com.example.guolx.soloopbeautydemo;

import android.opengl.GLES20;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;
import static android.opengl.GLES20.*;

public class Square {

    private final String vertexShaderCode =
            "attribute vec4 vPosition;" +
            "void main() {" +
            "  gl_Position = vPosition;" +
            "}";

    private final String fragmentShaderCode =
            "precision mediump float;" +
            "uniform vec4 vColor;" +
            "void main() {" +
            "  gl_FragColor = vColor;" +
            "}";

    // number of coordinates per vertex in this array
    static final int COORDS_PER_VERTEX = 3;
    static float squareCoords[] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
    };

    private short drawOrder[] = { 0, 1, 2, 0, 2, 3 }; // order to draw vertices

    float color[] = { 0.63671875f, 0.76953125f, 0.22265625f, 1.0f };

    private FloatBuffer vertexBuffer;
    private ShortBuffer drawListBuffer;

    private int[] vbo = new int[1];
    private int[] ibo = new int[1];

    private final int mProgram;

    public Square() {
        // initialize vertex byte buffer for shape coordinates
        ByteBuffer bb = ByteBuffer.allocateDirect(
                // (# of coordinate values * 4 bytes per float)
                squareCoords.length * 4);
        bb.order(ByteOrder.nativeOrder());
        vertexBuffer = bb.asFloatBuffer();
        vertexBuffer.put(squareCoords);
        vertexBuffer.position(0);

        // initialize byte buffer for the draw list
        ByteBuffer dlb = ByteBuffer.allocateDirect(
                // (# of coordinate values * 2 bytes per short)
                drawOrder.length * 2);
        dlb.order(ByteOrder.nativeOrder());
        drawListBuffer = dlb.asShortBuffer();
        drawListBuffer.put(drawOrder);
        drawListBuffer.position(0);

        glGenBuffers(1, vbo, 0);
        glGenBuffers(1, ibo, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, vertexBuffer.capacity() * 4, vertexBuffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawListBuffer.capacity() * 2, drawListBuffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        int vertexShader = Utils.loadShader(GLES20.GL_VERTEX_SHADER,
                vertexShaderCode);
        int fragmentShader = Utils.loadShader(GLES20.GL_FRAGMENT_SHADER,
                fragmentShaderCode);

        // create empty OpenGL ES Program
        mProgram = GLES20.glCreateProgram();

        // add the vertex shader to program
        GLES20.glAttachShader(mProgram, vertexShader);

        // add the fragment shader to program
        GLES20.glAttachShader(mProgram, fragmentShader);

        // creates OpenGL ES program executables
        GLES20.glLinkProgram(mProgram);
    }

    private int positionHandle;
    private int colorHandle;

    private final int vertexCount = squareCoords.length / COORDS_PER_VERTEX;
    private final int vertexStride = COORDS_PER_VERTEX * 4; // 4 bytes per vertex

    public void draw() {
        glUseProgram(mProgram);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        positionHandle = glGetAttribLocation(mProgram, "vPosition");
        glEnableVertexAttribArray(positionHandle);
        glVertexAttribPointer(positionHandle, COORDS_PER_VERTEX, GL_FLOAT, false, vertexStride, 0);

        colorHandle = glGetUniformLocation(mProgram, "vColor");
        glUniform4fv(colorHandle, 1, color, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
        glDrawElements(GL_TRIANGLES, drawOrder.length, GL_UNSIGNED_SHORT, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableVertexAttribArray(positionHandle);
    }
}

