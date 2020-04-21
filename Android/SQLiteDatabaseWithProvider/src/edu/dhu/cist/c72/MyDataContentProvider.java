/**
 * 
 */
package edu.dhu.cist.c72;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.text.TextUtils;

/**
 * @author Odie_wx
 *
 */
public class MyDataContentProvider extends ContentProvider {

	/* (non-Javadoc)
	 * @see android.content.ContentProvider#delete(android.net.Uri, java.lang.String, java.lang.String[])
	 */
	
	private myData dataio;
	private final static int STUDENTS = 1;
	private final static int STUDENT = 2;
	private final static String AUTHORITY = "edu.dhu.cist.c72.MyDataContentProvider";
	private static final UriMatcher sMatcher = new UriMatcher(UriMatcher.NO_MATCH);
	static
	{
		sMatcher.addURI(AUTHORITY, "MYSTUDENTDB", STUDENTS);
		sMatcher.addURI(AUTHORITY, "MYSTUDENTDB/#", STUDENT);
	}
	
	@Override
	public int delete(Uri uri, String selection, String[] selectionArgs) {
		// TODO Auto-generated method stub
		SQLiteDatabase db = dataio.getWritableDatabase();
		int count = 0;
		switch (sMatcher.match(uri))
		{
		//uri="content://XX/person"
		case STUDENTS:
			count = db.delete("MYSTUDENTDB", selection, selectionArgs);
			break;
		//uri="XX/person/#"
		case STUDENT:
			//selection = " NMAE=? and CLASS=? and _ID=?"   ; selectionargs={"zs","2","1"}
			long sid = ContentUris.parseId(uri);
			String where = TextUtils.isEmpty(selection) ? "_ID=?" : selection + " and _ID=?";
			String[] params = new String[] { String.valueOf(sid) };
			if (!TextUtils.isEmpty(selection) && selectionArgs != null)
			{
				params = new String[selectionArgs.length + 1];
				for (int i = 0; i < selectionArgs.length; i++)
				{
					params[i] = selectionArgs[i];
				}
				params[selectionArgs.length] = String.valueOf(sid);
			}
			count = db.delete("MYSTUDENTDB", where, params);
			break;
		default:
			throw new IllegalArgumentException("Unknow Uri:" + uri);
		}
		return count;
	}

	/* (non-Javadoc)
	 * @see android.content.ContentProvider#getType(android.net.Uri)
	 */
	@Override
	public String getType(Uri uri) {
		// TODO Auto-generated method stub
		switch (sMatcher.match(uri))
		{
		case STUDENTS:
			return "vnd.android.cursor.dir/personprovider.person";
		case STUDENT:
			return "vnd.android.cursor.item/personprovider.person";
		default:
			throw new IllegalArgumentException("Unknow Uri:" + uri);
		}
	}

	/* (non-Javadoc)
	 * @see android.content.ContentProvider#insert(android.net.Uri, android.content.ContentValues)
	 */
	@Override
	public Uri insert(Uri uri, ContentValues values) {
		// TODO Auto-generated method stub
		SQLiteDatabase db = dataio.getWritableDatabase();
		long pid = 0;
		switch (sMatcher.match(uri))
		{
		case STUDENTS:
			pid = db.insert("MYSTUDENTDB", "name", values);
			return ContentUris.withAppendedId(uri, pid);
		case STUDENT://content://pkg/xxxx/3
			pid = db.insert("MYSTUDENTDB", "name", values);
			String path = uri.toString();
			return Uri.parse(path.substring(0, path.lastIndexOf('/')+1) + pid);
		default:
			throw new IllegalArgumentException("Unknow Uri:" + uri);
		}
	}

	/* (non-Javadoc)
	 * @see android.content.ContentProvider#onCreate()
	 */
	@Override
	public boolean onCreate() {
		// TODO Auto-generated method stub
		dataio = new myData(this.getContext(),this.getContext().getFilesDir()+"/test.db");
		return true;
		
	}

	/* (non-Javadoc)
	 * @see android.content.ContentProvider#query(android.net.Uri, java.lang.String[], java.lang.String, java.lang.String[], java.lang.String)
	 */
	@Override
	public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sortOrder) {
		// TODO Auto-generated method stub
		SQLiteDatabase db = dataio.getReadableDatabase();
		switch (sMatcher.match(uri))
		{
		case STUDENTS:
			return db.query("MYSTUDENTDB", projection, selection, selectionArgs, null, null, sortOrder);
		case STUDENT:
			long pid = ContentUris.parseId(uri);
			String where = TextUtils.isEmpty(selection) ? "_ID=?" : selection + " and _ID=?";
			String[] params = new String[]
			{ String.valueOf(pid) };
			if (!TextUtils.isEmpty(selection) && selectionArgs != null)
			{
				params = new String[selectionArgs.length + 1];
				for (int i = 0; i < selectionArgs.length; i++)
				{
					params[i] = selectionArgs[i];
				}
			}
			return db.query("MYSTUDENTDB", projection, where, params, null, null, sortOrder);
		default:
			throw new IllegalArgumentException("Unknow Uri:" + uri);
		}
	}

	/* (non-Javadoc)
	 * @see android.content.ContentProvider#update(android.net.Uri, android.content.ContentValues, java.lang.String, java.lang.String[])
	 */
	@Override
	public int update(Uri uri, ContentValues values, String selection, String[] selectionArgs) {
		// TODO Auto-generated method stub
		SQLiteDatabase db = dataio.getWritableDatabase();
		int count = 0;
		switch (sMatcher.match(uri))
		{
		case STUDENTS:
			count = db.update("MYSTUDENTDB", values, selection, selectionArgs);
			break;
		case STUDENT:
			long sid = ContentUris.parseId(uri);
			String where = TextUtils.isEmpty(selection) ? "_ID=?" : selection + " and _ID=?";
			String[] params = new String[] { String.valueOf(sid) };
			if (!TextUtils.isEmpty(selection) && selectionArgs != null)
			{
				params = new String[selectionArgs.length + 1];
				for (int i = 0; i < selectionArgs.length; i++)
				{
					params[i] = selectionArgs[i];
				}
				params[selectionArgs.length + 1] = String.valueOf(sid);
			}
			count = db.update("MYSTUDENTDB", values, where, params);
			break;
		default:
			throw new IllegalArgumentException("Unknow Uri:" + uri);
		}
		return count;
	}

}
