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
		new myThread().start();// 调用新线程，用以执行服务

		// try
		// // 模拟执行服务
		// {
		// Log.i("TESTSVC", "startedSvc 正在运行,当前线程ID为：" +
		// Thread.currentThread().getId());
		// Thread.sleep(6000);// 模拟执行特别耗时的服务
		// } catch (InterruptedException e)
		// {
		// // TODO Auto-generated catch block
		// e.printStackTrace();
		// }

		// if (timer == null)//模拟服务示例2
		// {
		// // true表示以精灵线程(守护线程，优先级最低)模式启动
		// timer = new Timer(true);
		// TimerTask tt = new TimerTask()
		// {
		//
		// @Override
		// public void run()
		// {
		// Log.i("TESTSVC", "文件下载中...,当前线程ID为："+Thread.currentThread().getId());
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

	public class myThread extends Thread // 自定义用于执行服务的新线程
	{

		/*
		 * (non-Javadoc)
		 * 
		 * @see java.lang.Thread#run()
		 */
		@Override
		public void run()// 执行内容
		{
			// TODO Auto-generated method stub
			super.run();
			try {
				Log.i("TESTSVC", "startedSvc 正在运行,当前线程ID为：" + Thread.currentThread().getId());
				Thread.sleep(6000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

	}

}
