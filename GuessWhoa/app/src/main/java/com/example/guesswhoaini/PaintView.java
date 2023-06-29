
package com.example.guesswhoaini;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BlurMaskFilter;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.EmbossMaskFilter;
import android.graphics.MaskFilter;
import android.graphics.Paint;
import android.graphics.Path;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.view.MotionEvent;
import android.view.View;

import com.google.firebase.FirebaseApp;
import com.google.firebase.FirebaseOptions;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashSet;
import java.util.Random;

import static com.facebook.FacebookSdk.getApplicationContext;

/**
 * This class serves as the painter board on the painter side
 * Main functionalities include local drawing and sending package
 */

public class PaintView extends View {

    public static int BRUSH_SIZE = 20;
    public static final int DEFAULT_COLOR = Color.RED;  //0
    public static final int DEFAULT_COLOR2 = Color.GREEN;  //1
    public static final int DEFAULT_COLOR3 = Color.BLUE;  //2
    public static final int DEFAULT_BG_COLOR = Color.WHITE;
    private static final float TOUCH_TOLERANCE = 4;
    public int colorIndicator = 0;
    private float mX, mY;
    private Path mPath;
    private Paint mPaint;
    private ArrayList<FingerPath> paths = new ArrayList<>();
    private int currentColor;
    private int backgroundColor = DEFAULT_BG_COLOR;
    private int strokeWidth;
    private Bitmap mBitmap;
    private Canvas mCanvas;
    private Paint mBitmapPaint = new Paint(Paint.DITHER_FLAG);
    private LocDBMes dBMes= null;
    private ArrayList<Coordinates> coord;


    public PaintView(Context context) {
        this(context, null);
    }

    public PaintView(Context context, AttributeSet attrs) {
        super(context, attrs);

        mPaint = new Paint();
        mPaint.setAntiAlias(true);
        mPaint.setDither(true);
        mPaint.setColor(DEFAULT_COLOR);
        mPaint.setStyle(Paint.Style.STROKE);
        mPaint.setStrokeJoin(Paint.Join.ROUND);
        mPaint.setStrokeCap(Paint.Cap.ROUND);
        mPaint.setXfermode(null);
        mPaint.setAlpha(0xff);
        coord = new ArrayList<Coordinates>();

    }


    public void init(DisplayMetrics metrics) {
        int height = metrics.heightPixels;
        int width = metrics.widthPixels;

        mBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        mCanvas = new Canvas(mBitmap);

        currentColor = DEFAULT_COLOR;
        strokeWidth = BRUSH_SIZE;
    }

    //color selection brancher function
    //color red branch
    public void red() {
        colorIndicator = 0;
    }

    //color green branch
    public void green() {
        colorIndicator = 1;
    }

    //color blue branch
    public void blue() {
        colorIndicator = 2;
    }

    //clear branch
    public void clear() {
        backgroundColor = DEFAULT_BG_COLOR;
        paths.clear();
        FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().removeValue();
        red();
        invalidate();

    }

    @Override
    protected void onDraw(Canvas canvas) {
        canvas.save();
        mCanvas.drawColor(backgroundColor);

        for (FingerPath fp : paths) {

            //FirebaseOptions options = new FirebaseOptions.Builder()
                    //.setApplicationId("guesswhoa-322a1")
                    //.setApiKey("AIzaSyCaQnv8AIWi9h0zjZSMunBOoNELiLMgYx4")
                    //.setDatabaseUrl("https://guesswhoa-322a1-58abe.firebaseio.com/")
                    //.build();



            //FirebaseApp.initializeApp(this.getContext(), options, "guesswhoa-322a1-58abe");
            //FirebaseApp secondApp = FirebaseApp.getInstance("guesswhoa-322a1-58abe");


            mPaint.setStrokeWidth(fp.strokeWidth);
            mPaint.setMaskFilter(null);

            //hardcode the color selection
            //based on the color indicator
            if (fp.color==0)
                mPaint.setColor(DEFAULT_COLOR);
            else if (fp.color==1)
                mPaint.setColor(DEFAULT_COLOR2);
            else
                mPaint.setColor(DEFAULT_COLOR3);

            //FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/")
              //      .getReference()
                //    .push()
                  //  .setValue(new FingerPath(fp.color, fp.strokeWidth, fp.path,fp.x,fp.y,fp.mx,fp.my
                       //     )
                    //);
            mCanvas.drawPath(fp.path, mPaint);

        }

        canvas.drawBitmap(mBitmap, 0, 0, mBitmapPaint);
        canvas.restore();
    }

