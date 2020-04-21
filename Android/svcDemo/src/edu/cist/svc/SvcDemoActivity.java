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

	private void findv()// ���ҿؼ�
	{
		startsvcButton = (Button) findViewById(R.id.startsvc);
		stopsvcButton = (Button) findViewById(R.id.stopsvc);
		startbindsvcButton = (Button) findViewById(R.id.startbindsvc);
		stopbindsvcButton = (Button) findViewById(R.id.stopbindsvc);
		startintentsvcButton = (Button) findViewById(R.id.startintentsvc);
	}

	private void bindbutton()// ����ť�󶨵���¼�
	{
		startsvcButton.setOnClickListener(this);
		stopsvcButton.setOnClickListener(this);
		startbindsvcButton.setOnClickListener(this);
		stopbindsvcButton.setOnClickListener(this);
		startintentsvcButton.setOnClickListener(this);
	}

	public void onClick(View v)// ʶ������ִ����Ӧ�¼�
	{
		Intent intent = new Intent();
		switch (v.getId()) {
		case R.id.startsvc:// �������star��service��ťʱ
			intent.setClass(SvcDemoActivity.this, startedSvc.class);
			Log.i("TESTSVC", "activity���߳�,�߳�IDΪ" + Thread.currentThread().getId());
			startService(intent);
			break;
		case R.id.stopsvc:// �ر� start service
			intent.setClass(SvcDemoActivity.this, startedSvc.class);
			Log.i("TESTSVC", "started service ended");
			stopService(intent);
			break;
		case R.id.startbindsvc:// ����bind service
			Log.i("TESTSVC", "bind service started,�߳�IDΪ" + Thread.currentThread().getId());
			connectSvc();
			break;
		case R.id.stopbindsvc:// ���bind service
			Log.i("TESTSVC", "bind service stopped");
			unBind();
			break;
		case R.id.startintentsvc:// ִ��intent service
			Log.i("TESTSVC", "intent service started,�߳�IDΪ" + Thread.currentThread().getId());

			i++;
			intent.putExtra("order", i);

			intent.setClass(SvcDemoActivity.this, intentSvc.class);
			startService(intent);
			break;
		default:
			break;
		}
	}

	private void unBind()// �Զ��������
	{
		if (isConnected) {
			unbindService(conn);
		}
	}

	private void connectSvc()// �Զ���󶨷���
	{
		Intent intent = new Intent(SvcDemoActivity.this, bindSvc.class);
		bindService(intent, conn, Context.BIND_AUTO_CREATE);
	}

	private ServiceConnection conn = new ServiceConnection() // �Զ���serviceconnection����
	{
		public void onServiceDisconnected(ComponentName name)// bind���ӶϿ�ʱִ��
		{
			isConnected = false;
		}

		public void onServiceConnected(ComponentName name, IBinder binder)// bind����ʱִ��
		{
			isConnected = true;
			MyBinder myBinder = (MyBinder) binder;// ע���ʽת��
			bindSvc service = myBinder.getService();// ͨ���˿ڻ�ȡserevice
			service.myMethod();// ���ò�ִ��bindsvc�з���

		}
	};

}