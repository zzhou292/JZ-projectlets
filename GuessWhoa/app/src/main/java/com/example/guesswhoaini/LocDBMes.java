package com.example.guesswhoaini;

import android.graphics.Path;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class LocDBMes {

    public float x;
    public float y;
    public int color;
    public ArrayList<FingerPath> fpl;

    public LocDBMes(float x, float y, int color, ArrayList<FingerPath> fpl) {
        this.color = color;
        this.x = x;
        this.y = y;
        this.fpl = fpl;
    }

}
