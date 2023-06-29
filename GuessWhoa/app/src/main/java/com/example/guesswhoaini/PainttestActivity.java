package com.example.guesswhoaini;
import com.example.guesswhoaini.R;
import com.firebase.ui.database.FirebaseListAdapter;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.FirebaseDatabase;

import android.content.Intent;
import android.os.Bundle;
import android.text.format.DateFormat;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Adapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

/**
 * This activity will invoke a fully-functional painting board
 * This activity is designed for painter
 *
 * At the same time
 * A chat-room activity will be displayed at the bottom half of the activity
 */

import androidx.appcompat.app.AppCompatActivity;

import java.util.Random;

public class PainttestActivity extends AppCompatActivity {

    private PaintView paintView;
    private int counter = 0;
    FirebaseAuth mFirebaseAuth = FirebaseAuth.getInstance();
    FirebaseUser mFirebaseUser = mFirebaseAuth.getCurrentUser();
    private FirebaseListAdapter<ChatMessage> adapter;
    private String questionStr;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_painttest);

        //initiate and display the painting board(painter side)
        paintView = (PaintView) findViewById(R.id.paintView);
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        paintView.init(metrics);

        //display chat-room on the other half of the screen
        displayChatMessages();

        //show problem in a toast
        problemShow();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater menuInflater = getMenuInflater();
        menuInflater.inflate(R.menu.main, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()) {
            //change the stroke color to red
            case R.id.red:
                paintView.red();
                return true;
            //change the stroke color to green
            case R.id.green:
                paintView.green();
                return true;
            //change the stroke color to blue
            case R.id.blue:
                paintView.blue();
                return true;
            //clear the painting board
            case R.id.clear:
                paintView.clear();
                return true;
            //this option is going to bring up pick winner activity
            //which allows the painter to type in the name of the winner
            case R.id.pick:
                Intent intent = new Intent(this,PickWinnerActivity.class);
                startActivity(intent);
            case R.id.problem:
                problemReview();
        }

        return super.onOptionsItemSelected(item);
    }

    private void onClickColorButton(){
        openColorDialog();
    }

    private void openColorDialog(){

    }

    private void displayChatMessages() {
        final ListView listOfMessages = (ListView)findViewById(R.id.list_of_messages1);

        listOfMessages.setTranscriptMode(ListView.TRANSCRIPT_MODE_NORMAL);
        adapter = new FirebaseListAdapter<ChatMessage>(this, ChatMessage.class,
                R.layout.message, FirebaseDatabase.getInstance().getReference()) {
            @Override

            //populate messages stored in the database.
            protected void populateView(View v, ChatMessage model, int position) {

                if (model.getType() != 1 && model != null) {
                    Log.d("out", String.valueOf(model.getType()));
                    // Get references to the views of message.xml
                    TextView messageText = (TextView) v.findViewById(R.id.message_text);
                    TextView messageUser = (TextView) v.findViewById(R.id.message_user);
                    TextView messageTime = (TextView) v.findViewById(R.id.message_time);

                    // Set their text
                    messageText.setText(model.getMessageText());
                    messageUser.setText(model.getMessageUser());

                    // Format the date before showing it
                    messageTime.setText(DateFormat.format("dd-MM-yyyy (HH:mm:ss)",
                            model.getMessageTime()));


                    scrollMyListViewToBottom(listOfMessages, adapter);
                }
            }
        };

        listOfMessages.setAdapter(adapter);
    }

    //This function helps the chat room to always keep the newest message received
    //at bottom
    private void scrollMyListViewToBottom(final ListView myListView, final Adapter myListAdapter) {
        if(counter == 0)
        {
            myListView.post(new Runnable() {
                @Override
                public void run() {
                    // Select the last row so it will scroll into view...
                    myListView.setSelection(myListAdapter.getCount() - 1);
                }
            });
            counter++;
        }
    }
    public void problemShow(){
        Problem problem=new Problem();
        int len=problem.getLength();
        // generate random int to get question
        Random ran=new Random();
        int randi = ran.nextInt(len-1);
        String que= problem.getProblem(randi);
        questionStr=que;
        String toastStr="The Suggested Problem is "+que;
        // show problem on screen via toast
        Toast.makeText(PainttestActivity.this,toastStr,Toast.LENGTH_SHORT).show();
    }
    public void problemReview(){
        String toastStr="The Suggested Problem is "+questionStr;
        // show problem on screen via toast
        Toast.makeText(PainttestActivity.this,toastStr,Toast.LENGTH_SHORT).show();
    }
}