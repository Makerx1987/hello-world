/**
 * 
 */
package io.github.grdaimap.test;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

/**
 * @author cloud
 * 
 */
public class HelloActivity2 extends Activity {
	private TextView tv2;
	private Button bt3;
	private float f;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main2);
		tv2 = (TextView) findViewById(R.id.tv2);
		bt3 = (Button) findViewById(R.id.bt3);

		Intent it2 = new Intent();
		it2 = this.getIntent();
		f = Float.parseFloat(it2.getStringExtra("input"));
		if (f == 2.0) {
			tv2.setText("Yes, you are right.");
		} else {
			tv2.setText("No, you are wrong.");
		}
		bt3.setText("back");
		bt3.setOnClickListener(new OnClickListener() {

			public void onClick(View v) {
				// TODO Auto-generated method stub
				onBackPressed();
			}
		});

	}

}
