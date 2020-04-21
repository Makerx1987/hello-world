package edu.dhu.cist.c72;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

public class SQLiteDatabaseActivity extends Activity implements OnClickListener {

	private Button button, btnUpdate, btnDelete, btnQuery, clearall, destroy, pullout;
	private EditText inputname, inputid, inputclass, inputemail;
	private String[] list = { "请选择..." };

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		initView();
		setEvent();

		try {
			newspinner();
		} catch (Exception e) {
			Toast.makeText(this, "数据库为空，请添加数据!", 0).show();
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see android.app.Activity#onDestroy()
	 */
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		myData helper = new myData(SQLiteDatabaseActivity.this, SQLiteDatabaseActivity.this.getFilesDir()
				+ "/new_data.db");
		SQLiteDatabase database = helper.getWritableDatabase();
		database.close();
		helper.close();
	}

	private void setEvent() {
		button.setOnClickListener(this);
		btnUpdate.setOnClickListener(this);
		btnDelete.setOnClickListener(this);
		btnQuery.setOnClickListener(this);
		clearall.setOnClickListener(this);
		pullout.setOnClickListener(this);
		destroy.setOnClickListener(this);
	}

	private void initView() {
		inputname = (EditText) findViewById(R.id.name);
		inputid = (EditText) findViewById(R.id.stuid);
		inputclass = (EditText) findViewById(R.id.stclass);
		inputemail = (EditText) findViewById(R.id.email);
		button = (Button) findViewById(R.id.id_databaseButton);
		btnUpdate = (Button) findViewById(R.id.id_databaseButtonUpdate);
		btnDelete = (Button) findViewById(R.id.id_databaseButtonDelete);
		btnQuery = (Button) findViewById(R.id.id_databaseButtonQuery);
		clearall = (Button) findViewById(R.id.id_clearall);
		pullout = (Button) findViewById(R.id.id_pullout);
		destroy = (Button) findViewById(R.id.id_destroy);

	}

	public class myData extends SQLiteOpenHelper {
		public myData(Context context, String str) {
			super(context, str, null, 1);
			// TODO Auto-generated constructor stub
		}

		@Override
		public void onCreate(SQLiteDatabase db) {
			// TODO Auto-generated method stub
			String DATABASE_SQL = "CREATE TABLE " + "MYSTUDENTDB" + " (" + "_ID"
					+ " INTEGER primary key autoincrement, " + "NAME" + " text not null, " + "STUID"
					+ " text not null, " + "CLASS" + " text not null, " + "EMAIL" + " text not null " + ");";

			db.execSQL(DATABASE_SQL);

		}

