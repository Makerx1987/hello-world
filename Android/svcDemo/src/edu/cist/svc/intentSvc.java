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
/*������Ҫע��һ�£�EclipseĬ�����ɵ��Ǵ������Ĺ��캯�������������������쳣��
	java.lang.InstantiationException: can't instantiate class..... no empty constructor ����
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
	protected void onHandleIntent(Intent intent)//���������δ���
	{
		// TODO Auto-generated method stub
		j=intent.getIntExtra("order", 0);
		try
		{
			Log.i("TESTSVC", "��"+j+"��intent��"+"��ǰ�߳�IDΪ��" + Thread.currentThread().getId());
			Thread.sleep(6000);//��λ��ms��*1000Ϊ��
		} catch (InterruptedException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
