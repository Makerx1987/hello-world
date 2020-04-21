package p.p.p.p;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class UpdateUIActivity extends Activity implements SensorEventListener {
	/** Called when the activity is first created. */
	private TextView tv1, tv2, tv3, tv4;
	private EditText et1;
	private Button bt1;
	private float f1 = 0, f2 = 0, f3 = 0;
	private SensorManager sm = null;
	private Sensor sor = null;
	private List<Sensor> sensors = new ArrayList<Sensor>();
	private int sensorNumber;
	private String allName;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		tv1 = (TextView) findViewById(R.id.tv1);
		tv2 = (TextView) findViewById(R.id.tv2);
		tv3 = (TextView) findViewById(R.id.tv3);
		tv4 = (TextView) findViewById(R.id.tv4);
		et1 = (EditText) findViewById(R.id.et1);
		bt1 = (Button) findViewById(R.id.bt1);

		sm = (SensorManager) getSystemService(SENSOR_SERVICE);
		sensors = sm.getSensorList(Sensor.TYPE_ALL);
		sensorNumber = sensors.size();

		StringBuffer sb = new StringBuffer("");

		for (int i = 0; i < sensorNumber; i++) {
			sb.append(sensors.get(i).getType() + ", ");
		}

		allName = sb.toString();

		tv1.setText(allName);

		bt1.setOnClickListener(new OnClickListener() {

			public void onClick(View v) {
				// TODO Auto-generated method stub
				int input = Integer.parseInt(et1.getText().toString());
				if (input < sensorNumber) {
					int sensorName = input;
					sor = sm.getDefaultSensor(sensorName);
					sm.registerListener(UpdateUIActivity.this, sor, SensorManager.SENSOR_DELAY_NORMAL);

				}

			}
		});

		// handler = new Handler() { // 消息机制异步更新UI
		// @Override
		// public void handleMessage(Message msg) {
		// // 刷新图表
		// tv2.setText("X  :" + f1);
		// tv3.setText("Y  :" + f2);
		// tv4.setText("Z  :" + f3);
		// super.handleMessage(msg);
		// }
		// };
		//
		// Timer tm = new Timer();
		// TimerTask tt = new TimerTask() {
		// @Override
		// public void run() {
		// // TODO Auto-generated method stub
		// handler.sendEmptyMessage(1);
		// }
		// };
		// tm.schedule(tt, 1000, 1000);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see android.app.Activity#onPause()
	 */
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		sm.unregisterListener(this);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see android.app.Activity#onResume()
	 */
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();

	}

	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub

	}

	public void onSensorChanged(SensorEvent event) {
		// TODO Auto-generated method stub
		if (event.values.length >= 2) {
			f1 = event.values[0];
			f2 = event.values[1];
			f3 = event.values[2];

			tv2.setText("X:" + f1);
			tv3.setText("Y:" + f2);
			tv4.setText("Z:" + f3);
		} else {
			f1 = event.values[0];
			tv2.setText("X:" + f1);
		}

	}
}