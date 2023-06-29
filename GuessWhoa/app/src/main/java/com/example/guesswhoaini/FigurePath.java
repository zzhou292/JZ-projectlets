package com.example.guesswhoaini;

import android.graphics.Path;

class FingerPath {

    public int color;
    public int strokeWidth;
    public Path path;
    public int type;
    public float x;
    public float y;
    public float mx;
    public float my;

    public FingerPath(int color, int strokeWidth, Path path, float x, float y, float mx, float my) {
        this.color = color;
        this.strokeWidth = strokeWidth;
        this.path = path;
        this.type = 1;
        this.x = x;
        this.y = y;
        this.mx = mx;
        this.my = my;
    }

    public int getType() {
        return type;
    }
}