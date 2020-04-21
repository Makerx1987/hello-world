/**
 * 
 */
package edu.dhu.cist.c12_2;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

/**
 * @author Odie_wx
 *
 */
public class FirstReceiver extends BroadcastReceiver {

	/* (non-Javadoc)
	 * @see android.content.BroadcastReceiver#onReceive(android.content.Context, android.content.Intent)
	 */
private static final String TAG = "MyReceiver";

	
	public FirstReceiver()
	{
		Log.i(TAG, "MyReceiver");
	}


	@Override
	public void onReceive(Context context, Intent intent)
	{
		Log.i(TAG, "onReceive 1st receiver");
	}

}
