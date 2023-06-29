package com.example.guesswhoaini;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

/**
 * After a message is sent to confirm the winner
 * A child node will be added to Firebase Realtime database
 * https://guesswhoa-322a1-414eb.firebaseio.com/
 *
 * This Activity will be activated when an "add child" is detected
 */

public class ConfirmActivity extends AppCompatActivity {
    TextView textViewwin;
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_winnerconfirm);

        textViewwin = (TextView) findViewById(R.id.confirmText2);
        Bundle bundleEx = getIntent().getExtras();

        System.out.println((String)bundleEx.get("pickedName"));
        if(textViewwin!=null) {
            textViewwin.setText((String)bundleEx.get("pickedName")+" is the Winner !!!!");
        }
    }

    public void returnFunction(View view)
    {
        Intent intent = new Intent(this,MainActivity.class);
        startActivity(intent);
    }


}
