package edu.cist.svc;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

/**
 * 
 */

/**
 * @author Odie_wx
 * 
 */
public class bindSvc extends Service {
	// private MediaPlayer mediaPlayer;
	// private Timer timer;
	public final IBinder binder = new MyBinder();

	// ��·ʽд��
	public class MyBinder extends Binder {
		bindSvc getService()// ��չIBinder�˿ڣ�ʹ����Է��ص�ǰservice
		{
			return bindSvc.this;
		}
	}

	@Override
	public IBinder onBind(Intent intent) {
		return binder;// ����һ�����Բ���bindSvc�Ķ˿ڣ���ʽΪIBinder
	}

	//

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
	}

	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		// TODO Auto-generated method stub
		return super.onStartCommand(intent, flags, startId);
	}

	@Override
	public boolean onUnbind(Intent intent) {
		// TODO Auto-generated method stub
		// timer.cancel();
		return super.onUnbind(intent);
	}

	public void myMethod()// bindservice��ִ�еķ���
	{
		Log.d("TESTSVC", "bindSvc ��������,�߳�IDΪ��" + Thread.currentThread().getId());

		// if (timer == null)//ģ���̨����2
		// {
		// // true��ʾ�����ȼ����ģʽ����
		// timer = new Timer(true);
		// TimerTask tt = new TimerTask()
		// {
		//
		// @Override
		// public void run()
		// {
		// Log.d("TESTSVC",
		// "bindSvc ��������,�߳�IDΪ��"+Thread.currentThread().getId());
		// }
		// };
		// timer.schedule(tt, 0, 1000);
		// }
	}

}
