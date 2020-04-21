/**
 * 
 */
package edu.dhu.cist.c72;

import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;

import android.app.Service;
import android.content.Intent;
import android.os.Environment;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

/**
 * @author cloud
 * 
 */
public class fileout extends Service {
	private String s;

	/*
	 * (non-Javadoc)
	 * 
	 * @see android.app.Service#onBind(android.content.Intent)
	 */
	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see android.app.Service#onStartCommand(android.content.Intent, int, int)
	 */
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		s = intent.getStringExtra("info");

		new myThread().start();

		// TODO Auto-generated method stub
		return super.onStartCommand(intent, flags, startId);
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

			String filename = "/export.txt";
			try {
				// 如果手机插入了SD卡，而且应用程序具有访问SD的权限
				if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
					final String fp = Environment.getExternalStorageDirectory().getCanonicalPath() + filename;
					File fl = new File(fp);
					Log.i(" ", fp);
					Handler handler = new Handler(Looper.getMainLooper());
					handler.post(new Runnable() {
						public void run() {
							Toast.makeText(getApplicationContext(), "数据已保存到" + fp, Toast.LENGTH_LONG).show();
						}
					});

					if (!fl.exists()) {
						fl.createNewFile();
					}

					FileOutputStream fos = new FileOutputStream(fl);
					PrintStream ps = new PrintStream(fos);// 输出流包装为打印流
					ps.print(s);// 打印流的内容，名叫 content的string数据
					fos.close();
					ps.close();

				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

	}

}
