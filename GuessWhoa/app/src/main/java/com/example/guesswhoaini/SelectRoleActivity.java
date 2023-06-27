package com.example.guesswhoaini;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import com.example.guesswhoaini.R;

public class SelectRoleActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_role);
    }

    public void painterFunction(View view)
    {
        Intent intent = new Intent(this,PainttestActivity.class);
        startActivity(intent);
    }

    public void playerFunction(View view)
    {
        Intent intent = new Intent(this,IntloginActivity.class);
        startActivity(intent);
    }

    public void returnFunction(View view)
    {
        Intent intent = new Intent(this,MainActivity.class);
        startActivity(intent);
    }


}