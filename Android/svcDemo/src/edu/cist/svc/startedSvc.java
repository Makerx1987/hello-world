package edu.cist.svc;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

public class startedSvc extends Service {
	// private Timer timer;
	public final static String TAG = "TESTSVC";

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		new myThread().start();// �������̣߳�����ִ�з���

		// try
		// // ģ��ִ�з���
		// {
		// Log.i("TESTSVC", "startedSvc ��������,��ǰ�߳�IDΪ��" +
		// Thread.currentThread().getId());
		// Thread.sleep(6000);// ģ��ִ���ر��ʱ�ķ���
		// } catch (InterruptedException e)
		// {
		// // TODO Auto-generated catch block
		// e.printStackTrace();
		// }

		// if (timer == null)//ģ�����ʾ��2
		// {
		// // true��ʾ�Ծ����߳�(�ػ��̣߳����ȼ����)ģʽ����
		// timer = new Timer(true);
		// TimerTask tt = new TimerTask()
		// {
		//
		// @Override
		// public void run()
		// {
		// Log.i("TESTSVC", "�ļ�������...,��ǰ�߳�IDΪ��"+Thread.currentThread().getId());
		// }
		// };
		// timer.schedule(tt, 0, 1000);
		// }

		// TODO Auto-generated method stub
		return super.onStartCommand(intent, flags, startId);
		// return START_STICKY;

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see android.app.Service#onCreate()
	 */
	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
	}

	@Override
	public void onDestroy() {
		// timer.cancel();
		// TODO Auto-generated method stub
		super.onDestroy();
	}

	public class myThread extends Thread // �Զ�������ִ�з�������߳�
	{

		/*
		 * (non-Javadoc)
		 * 
		 * @see java.lang.Thread#run()
		 */
		@Override
		public void run()// ִ������
		{
			// TODO Auto-generated method stub
			super.run();
			try {
				Log.i("TESTSVC", "startedSvc ��������,��ǰ�߳�IDΪ��" + Thread.currentThread().getId());
				Thread.sleep(6000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

}
