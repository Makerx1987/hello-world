package edu.dhu.cist.c13;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class BroadcastRecDemoActivity extends Activity {
    /** Called when the activity is first created. */
	protected static final String ACTION = "edu.dhu.cist.myACTION";
	private Button btnBroadcast;
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		btnBroadcast=(Button)findViewById(R.id.btnBroadcast);
		btnBroadcast.setOnClickListener(new OnClickListener()
		{
			public void onClick(View v)
			{
				Intent intent=new Intent();
				intent.setAction(ACTION);
				sendBroadcast(intent);
			}
		});
	}
}