package edu.cist.svc;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import edu.cist.svc.bindSvc.MyBinder;

public class SvcDemoActivity extends Activity implements OnClickListener {
	/** Called when the activity is first created. */
	private Button startsvcButton, stopsvcButton, startbindsvcButton, stopbindsvcButton, startintentsvcButton;
	private Boolean isConnected = false;
	private int i = 0;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		findv();
		bindbutton();
	}

	private void findv()// 查找控件
	{
		startsvcButton = (Button) findViewById(R.id.startsvc);
		stopsvcButton = (Button) findViewById(R.id.stopsvc);
		startbindsvcButton = (Button) findViewById(R.id.startbindsvc);
		stopbindsvcButton = (Button) findViewById(R.id.stopbindsvc);
		startintentsvcButton = (Button) findViewById(R.id.startintentsvc);
	}

	private void bindbutton()// 给按钮绑定点击事件
	{
		startsvcButton.setOnClickListener(this);
		stopsvcButton.setOnClickListener(this);
		startbindsvcButton.setOnClickListener(this);
		stopbindsvcButton.setOnClickListener(this);
		startintentsvcButton.setOnClickListener(this);
	}

	public void onClick(View v)// 识别点击，执行相应事件
	{
		Intent intent = new Intent();
		switch (v.getId()) {
		case R.id.startsvc:// 点击开启star是service按钮时
			intent.setClass(SvcDemoActivity.this, startedSvc.class);
			Log.i("TESTSVC", "activity主线程,线程ID为" + Thread.currentThread().getId());
			startService(intent);
			break;
		case R.id.stopsvc:// 关闭 start service
			intent.setClass(SvcDemoActivity.this, startedSvc.class);
			Log.i("TESTSVC", "started service ended");
			stopService(intent);
			break;
		case R.id.startbindsvc:// 开启bind service
			Log.i("TESTSVC", "bind service started,线程ID为" + Thread.currentThread().getId());
			connectSvc();
			break;
		case R.id.stopbindsvc:// 解绑bind service
			Log.i("TESTSVC", "bind service stopped");
			unBind();
			break;
		case R.id.startintentsvc:// 执行intent service
			Log.i("TESTSVC", "intent service started,线程ID为" + Thread.currentThread().getId());

			i++;
			intent.putExtra("order", i);

			intent.setClass(SvcDemoActivity.this, intentSvc.class);
			startService(intent);
			break;
		default:
			break;
		}
	}

	private void unBind()// 自定义解绑服务
	{
		if (isConnected) {
			unbindService(conn);
		}
	}

	private void connectSvc()// 自定义绑定服务
	{
		Intent intent = new Intent(SvcDemoActivity.this, bindSvc.class);
		bindService(intent, conn, Context.BIND_AUTO_CREATE);
	}

	private ServiceConnection conn = new ServiceConnection() // 自定义serviceconnection对象
	{
		public void onServiceDisconnected(ComponentName name)// bind连接断开时执行
		{
			isConnected = false;
		}

		public void onServiceConnected(ComponentName name, IBinder binder)// bind连接时执行
		{
			isConnected = true;
			MyBinder myBinder = (MyBinder) binder;// 注意格式转换
			bindSvc service = myBinder.getService();// 通过端口获取serevice
			service.myMethod();// 调用并执行bindsvc中方法

		}
	};

}