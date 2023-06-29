package com.example.guesswhoaini;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatDialogFragment;
import android.view.LayoutInflater;


import androidx.appcompat.app.AppCompatDialogFragment;

/**
 * This class is an accessory class which can be implemented as a part of the
 * Painting Board
 */

public class ColorDialog extends AppCompatDialogFragment {

//public Dialog onCreateDialog(Bundle savedInstanceState){
//    AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
//    builder.setTitle("Information")
//            .setMessage("This is a diag")
//            .setPositiveButton("ok", new DialogInterface.OnClickListener() {
//                @Override
//                public void onClick(DialogInterface dialog, int which) {
//
//                }
//            });
//    return builder.create();
//}

    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        // Get the layout inflater
        LayoutInflater inflater = requireActivity().getLayoutInflater();

        // Inflate and set the layout for the dialog
        // Pass null as the parent view because its going in the dialog layout
        builder.setView(inflater.inflate(R.layout.color_dialog_layout, null))
                // Add action buttons
                .setPositiveButton("sign in", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int id) {
                        // sign in the user ...
                    }
                })
                .setNegativeButton("cancel", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
//                        LoginDialogFragment.this.getDialog().cancel();
                    }
                });
        return builder.create();
    }
//    private void onClickRed(){
//        EditText button=exampleDialog.getDialog().findViewById(R.id.username);
//        button.setText("red");
//    }
//    private void onClickYel(){
//        EditText button=exampleDialog.getDialog().findViewById(R.id.username);
//        button.setText("yel");
//    }
//    private void onClickGre(){
//        EditText button=exampleDialog.getDialog().findViewById(R.id.username);
//        button.setText("gre");
//    }




}



