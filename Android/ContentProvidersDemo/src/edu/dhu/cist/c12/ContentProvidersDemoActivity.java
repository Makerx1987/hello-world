package edu.dhu.cist.c12;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class ContentProvidersDemoActivity extends Activity {
	/** Called when the activity is first created. */
	private static final String TAG = "Test";
	private static final int ONE = 1;
	private static final int TWO = 2;
	private Button btnAdd1;
	private Button btnAdd2;
	private Button btnUpdate1;
	private Button btnUpdate2;
	private Button btnQuery1;
	private Button btnQuery2;
	private Button btnDel1;
	private Button btnDel2;
	private int times = 1, id_default = 12345671;;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		btnDel1 = (Button) findViewById(R.id.btnDel1);
		btnDel2 = (Button) findViewById(R.id.btnDel2);
		btnAdd1 = (Button) findViewById(R.id.btnAdd1);
		btnAdd2 = (Button) findViewById(R.id.btnAdd2);
		btnUpdate1 = (Button) findViewById(R.id.btnUpdate1);
		btnUpdate2 = (Button) findViewById(R.id.btnUpdate2);
		btnQuery1 = (Button) findViewById(R.id.btnQuery1);
		btnQuery2 = (Button) findViewById(R.id.btnQuery2);

		btnAdd1.setOnClickListener(listener);
		btnAdd2.setOnClickListener(listener);
		btnUpdate1.setOnClickListener(listener);
		btnUpdate2.setOnClickListener(listener);
		btnQuery1.setOnClickListener(listener);
		btnQuery2.setOnClickListener(listener);
		btnDel1.setOnClickListener(listener);
		btnDel2.setOnClickListener(listener);
	}

	private OnClickListener listener = new OnClickListener() {

		public void onClick(View v) {
			switch (v.getId()) {
			case R.id.btnAdd1:
				add(ONE);
				break;
			case R.id.btnAdd2:
				add(TWO);
				break;
			case R.id.btnUpdate1:
				update(ONE);
				break;
			case R.id.btnUpdate2:
				update(TWO);
				break;
			case R.id.btnQuery1:
				query(ONE);
				break;
			case R.id.btnQuery2:
				query(TWO);
				break;
			case R.id.btnDel1:
				delete(ONE);
				break;
			case R.id.btnDel2:
				delete(TWO);
				break;
			default:
				break;
			}

		}

	};

	protected void delete(int type) {
		ContentResolver contentResolver = getContentResolver();
		Uri url = null;
		String where = "";
		String[] selectionArgs = null;
		switch (type) {
		case ONE:
			url = Uri.parse("content://edu.dhu.cist.c72.MyDataContentProvider/MYSTUDENTDB");
			where = "_ID in (?,?)";
			selectionArgs = new String[] { "1", "2" };
			contentResolver.delete(url, where, selectionArgs);
			break;
		case TWO:
			url = Uri.parse("content://edu.dhu.cist.c72.MyDataContentProvider/MYSTUDENTDB/2");
			// where = "age = ?";
			// selectionArgs = new String[]{"23"};
			where = null;
			selectionArgs = null;
			contentResolver.delete(url, where, selectionArgs);
			break;
		}
	}

	protected void query(int type) {
		ContentResolver contentResolver = getContentResolver();
		Uri url = null;
		String[] projection = new String[] { "NAME", "STUID"};
		String selection = "";
		String[] selectionArgs = null;
		String sortOrder = "";
		Cursor cursor = null;
		switch (type) {
		case ONE:
			url = Uri.parse("content://edu.dhu.cist.c72.MyDataContentProvider/MYSTUDENTDB");
			selection = "_ID < ?";
			selectionArgs = new String[] { "3" };
			cursor = contentResolver.query(url, projection, selection, selectionArgs, sortOrder);
			while (cursor.moveToNext()) {
				Log.i(TAG, "_ID=" + cursor.getInt(0) + "name=" + cursor.getString(1) + "age=" + cursor.getShort(2));
			}
			break;
		case TWO:
			url = Uri.parse("content://edu.dhu.cist.c72.MyDataContentProvider/MYSTUDENTDB/1");
			cursor = contentResolver.query(url, projection, selection, selectionArgs, sortOrder);
			while (cursor.moveToNext()) {
				Log.i(TAG, "_ID" + cursor.getInt(0) + "name=" + cursor.getString(1) + "age=" + cursor.getShort(2));
			}
			break;
		}
	}

	protected void update(int type) {
		ContentResolver contentResolver = getContentResolver();
		Uri url = null;
		ContentValues values = new ContentValues();
		String where = "";
		String[] selectionArgs = null;
		switch (type) {
		case ONE:
			url = Uri.parse("content://edu.dhu.cist.c72.MyDataContentProvider/MYSTUDENTDB");
			values.put("NAME", "zs_" + times + "updated1");
			values.put("STUID", id_default);
			values.put("CLASS", "1");
			values.put("EMAIL", "zs_" + times + "@dhu.edu.cn");

			where = "NAME = ?";
			selectionArgs = new String[] { "zs_2" };
			contentResolver.update(url, values, where, selectionArgs);
			break;
		case TWO:
			url = Uri.parse("content://edu.dhu.cist.c72.MyDataContentProvider/MYSTUDENTDB/2");
			values.put("NAME", "zs_" + times + "updated2");
			values.put("STUID", id_default);
			values.put("CLASS", "1");
			values.put("EMAIL", "zs_" + times + "@dhu.edu.cn");
			
			where = null;
			selectionArgs = null;
			contentResolver.update(url, values, where, selectionArgs);
			break;
		}

	}

	protected void add(int type) {
		ContentResolver contentResolver = getContentResolver();
		Uri url = null;
		ContentValues values = new ContentValues();

		switch (type) {
		case ONE:
			values.put("NAME", "zs_" + times);
			values.put("STUID", id_default);
			values.put("CLASS", "1");
			values.put("EMAIL", "zs_" + times + "@dhu.edu.cn");

			url = Uri.parse("content://edu.dhu.cist.c72.MyDataContentProvider/MYSTUDENTDB");

			Log.i(TAG, contentResolver.insert(url, values).toString());
			break;
		case TWO:
			url = Uri.parse("content://edu.dhu.cist.c72.MyDataContentProvider/MYSTUDENTDB/1");
			values.put("NAME", "zs_" + times);
			values.put("STUID", id_default);
			values.put("CLASS", "2");
			values.put("EMAIL", "zs_" + times + "@dhu.edu.cn");

			Log.i(TAG, contentResolver.insert(url, values).toString());
			break;
		}
		times++;
		id_default++;
	}

}