    /**
     * This function is called when a "touch down" simulation starts
     * This is the initial touch of a line
     * @param x touch down x coordinate
     * @param y touch down y coordinate
     * @param addToCoord    whether add to data array and send to database
     */
    private void touchStart(float x, float y, boolean addToCoord) {
        mPath = new Path();
        FingerPath fp = new FingerPath(colorIndicator, strokeWidth, mPath, x,y,mX,mY);
        paths.add(fp);


        mPath.reset();
        mPath.moveTo(x, y);
        mX = x;
        mY = y;

        if(addToCoord) {
            coord.add(new Coordinates(x, y, MotionEvent.ACTION_DOWN,colorIndicator));
        }
    }

    /**
     * This function is called when finger is moving and constantly collecting data
     * @param x the x coordinate during moving
     * @param y the y coordinate during moving
     * @param addToCoord whether to add this data point to the record
     */
    private void touchMove(float x, float y, boolean addToCoord) {

        //the amount of displacement on x direction
        float dx = Math.abs(x - mX);
        //the amount of displacement on y direction
        float dy = Math.abs(y - mY);

        //if the movement is believed to be larger than tolerance
        //start drawing line using quadTo
        if (dx >= TOUCH_TOLERANCE || dy >= TOUCH_TOLERANCE) {
            mPath.quadTo(mX, mY, (x + mX) / 2, (y + mY) / 2);
            //debugging helper - print out x y coordinates data
            //System.out.println("x"+x);
            //System.out.println("y"+y);

            //update last x point
            //the current floater
            mX = x;
            //update last y point
            //the current floater
            mY = y;

            //if add to cord, save the current coordinate to the data array
            if(addToCoord) {
                coord.add(new Coordinates(x, y, MotionEvent.ACTION_MOVE,colorIndicator));
            }
        }

       // FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/")
          //  .getReference()
           //  .push()
            //.setValue(new LocDBMes(x,y,colorIndicator
           //    )
        // );
    }

    /**
     * This function is called when the painter's finger is removed from the screen
     * touch up function finishes one line
     * @param x the finishing x coordinate
     * @param y the finishing y coordinate
     * @param addToCoord whether to add the current data point to the data array
     */
    private void touchUp(float x, float y, boolean addToCoord) {
        //using lineTo to finish drawing the line
        mPath.lineTo(x, y);

        //if addToCoord is true
        //then we add the current coordinate point to the data array
        if(addToCoord) {
            coord.add(new Coordinates(mX, mY,  MotionEvent.ACTION_UP, colorIndicator));
        }


        //after finger is removed
        //and one line is finished
        //start uploading current data to the database
        for(Coordinates c : coord){
            String nextStringIdx = getNextString();
            //x coordinate field
            FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().child(nextStringIdx).child("x").setValue(c.getX());
            //y coordinate field
            FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().child(nextStringIdx).child("y").setValue(c.getY());
            //action field
            FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().child(nextStringIdx).child("action").setValue(c.getAction());
            //color field
            FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().child(nextStringIdx).child("color").setValue(c.getColor());
        }
        coord.clear();
    }

    /**
     * Brancher which determines which action number does what action
     * @param event the current motion event
     * @return
     */
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float x = event.getX();
        float y = event.getY();

        switch(event.getAction()) {
            //branch to action down
            case MotionEvent.ACTION_DOWN :
                touchStart(x, y,true);
                invalidate();
                break;
            //branch to action move
            case MotionEvent.ACTION_MOVE :
                touchMove(x, y,true);
                invalidate();
                break;
            //branch to action up
            case MotionEvent.ACTION_UP :
                touchUp(x,y,true);
                invalidate();
                break;
        }

        return true;
    }

    /**
     * Automatic index generator for more ordered database access
     * @return a string which is an ordered while unique id
     */
    private String getNextString(){
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append((new Date()).getTime());
        Random random = new Random();
        for(int i = 0; i < 32; i++){
            int c = random.nextInt(26) + 97;
            stringBuilder.append((char)c);
        }
        return stringBuilder.toString();
    }
}