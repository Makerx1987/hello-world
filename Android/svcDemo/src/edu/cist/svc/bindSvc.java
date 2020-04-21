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

	// 套路式写法
	public class MyBinder extends Binder {
		bindSvc getService()// 扩展IBinder端口，使其可以返回当前service
		{
			return bindSvc.this;
		}
	}

	@Override
	public IBinder onBind(Intent intent) {
		return binder;// 返回一个可以操作bindSvc的端口，格式为IBinder
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

	public void myMethod()// bindservice将执行的方法
	{
		Log.d("TESTSVC", "bindSvc 正在运行,线程ID为：" + Thread.currentThread().getId());

		// if (timer == null)//模拟后台服务2
		// {
		// // true表示以优先级最低模式启动
		// timer = new Timer(true);
		// TimerTask tt = new TimerTask()
		// {
		//
		// @Override
		// public void run()
		// {
		// Log.d("TESTSVC",
		// "bindSvc 正在运行,线程ID为："+Thread.currentThread().getId());
		// }
		// };
		// timer.schedule(tt, 0, 1000);
		// }
	}

}
