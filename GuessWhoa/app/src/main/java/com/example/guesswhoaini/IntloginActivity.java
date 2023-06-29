package com.example.guesswhoaini;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class IntloginActivity extends AppCompatActivity {
    EditText username, password;
    Button btnSignIn;
    FirebaseAuth mFirebaseAuth;
    private FirebaseAuth.AuthStateListener mAuthStateListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_intlogin);

        mFirebaseAuth = FirebaseAuth.getInstance();
        username = findViewById(R.id.username_edit);
        password = findViewById(R.id.password_edit);
        btnSignIn = findViewById(R.id.button9);

        mAuthStateListener = new FirebaseAuth.AuthStateListener() {
            @Override
            public void onAuthStateChanged(@NonNull FirebaseAuth firebaseAuth) {
                FirebaseUser mFirebaseUser = mFirebaseAuth.getCurrentUser();
                if( mFirebaseUser != null ){
                    Toast.makeText(IntloginActivity.this,"You are logged in",Toast.LENGTH_SHORT).show();
                    Intent i = new Intent(IntloginActivity.this, IntloginActivity.class);
                    startActivity(i);
                }
                else{
                    Toast.makeText(IntloginActivity.this,"Please Login",Toast.LENGTH_SHORT).show();
                }
            }
        };
    }


    public void returnFunction(View view)
    {
        Intent intent = new Intent(this,MainActivity.class);
        startActivity(intent);
    }

    public void regFunction(View view)
    {
        Intent intent = new Intent(this,RegActivity.class);
        startActivity(intent);
    }

    public void loginFunction(View view)
    {
        String username_text = username.getText().toString();
        String pwd = password.getText().toString();
        if(username_text.isEmpty()){
            username.setError("Please enter email id");
            username.requestFocus();
        }
        else  if(pwd.isEmpty()){
            password.setError("Please enter your password");
            password.requestFocus();
        }
        else  if(username_text.isEmpty() && pwd.isEmpty()){
            Toast.makeText(IntloginActivity.this,"Fields Are Empty!",Toast.LENGTH_SHORT).show();
        }
        else  if(!(username_text.isEmpty() && pwd.isEmpty())){
            mFirebaseAuth.signInWithEmailAndPassword(username_text, pwd).addOnCompleteListener(IntloginActivity.this, new OnCompleteListener<AuthResult>() {
                @Override
                public void onComplete(@NonNull Task<AuthResult> task) {
                    if(!task.isSuccessful()){
                        Toast.makeText(IntloginActivity.this,"Login Error,to Please Login Again",Toast.LENGTH_SHORT).show();
                    }
                    else{
                        Intent intToHome = new Intent(IntloginActivity.this,MessageActivity.class);
                        startActivity(intToHome);
                    }
                }
            });
        }
        else{
            Toast.makeText(IntloginActivity.this,"Error Occurred!",Toast.LENGTH_SHORT).show();

        }
    }
}


