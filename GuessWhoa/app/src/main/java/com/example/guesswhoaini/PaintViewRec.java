
package com.example.guesswhoaini;

import android.annotation.SuppressLint;
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
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import androidx.annotation.NonNull;

import com.google.firebase.FirebaseApp;
import com.google.firebase.FirebaseError;
import com.google.firebase.FirebaseOptions;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashSet;
import java.util.Objects;
import java.util.Random;

import static com.facebook.FacebookSdk.getApplicationContext;

/**
 * This class is the painting board on the receiver side
 * The painting board has the simulation function
 * but it doesn't have on touch draw function
 * to ensure consistency
 */

public class PaintViewRec extends View {

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


    public PaintViewRec(Context context) {
        this(context, null);
    }

    public PaintViewRec(Context context, AttributeSet attrs) {
        //hardcode default settings
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

    /**
     * The simulate drawing is going to draw all data points received from database
     * @param newCoords each coordinate is a data packet which includes:
     *                  x, y , action type, color
     */
    private void simulateDrawing(ArrayList<Coordinates> newCoords) {
        for(Coordinates event : newCoords){
            //before anything is done, an if-else clause
            //is used to hardcode color
            if(event.getColor()==0)
            {
                red();
            }else if(event.getColor()==1)
            {
                green();
            }else{
                blue();
            }
            //the if getY clause is used to eliminate a bug
            //it's not believed this clause has side effect
            if(event.getY()!=0) {
                switch (event.getAction()) {
                    // branch to action down
                    case MotionEvent.ACTION_DOWN:
                        touchStart(event.getX(), event.getY(), false);
                        invalidate();
                        break;
                    // branch to action move
                    case MotionEvent.ACTION_MOVE:
                        touchMove(event.getX(), event.getY(), false);
                        invalidate();
                        break;
                    // branch to action up
                    case MotionEvent.ACTION_UP:
                        touchUp(event.getX(), event.getY(), false);
                        invalidate();
                        break;
                }
            }
        }
    }

    //initialization function
    //will be called everytime it starts
    public void init(DisplayMetrics metrics) {
        //retrieve hardcoded height pixel
        int height = metrics.heightPixels;
        //retrieve hardcoded width pixel
        int width = metrics.widthPixels;
        //create a new path for further use
        mPath = new Path();

        FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().addValueEventListener(new ValueEventListener() {
            //@SuppressLint("NewApi")
            @Override
            //detection on database data change
            public void onDataChange(DataSnapshot dataSnapshot) {
                ArrayList<Coordinates> newCoords = new ArrayList<Coordinates>();
                for(DataSnapshot coordSnapshot : dataSnapshot.getChildren()){
                    Coordinates currCoord = coordSnapshot.getValue(Coordinates.class);
                    newCoords.add(currCoord);
                }
                //after data packets were retrieved from the database
                //and stored in newCoords array
                //perform simulation on the newCoords array
                simulateDrawing(newCoords);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }

        });
        FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().addChildEventListener(new ChildEventListener() {
            @Override
            //this detection is temporarily disabled
            //it's believed a bug can be caused if using on ChildAdded
            //no side effects detected
            public void onChildAdded(DataSnapshot dataSnapshot, String s) {
                //ArrayList<Coordinates> newCoord = new ArrayList<Coordinates>();
                //Coordinates currCoord = dataSnapshot.getValue(Coordinates.class);
                //newCoords.add(currCoord);
                //simulateDrawing();
            }

            @Override
           public void onChildChanged(DataSnapshot dataSnapshot, String s) {

            }

            @Override
            public void onChildRemoved(DataSnapshot dataSnapshot) {
                clear();
            }

            @Override
            public void onChildMoved(DataSnapshot dataSnapshot, String s) {

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }

        });



        mBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        mCanvas = new Canvas(mBitmap);

        currentColor = DEFAULT_COLOR;
        strokeWidth = BRUSH_SIZE;
    }

    // color brancher based on received data packet color field
    // red branch
    public void red() {
        colorIndicator = 0;
    }

    //green branch
    public void green() {
        colorIndicator = 1;
    }

    //blue branch
    public void blue() {
        colorIndicator = 2;
    }

    //clear branch, this is not actually needed
    //but added for simplier modulization
    public void clear() {
        backgroundColor = DEFAULT_BG_COLOR;
        paths.clear();

        red();
        invalidate();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        canvas.save();
        if(mCanvas!=null) {
            mCanvas.drawColor(backgroundColor);
        }else{
            mCanvas = new Canvas();
            mCanvas.drawColor(backgroundColor);
        }

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

    //touch start simulation function
    private void touchStart(float x, float y, boolean addToCoord) {

        mPath = new Path();
        FingerPath fp = new FingerPath(colorIndicator, strokeWidth, mPath, x,y,mX,mY);
        paths.add(fp);

        //system output used for debugging
        //can be reduced or deleted
        System.out.println("start !!!! x"+x);
        System.out.println("start !!!! y"+y);
        System.out.println("start !!!! mx"+mX);
        System.out.println("start !!!! my"+mY);

        //move line to x and y
        mPath.moveTo(x, y);

        mX = x;
        mY = y;

        //if(addToCoord) {
        //    coord.add(new Coordinates(x, y, MotionEvent.ACTION_DOWN));
        //}
    }

    //touch move simulation function
    private void touchMove(float x, float y, boolean addToCoord) {

        float dx = Math.abs(x - mX);
        float dy = Math.abs(y - mY);

        if (dx >= TOUCH_TOLERANCE || dy >= TOUCH_TOLERANCE) {
            mPath.quadTo(mX, mY, (x + mX) / 2, (y + mY) / 2);
            mX = x;
            mY = y;

            //if(addToCoord) {
             //   coord.add(new Coordinates(x, y, MotionEvent.ACTION_MOVE));
            //}
        }

        // FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/")
        //  .getReference()
        //  .push()
        //.setValue(new LocDBMes(x,y,colorIndicator
        //    )
        // );
    }

    //touch up simulation function
    private void touchUp(float x, float y, boolean addToCoord) {

        mPath.lineTo(x, y);
        //if(addToCoord) {
        //    coord.add(new Coordinates(mX, mY,  MotionEvent.ACTION_UP));
        //}

        //for(Coordinates c : coord){
         //   String nextStringIdx = getNextString();
         //   FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().child(nextStringIdx).child("x").setValue(c.getX());
         //   FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().child(nextStringIdx).child("y").setValue(c.getY());
         //   FirebaseDatabase.getInstance("https://guesswhoa-322a1-58abe.firebaseio.com/").getReference().child(nextStringIdx).child("action").setValue(c.getAction());
        //}
        //coord.clear();
    }

   // @Override
    //public boolean onTouchEvent(MotionEvent event) {
     //   float x = event.getX();
    //    float y = event.getY();

     //   switch(event.getAction()) {
      //      case MotionEvent.ACTION_DOWN :
      //          touchStart(x, y,true);
      //          invalidate();
      //          break;
      //      case MotionEvent.ACTION_MOVE :
       //         touchMove(x, y,true);
       //         invalidate();
         //       break;
         //   case MotionEvent.ACTION_UP :
         //       touchUp(x,y,true);
          //      invalidate();
          //      break;
        //}

        //return true;
    //}

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