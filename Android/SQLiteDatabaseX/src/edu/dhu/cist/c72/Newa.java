/**
 * 
 */
package edu.dhu.cist.c72;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

/**
 * @author cloud
 * 
 */
public class Newa extends Activity {

	private TextView hall;
	private int num;
	private String s;

	/*
	 * (non-Javadoc)
	 * 
	 * @see android.app.Activity#onCreate(android.os.Bundle)
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.newa);

		Intent it2 = new Intent();
		it2 = this.getIntent();
		hall = (TextView) findViewById(R.id.hall);
		num = it2.getIntExtra("num", 0);
		s = "当前已有数据如下:";
		for (int i = 0; i < num; i++) {
			s += "\n" + it2.getStringExtra(String.valueOf(i));
		}
		hall.setText(s);
	}

}
