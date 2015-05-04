#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

//#ifndef false
//#define false (0)
//#endif
#ifndef LOG_TAG
#define LOG_TAG "ANDROID_LAB"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif

/* Header for class lab_sodino_jnitest_MainActivity */

#ifndef _Included_lab_sodino_jnitest_MainActivity
#define _Included_lab_sodino_jnitest_MainActivity
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jintArray JNICALL Java_com_meitu_camera_ui_TakePictureActivity_imgToGray(JNIEnv* env, jobject obj, jintArray buf, jint w, jint h){
    jint *cbuf;
    cbuf = env->GetIntArrayElements(buf, NULL);
    if (cbuf == NULL) {
        return 0; /* exception occurred */
    }
    int alpha = 0xFF << 24;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int color = cbuf[w * i + j];
            int red = ((color & 0x00FF0000) >> 16);
            int green = ((color & 0x0000FF00) >> 8);
            int blue = color & 0x000000FF;
            color = (red + green + blue) / 3;
            color = alpha | (color << 16) | (color << 8) | color;
            cbuf[w * i + j] = color;
        }
    }
    int size=w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, cbuf);
    env->ReleaseIntArrayElements(buf, cbuf, 0);
    return result;
}

#ifdef __cplusplus
}
#endif
#endif