		@Override
		public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
			// TODO Auto-generated method stub
		}
	}

	public void onClick(View v) {
		// TODO Auto-generated method stub

		final myData helper = new myData(SQLiteDatabaseActivity.this, SQLiteDatabaseActivity.this.getFilesDir()
				+ "/new_data.db");
		final SQLiteDatabase database = helper.getWritableDatabase();
		AlertDialog.Builder builder = new AlertDialog.Builder(SQLiteDatabaseActivity.this);
		builder.setIcon(R.drawable.ic_launcher);

		switch (v.getId()) {
		case R.id.id_databaseButton:// 添加元素

			ContentValues value1 = new ContentValues();
			value1.put("NAME", inputname.getText().toString());
			value1.put("STUID", inputid.getText().toString());
			value1.put("CLASS", inputclass.getText().toString());
			value1.put("EMAIL", inputemail.getText().toString());
			if (!inputname.getText().toString().isEmpty()) {
				long i = database.insert("MYSTUDENTDB", null, value1);
				if (i == -1) {
					Toast.makeText(this, "添加失败", 0).show();
				} else {
					Toast.makeText(this, "添加成功", 0).show();
				}
			}

			database.close();
			inputname.setText("");
			inputid.setText("");
			inputclass.setText("");
			inputemail.setText("");
			break;

		case R.id.id_databaseButtonUpdate:// 更新元素

			ContentValues value2 = new ContentValues();
			value2.put("NAME", inputname.getText().toString());
			value2.put("STUID", inputid.getText().toString());
			value2.put("CLASS", inputclass.getText().toString());
			value2.put("EMAIL", inputemail.getText().toString());
			if (!inputname.getText().toString().isEmpty()) {
				String where = "NAME" + " = " + inputname.getText().toString();
				int o = database.update("MYSTUDENTDB", value2, where, null);
				Toast.makeText(this, "" + o + "条数据受影响", 0).show();
			}
			database.close();

			break;

		case R.id.id_databaseButtonDelete:// 删除元素

			String where2 = "NAME" + " = " + inputname.getText().toString();
			if (!inputid.getText().toString().isEmpty()) {
				int o = database.delete("MYSTUDENTDB", where2, null);
				Toast.makeText(this, "" + o + "条数据受影响", 0).show();
				Cursor cursor = database.query("MYSTUDENTDB", null, null, null, null, null, null);
				if (cursor.getCount() == 0) {

					String[] list1 = { "请选择..." };
					list = list1;
					Spinner spinner = (Spinner) findViewById(R.id.spinner);
					ArrayAdapter<CharSequence> adapter = new ArrayAdapter<CharSequence>(this,
							android.R.layout.simple_spinner_item, list);
					spinner.setAdapter(adapter);
				}
			}
			database.close();
			break;

		case R.id.id_databaseButtonQuery:// 查询所有元素依次弹窗

			Cursor cursor = database.query("MYSTUDENTDB", null, null, null, null, null, null);
			if (cursor.getCount() > 0) {
				int i = 0;
				Intent it = new Intent();

				while (cursor.moveToNext()) {
					String id = "学号：" + cursor.getString(1) + ";";
					String name = "姓名：" + cursor.getString(2) + ";";
					String age = "班级：" + cursor.getString(3) + ";";
					String address = "邮箱：" + cursor.getString(4) + ".";
					String info = cursor.getString(0).toString() + ") " + id + name + age + address;

					it.putExtra(String.valueOf(i), info);
					i++;
				}
				it.putExtra("num", i);
				it.setClass(this, Newa.class);
				startActivity(it);
			} else {
				Toast.makeText(this, "" + cursor.getCount() + "", 0).show();
			}
			database.close();
			break;
		case R.id.id_clearall:// 清空

			inputname.setText("");
			inputid.setText("");
			inputclass.setText("");
			inputemail.setText("");

			break;
		case R.id.id_pullout:

			builder.setTitle(list[0]);
			if (list.length == 1)
				break;
			String[] list2 = new String[list.length - 1];
			System.arraycopy(list, 1, list2, 0, list2.length);
			final String[] list3 = list2;
			boolean[] initChoose2 = new boolean[list3.length];
			for (int i = 0; i < initChoose2.length; i++) {
				initChoose2[i] = false;
			}
			final boolean[] initChoose = initChoose2;
			builder.setMultiChoiceItems(list3, initChoose, new DialogInterface.OnMultiChoiceClickListener() {
				public void onClick(DialogInterface dialog, int which, boolean isChecked) {

				}
			});
			builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int which) {
					Intent it = new Intent();
					myData helper = new myData(SQLiteDatabaseActivity.this, SQLiteDatabaseActivity.this.getFilesDir()
							+ "/new_data.db");
					SQLiteDatabase database = helper.getWritableDatabase();
					StringBuffer s = new StringBuffer("");
					for (int i = 0; i < initChoose.length; i++) {
						if (initChoose[i]) {
							Cursor cursor = database.query("MYSTUDENTDB", null, "NAME=?", new String[] { list3[i] },
									null, null, null);

							if (cursor.getCount() > 0) {
								while (cursor.moveToNext()) {
									String id = "学号：" + cursor.getString(1) + ";";
									String name = "姓名：" + cursor.getString(2) + ";";
									String age = "班级：" + cursor.getString(3) + ";";
									String address = "邮箱：" + cursor.getString(4) + ".";
									String info = id + name + age + address;
									s.append(info + "\n");
								}

							} else {
								Toast.makeText(getApplicationContext(), "???????????", 0).show();
							}
						}
					}
					database.close();
					it.putExtra("info", s.toString());
					it.setClass(SQLiteDatabaseActivity.this, fileout.class);
					Log.i("TESTSVC", "activity主线程,线程ID为" + Thread.currentThread().getId());
					Toast.makeText(getApplicationContext(), "后台服务启动", 1000).show();
					startService(it);
					Log.i("TESTSVC", "started service ended");
					stopService(it);
					Toast.makeText(getApplicationContext(), "后台服务终止", 1000).show();

				}
			});
			builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {

				public void onClick(DialogInterface dialog, int which) {
					dialog.dismiss();
					// TODO Auto-generated method stub

				}
			});
			builder.create().show();
			break;
		case R.id.id_destroy:
			builder.setTitle("提示");
			builder.setMessage("确认退出吗？");
			builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface arg0, int arg1) {
					finish();
				}
			});
			builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface arg0, int arg1) {

				}
			});
			builder.create().show();

			break;

		}
		try {
			newspinner();
		} catch (Exception e) {
			Toast.makeText(this, "数据库为空，请添加数据!", 0).show();
		}
	}

	public void newspinner() {
		myData helper = new myData(SQLiteDatabaseActivity.this, SQLiteDatabaseActivity.this.getFilesDir()
				+ "/new_data.db");
		SQLiteDatabase database = helper.getWritableDatabase();

		Cursor cursor = database.query("MYSTUDENTDB", null, null, null, null, null, null);
		if (cursor.getCount() > 0) {
			int i = 2;
			while (cursor.moveToNext()) {
				String id = cursor.getString(1);

				String[] list2 = new String[i];
				System.arraycopy(list, 0, list2, 0, i - 1);
				list2[i - 1] = id;
				list = list2;
				i++;

			}
		} else {

		}
		database.close();
		Spinner spinner = (Spinner) findViewById(R.id.spinner);
		ArrayAdapter<CharSequence> adapter = new ArrayAdapter<CharSequence>(this, android.R.layout.simple_spinner_item,
				list);
		Log.i("", list[0] + list[1]);
		spinner.setAdapter(adapter);
		spinner.setOnItemSelectedListener(new OnItemSelectedListener() {

			public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
				if (arg3 == 0) {

				} else {
					myData helper = new myData(SQLiteDatabaseActivity.this, SQLiteDatabaseActivity.this.getFilesDir()
							+ "/new_data.db");
					SQLiteDatabase database = helper.getWritableDatabase();

					Log.i(" ", arg0.getItemAtPosition(arg2).toString());
					String[] iii = { arg0.getItemAtPosition(arg2).toString() };
					Cursor cursor = database.query("MYSTUDENTDB", null, "NAME=?", iii, null, null, null);
					if (cursor.getCount() > 0) {
						while (cursor.moveToNext()) {
							String id = "学号：" + cursor.getString(1) + "; ";
							String name = "名字：" + cursor.getString(2) + "; ";
							String age = "班级：" + cursor.getString(3) + "; ";
							String address = "邮箱：" + cursor.getString(4) + ".";
							Toast.makeText(getApplicationContext(), id + name + age + address, 0).show();
						}
					} else {

					}
					database.close();
				}

				// TODO Auto-generated method stub

			}

			public void onNothingSelected(AdapterView<?> arg0) {
				// TODO Auto-generated method stub

			}
		});
	}
}