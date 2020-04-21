/**
 * 
 */
package edu.cist.svc;

import android.app.IntentService;
import android.content.Intent;
import android.util.Log;

/**
 * @author Odie_wx
 * 
 */
public class intentSvc extends IntentService
{
private int j=0;
	/**
	 * @author Odie_wx
	 * 
	 */
/*这里需要注意一下，Eclipse默认生成的是带参数的构造函数，但是这样会引起异常的
	java.lang.InstantiationException: can't instantiate class..... no empty constructor 错误
*/	
	public intentSvc()
	{
		super("intentSvc");
		// TODO Auto-generated constructor stub
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see android.app.IntentService#onHandleIntent(android.content.Intent)
	 */
	@Override
	protected void onHandleIntent(Intent intent)//多个任务如何处理
	{
		// TODO Auto-generated method stub
		j=intent.getIntExtra("order", 0);
		try
		{
			Log.i("TESTSVC", "第"+j+"个intent，"+"当前线程ID为：" + Thread.currentThread().getId());
			Thread.sleep(6000);//单位是ms，*1000为秒
		} catch (InterruptedException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
