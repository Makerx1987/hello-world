/**
 * 
 */
package edu.dhu.cist.c72;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * @author Odie_wx
 * 
 */
public class myData extends SQLiteOpenHelper {

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * android.database.sqlite.SQLiteOpenHelper#onCreate(android.database.sqlite
	 * .SQLiteDatabase)
	 */
	public myData(Context context, String str) {
		super(context, str, null, 1);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		// TODO Auto-generated method stub
		String DATABASE_SQL = "CREATE TABLE " + "MYSTUDENTDB" + " (" + "_ID" + " INTEGER primary key autoincrement, "
				+ "NAME" + " text not null, " + "STUID" + " text not null, " + "CLASS" + " text not null, " + "EMAIL"
				+ " text not null " + ");";
		// "create table mytable (_ID,NAME, STUID, CLASS, EMAIL);"
		db.execSQL(DATABASE_SQL);
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		// TODO Auto-generated method stub
	}

}
