/**
 * 
 */
package edu.dhu.cist.c13;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

/**
 * @author Odie_wx
 *
 */
public class myReceiver extends BroadcastReceiver {

	/* (non-Javadoc)
	 * @see android.content.BroadcastReceiver#onReceive(android.content.Context, android.content.Intent)
	 */
private static final String TAG = "MyReceiver";

	
	public void MyReceiver()
	{
		Log.i(TAG, "MyReceiver");
	}


	@Override
	public void onReceive(Context context, Intent intent)
	{
		Log.i(TAG, "onReceive: "+Thread.currentThread().getId());
	}

}
