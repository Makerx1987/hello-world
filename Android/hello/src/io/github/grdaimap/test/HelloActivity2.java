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
	private Button bt2;
	private int f1, f2, f3;
	private String str;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main2);
		tv2 = (TextView) findViewById(R.id.tv2);
		bt2 = (Button) findViewById(R.id.bt2);

		Intent it2 = new Intent();
		it2 = this.getIntent();
		f1 = Integer.parseInt(it2.getStringExtra("input1"));
		f2 = Integer.parseInt(it2.getStringExtra("input2"));
		f3 = f1 + f2;
		str = f1 + "+" + f2 + "=" + f3;
		tv2.setText(str);
		bt2.setText("back");
		bt2.setOnClickListener(new OnClickListener() {

			public void onClick(View v) {
				// TODO Auto-generated method stub
				onBackPressed();
			}
		});

	}

}
