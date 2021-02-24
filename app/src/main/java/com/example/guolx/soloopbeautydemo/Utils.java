package com.example.guolx.soloopbeautydemo;
import android.graphics.Bitmap;
import android.opengl.GLES20;
import android.opengl.GLUtils;

import static android.opengl.GLES20.*;

public class Utils {

    public static int loadShader(int type, String shaderCode){

        // create a vertex shader type (GLES20.GL_VERTEX_SHADER)
        // or a fragment shader type (GLES20.GL_FRAGMENT_SHADER)
        int shader = GLES20.glCreateShader(type);

        // add the source code to the shader and compile it
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);

        return shader;
    }

    public static int createTexture(Bitmap bitmap) {
        int[] textureId = new int[1];
        glGenTextures(1, textureId, 0);
        glBindTexture(GL_TEXTURE_2D, textureId[0]);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (null != bitmap && !bitmap.isRecycled()) {
            GLUtils.texImage2D(GL_TEXTURE_2D, 0, bitmap, 0);
            glGenerateMipmap(GL_TEXTURE_2D);
            bitmap.recycle();
            return textureId[0];
        } else {
            return -1;
        }
    }
}
