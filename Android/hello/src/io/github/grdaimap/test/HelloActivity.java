package io.github.grdaimap.test;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class HelloActivity extends Activity {
	/** Called when the activity is first created. */
	private Button bt1;

	private EditText et1, et2;
	private String str1, str2;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		bt1 = (Button) findViewById(R.id.bt1);

		et1 = (EditText) findViewById(R.id.et1);
		et2 = (EditText) findViewById(R.id.et2);
		bt1.setOnClickListener(new OnClickListener() {

			public void onClick(View v) {
				// TODO Auto-generated method stub
				Toast.makeText(HelloActivity.this, "waiting...", 100).show();
				str1 = et1.getText().toString();
				str2 = et2.getText().toString();
				if (str1.trim().equals("") || str2.trim().equals("")) {
					Toast.makeText(HelloActivity.this, "no input",
							Toast.LENGTH_SHORT).show();
					return;
				}
				Intent it = new Intent();
				it.putExtra("input1", str1);
				it.putExtra("input2", str2);
				it.setClass(HelloActivity.this, HelloActivity2.class);
				startActivity(it);
			}
		});
	}

	/*
	 * (non-Java-doc)
	 * 
	 * @see android.app.Activity#onStart()
	 */
	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
		et1.setText("");
		et2.setText("");
	}

}