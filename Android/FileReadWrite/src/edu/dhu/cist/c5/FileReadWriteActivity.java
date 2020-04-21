package edu.dhu.cist.c5;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.PrintStream;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class FileReadWriteActivity extends Activity {
	public static StringBuffer ss = new StringBuffer("");
	public static String filename;

	private Button read, write;
	private EditText fn, edit1, edit2;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		// ��ȡ�ؼ�
		read = (Button) findViewById(R.id.read);
		write = (Button) findViewById(R.id.write);
		edit1 = (EditText) findViewById(R.id.edit1);
		edit2 = (EditText) findViewById(R.id.edit2);

		// Ϊwrite��ť���¼�������
		write.setOnClickListener(new OnClickListener() {
			public void onClick(View source) {
				// ��edit1�е�����д���ļ���
				write(edit1.getText().toString());// ��ȡ��������ݣ�д���ļ�
				edit1.setText("");// ���д�����������
			}
		});

		// Ϊread��ť���¼�������
		read.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				// ��ȡָ���ļ��е����ݣ�����ʾ����
				edit2.setText(read());
			}
		});
	}

	private String read()// ���ڶ�ȡ�ļ����Ӻ���
	{
		fn = (EditText) findViewById(R.id.filename);
		filename = "/" + fn.getText().toString() + ".txt";
		// File fle = Environment.getDataDirectory();
		// File f = getDir("1.txt", MODE_APPEND);
		// String s = fle.getName().toString();
		// Log.i("TEST", s);

		// File f1 = this.getFilesDir();
		// String[] a = f1.list();
		// Log.i("TEST", a[1]);
		try {
			// ����ֻ�������SD��������Ӧ�ó�����з���SD��Ȩ��
			if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
				// ��ȡSD����Ӧ�Ĵ洢Ŀ¼
				File sdCardDir = Environment.getExternalStorageDirectory();
				// ��ȡָ���ļ���Ӧ��������
				FileInputStream fis = new FileInputStream(getFilesDir() + filename);
				Log.i("TEST", sdCardDir.getCanonicalPath() + filename);
				// ��ָ����������װ��BufferedReader
				byte[] buffer = new byte[1024];
				StringBuffer sb = new StringBuffer("");
				// ѭ����ȡ�ļ�����
				int hasread = 0;
				while ((hasread = fis.read(buffer)) > 0) {
					sb.append(new String(buffer), 0, hasread);
				}
				// �ر���Դ
				fis.close();
				return sb.toString();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	private void write(String content)// ����д���ļ����Ӻ���
	{
		fn = (EditText) findViewById(R.id.filename);
		filename = "/" + fn.getText().toString() + ".txt";
		try {
			// ����ֻ�������SD��������Ӧ�ó�����з���SD��Ȩ��
			if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
				File fl = new File(getFilesDir() + filename);
				if (!fl.exists()) {
					fl.createNewFile();
				}

				FileOutputStream fos = new FileOutputStream(fl, true);
				PrintStream ps = new PrintStream(fos);// �������װΪ��ӡ��
				ps.print(content + ",");// ��ӡ�������ݣ����� content��string����
				fos.close();
				ps.close();

				/*
				 * // ��ȡSD����Ŀ¼ File sdCardDir =
				 * Environment.getExternalStorageDirectory(); File targetFile =
				 * new File(sdCardDir.getCanonicalPath() + filename); // ��ָ���ļ�����
				 * RandomAccessFile���� RandomAccessFile raf = new
				 * RandomAccessFile(targetFile, "rw"); // ���ļ���¼ָ���ƶ������
				 * raf.seek(targetFile.length()); // ����ļ�����
				 * raf.write(content.getBytes()); // �ر�RandomAccessFile
				 * raf.close();
				 */
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}