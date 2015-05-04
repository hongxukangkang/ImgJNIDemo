package com.meitu.camera.ui;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.widget.ImageView;

import meitu.imgjnidemo.R;


public class TakePictureActivity extends Activity {

    static {
        System.loadLibrary("imageToGray");
    }

    private ImageView imageView;

    public native int[] imgToGray(int[] buf, int w, int h);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_take_picture);

        findViews();
        exaggerateImageViewFromJNI();

    }

    private void findViews() {
        imageView = (ImageView) findViewById(R.id.imageView);
    }

    private void exaggerateImageViewFromJNI() {
        Bitmap img1 = ((BitmapDrawable) getResources().getDrawable(R.drawable.logo)).getBitmap();
        int w = img1.getWidth(), h = img1.getHeight();
        int[] pix = new int[w * h];
        img1.getPixels(pix, 0, w, 0, 0, w, h);
        int[] resultInt = imgToGray(pix, w, h);
        Bitmap resultImg = Bitmap.createBitmap(w, h, Bitmap.Config.RGB_565);
        resultImg.setPixels(resultInt, 0, w, 0, 0, w, h);
        imageView.setImageBitmap(resultImg);
    }
}