package io.github.grdaimap.test;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class HelloActivity extends Activity {
	/** Called when the activity is first created. */
	private Button bt1;
	private Button bt2;
	private TextView tv1;
	private EditText et1;
	private String str;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		bt1 = (Button) findViewById(R.id.bt1);
		bt2 = (Button) findViewById(R.id.bt2);
		tv1 = (TextView) findViewById(R.id.tv1);
		et1 = (EditText) findViewById(R.id.et1);

		tv1.setText("1+1=?");
		bt1.setText("run");
		bt1.setOnClickListener(new OnClickListener() {

			public void onClick(View v) {
				// TODO Auto-generated method stub
				Toast.makeText(HelloActivity.this, "waiting...",
						Toast.LENGTH_SHORT).show();
				str = et1.getText().toString();
				if (str.trim().equals("")) {
					Toast.makeText(HelloActivity.this, "no input",
							Toast.LENGTH_SHORT).show();
					return;
				}
				Intent it = new Intent();
				it.putExtra("input", str);
				it.setClass(HelloActivity.this, HelloActivity2.class);
				startActivity(it);
			}
		});
		OnClickListener listener = new OnClickListener() {

			public void onClick(View v) {
				// TODO Auto-generated method stub
				Toast.makeText(HelloActivity.this, "R U OK?",
						Toast.LENGTH_SHORT).show();
			}
		};
		bt2.setOnClickListener(listener);
	}
}