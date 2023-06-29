package com.example.guesswhoaini;

import android.content.Intent;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.FirebaseDatabase;

public class PainttestRecActivity extends AppCompatActivity {
    private PaintViewRec paintViewRec;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_painttestrec);

        paintViewRec = (PaintViewRec) findViewById(R.id.paintView);
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        paintViewRec.init(metrics);
        detectWinner();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater menuInflater = getMenuInflater();
        menuInflater.inflate(R.menu.menu3, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()) {
            case R.id.switchchat:
                Intent intent = new Intent(this,MessageActivity.class);
                startActivity(intent);
        }

        return super.onOptionsItemSelected(item);
    }

    public void detectWinner(){
        FirebaseDatabase.getInstance("https://guesswhoa-322a1-414eb.firebaseio.com/").getReference().addChildEventListener(new ChildEventListener() {
            @Override
            public void onChildAdded(DataSnapshot dataSnapshot, String s) {
                String str=dataSnapshot.getValue(String.class);

                startActivity(str);
                FirebaseDatabase.getInstance("https://guesswhoa-322a1-414eb.firebaseio.com/").getReference().removeValue();
            }

            @Override
            public void onChildChanged(DataSnapshot dataSnapshot, String s) {

            }

            @Override
            public void onChildRemoved(DataSnapshot dataSnapshot) {
            }

            @Override
            public void onChildMoved(DataSnapshot dataSnapshot, String s) {
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {
            }

        });
    }

    public void startActivity(String str)
    {
        System.out.println("test stromg ;p;p; : "+str);
        Intent intent = new Intent(this, ConfirmActivity.class);
        intent.putExtra("pickedName",str);
        startActivity(intent);
    }



}
