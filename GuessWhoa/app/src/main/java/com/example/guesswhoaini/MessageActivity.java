package com.example.guesswhoaini;

import android.content.Intent;
import android.os.Bundle;
import android.text.format.DateFormat;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Adapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.firebase.ui.database.FirebaseListAdapter;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.FirebaseDatabase;



public class MessageActivity extends AppCompatActivity {
    int counter = 0;
    FirebaseAuth mFirebaseAuth = FirebaseAuth.getInstance();
    FirebaseUser mFirebaseUser = mFirebaseAuth.getCurrentUser();
    String emailname = mFirebaseUser.getEmail();
    private FirebaseListAdapter<ChatMessage> adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.message1);
        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        displayChatMessages();
        detectWinner();
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText input = (EditText) findViewById(R.id.input);

                // Read the input field and push a new instance
                // of ChatMessage to the Firebase database
                FirebaseDatabase.getInstance()
                        .getReference()
                        .push()
                        .setValue(new ChatMessage(input.getText().toString(),
                                emailname)
                        );

                // Clear the input
                input.setText("");
            }
        });
    }

    private void displayChatMessages() {
        final ListView listOfMessages = (ListView)findViewById(R.id.list_of_messages1);

        listOfMessages.setTranscriptMode(ListView.TRANSCRIPT_MODE_NORMAL);
        adapter = new FirebaseListAdapter<ChatMessage>(this, ChatMessage.class,
                R.layout.message, FirebaseDatabase.getInstance().getReference()) {
            @Override

            protected void populateView(View v, ChatMessage model, int position) {

                if(model.getType()!=1 && model!=null){
                    Log.d("out",String.valueOf(model.getType()));
                // Get references to the views of message.xml
                TextView messageText = (TextView)v.findViewById(R.id.message_text);
                TextView messageUser = (TextView)v.findViewById(R.id.message_user);
                TextView messageTime = (TextView)v.findViewById(R.id.message_time);

                // Set their text
                messageText.setText(model.getMessageText());
                messageUser.setText(model.getMessageUser());

                // Format the date before showing it
                messageTime.setText(DateFormat.format("dd-MM-yyyy (HH:mm:ss)",
                        model.getMessageTime()));


                scrollMyListViewToBottom(listOfMessages,adapter);}
            }
        };

        listOfMessages.setAdapter(adapter);
    }

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
        //detectWinner();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater menuInflater = getMenuInflater();
        menuInflater.inflate(R.menu.menu2, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()) {
            case R.id.switchboard:
                Intent intent = new Intent(this,PainttestRecActivity.class);
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
