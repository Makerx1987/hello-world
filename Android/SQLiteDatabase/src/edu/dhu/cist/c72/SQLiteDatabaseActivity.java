package edu.dhu.cist.c72;

import java.io.File;
import java.security.PublicKey;
import android.app.Activity;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class SQLiteDatabaseActivity extends Activity implements OnClickListener {

	private Button button, btnUpdate, btnDelete, btnQuery, clearall;
	private EditText inputname, inputid, inputclass, inputemail;

	// final String str = SQLiteDatabaseActivity.this.getFilesDir() +
	// "/myDataBase.db";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		initView();
		setEvent();
		// Log.i("TEST", this.getFilesDir() + "/myDataBase.db");
	}

	private void setEvent() {
		button.setOnClickListener(this);
		btnUpdate.setOnClickListener(this);
		btnDelete.setOnClickListener(this);
		btnQuery.setOnClickListener(this);
		clearall.setOnClickListener(this);
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
	}

	public class myData extends SQLiteOpenHelper {
		public myData(Context context,String str) {
			super(context, str, null, 1);
			// TODO Auto-generated constructor stub
		}

		@Override
		public void onCreate(SQLiteDatabase db) {
			// TODO Auto-generated method stub
			String DATABASE_SQL = "CREATE TABLE " + "MYSTUDENTDB" + " ("
					+ "_ID" + " INTEGER primary key autoincrement, " + "NAME"
					+ " text not null, " + "STUID" + " text not null, "
					+ "CLASS" + " text not null, " + "EMAIL"
					+ " text not null " + ");";
			// "create table mytable (_ID,NAME, STUID, CLASS, EMAIL);"
			db.execSQL(DATABASE_SQL);
		}

		@Override
		public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
			// TODO Auto-generated method stub
		}
	}

	public void onClick(View v)
	{
		// TODO Auto-generated method stub

		myData helper = new myData(SQLiteDatabaseActivity.this,SQLiteDatabaseActivity.this.getFilesDir()+"/new_data.db");
		SQLiteDatabase database = helper.getWritableDatabase();

		switch (v.getId())
		{
		case R.id.id_databaseButton://添加元素

			ContentValues value1 = new ContentValues();
			value1.put("NAME", inputname.getText().toString());
			value1.put("STUID", inputid.getText().toString());
			value1.put("CLASS", inputclass.getText().toString());
			value1.put("EMAIL", inputemail.getText().toString());

			long i = database.insert("MYSTUDENTDB", null, value1);
			if (i == -1)
			{
				Toast.makeText(this, "添加失败", 0).show();
			} else
			{
				Toast.makeText(this, "添加成功", 0).show();
			}

			database.close();
			inputname.setText("");inputid.setText("");inputclass.setText("");inputemail.setText("");
			break;

		case R.id.id_databaseButtonUpdate://更新元素

			ContentValues value2 = new ContentValues();
			value2.put("NAME", inputname.getText().toString());
			value2.put("STUID", inputid.getText().toString());
			value2.put("CLASS", inputclass.getText().toString());
			value2.put("EMAIL", inputemail.getText().toString());

			String where = "NAME" + " = " + inputname.getText().toString();

			database.update("MYSTUDENTDB", value2, where, null);
			database.close();
			
			break;

		case R.id.id_databaseButtonDelete://删除元素

			String where2 = "NAME" + " = " + inputname.getText().toString();

			int o = database.delete("MYSTUDENTDB", where2, null);

			Toast.makeText(this, "" + o + "条数据受影响", 0).show();
			database.close();
			break;

		case R.id.id_databaseButtonQuery://查询所有元素依次弹窗
			String zsname = "zs";
//			Cursor cursor = database.query("MYSTUDENTDB", null, "CLASS= ? AND NAME=?", new String[]{"1","zs"}, null, null, null);//NAME='zs'
//			Cursor cursor = database.query("MYSTUDENTDB", null, "NAME=?", new String[]{"zs"}, null, null, null);
			Cursor cursor = database.query("MYSTUDENTDB", null, null, null, null, null, null);
			if (cursor.getCount() > 0)
			{
				while (cursor.moveToNext())
				{	
					String id = "名字："+cursor.getString(1) + ";";
					String name = "学号："+cursor.getString(2) + ";";
					String age = "班级："+cursor.getString(3) + ";";
					String address = "邮箱："+cursor.getString(4)+"." ;
					Toast.makeText(this, "查询成功：" + cursor.getString(0).toString()+"_" +id + name + age + address, 0).show();
				}
			} else
			{
				Toast.makeText(this, "" + cursor.getCount() + "", 0).show();
			}
			database.close();
			break;
		case R.id.id_clearall://清空

			inputname.setText("");inputid.setText("");inputclass.setText("");inputemail.setText("");
		
			break;
		default:
			break;
		}
	}
}