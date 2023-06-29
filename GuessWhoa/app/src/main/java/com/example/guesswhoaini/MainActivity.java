package com.example.guesswhoaini;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void aboutFunction(View view)
    {
        Intent intent = new Intent(this,AboutActivity.class);
        startActivity(intent);
    }

    public void startFunction(View view)
    {
        Intent intent = new Intent(this,SelectRoleActivity.class);
        startActivity(intent);
    }

    public void painttestFunction(View view)
    {
        Intent intent = new Intent(this,PainttestActivity.class);
        startActivity(intent);
    }

    public void painttestRecFunction(View view)
    {
        Intent intent = new Intent(this, PainttestRecActivity.class);
        startActivity(intent);
    }


}
