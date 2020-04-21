package edu.dhu.cist.c9;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;

public class SpinnerActivity extends Activity {
	/** Called when the activity is first created. */
	private String[] list = { "请选择...", "火星", "水星", "天王星" };

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		Spinner spinner = (Spinner) findViewById(R.id.spinner);
		// ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(
		// this, R.array.spinner_array,android.R.layout.simple_spinner_item);

		ArrayAdapter<CharSequence> adapter = new ArrayAdapter<CharSequence>(
				this, android.R.layout.simple_spinner_item, list);

		spinner.setAdapter(adapter);
		spinner.setOnItemSelectedListener(new OnItemSelectedListener() {

			public void onItemSelected(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				if (arg3 == 0) {

				} else {
					Toast.makeText(
							arg0.getContext(),
							"啊哦，你原来是 "
									+ arg0.getItemAtPosition(arg2).toString()
									+ "人！！", Toast.LENGTH_LONG).show();
				}

				// TODO Auto-generated method stub

			}

			public void onNothingSelected(AdapterView<?> arg0) {
				// TODO Auto-generated method stub

			}
		});
	}
}