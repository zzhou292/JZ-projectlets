package com.example.guesswhoaini;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.FirebaseDatabase;

/**
 * This Activity will be invoked when the painter has confirmed the winner
 * The winner's name will be sent to the realtime database
 * and retrieved by clients in real time
 */


public class PickWinnerActivity extends AppCompatActivity {
    EditText pickedName;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pickwinner);

    }


    public void confirmFunction(View view)
    {
        pickedName = findViewById(R.id.pickedName);
        //send the input string - the name of the winner
        //to the firebase database
        FirebaseDatabase.getInstance("https://guesswhoa-322a1-414eb.firebaseio.com/")
                .getReference()
                .push()
                .setValue(pickedName.getText().toString()
                );


        //After packet sent to the database
        //return the app to the main activity
        Intent intent = new Intent(this,MainActivity.class);
        startActivity(intent);


    }



}