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

		// 获取控件
		read = (Button) findViewById(R.id.read);
		write = (Button) findViewById(R.id.write);
		edit1 = (EditText) findViewById(R.id.edit1);
		edit2 = (EditText) findViewById(R.id.edit2);

		// 为write按钮绑定事件监听器
		write.setOnClickListener(new OnClickListener() {
			public void onClick(View source) {
				// 将edit1中的内容写入文件中
				write(edit1.getText().toString());// 获取输入框内容，写入文件
				edit1.setText("");// 完成写入后，清空输入框
			}
		});

		// 为read按钮绑定事件监听器
		read.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				// 读取指定文件中的内容，并显示出来
				edit2.setText(read());
			}
		});
	}

	private String read()// 用于读取文件的子函数
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
			// 如果手机插入了SD卡，而且应用程序具有访问SD的权限
			if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
				// 获取SD卡对应的存储目录
				File sdCardDir = Environment.getExternalStorageDirectory();
				// 获取指定文件对应的输入流
				FileInputStream fis = new FileInputStream(getFilesDir() + filename);
				Log.i("TEST", sdCardDir.getCanonicalPath() + filename);
				// 将指定输入流包装成BufferedReader
				byte[] buffer = new byte[1024];
				StringBuffer sb = new StringBuffer("");
				// 循环读取文件内容
				int hasread = 0;
				while ((hasread = fis.read(buffer)) > 0) {
					sb.append(new String(buffer), 0, hasread);
				}
				// 关闭资源
				fis.close();
				return sb.toString();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	private void write(String content)// 用于写入文件的子函数
	{
		fn = (EditText) findViewById(R.id.filename);
		filename = "/" + fn.getText().toString() + ".txt";
		try {
			// 如果手机插入了SD卡，而且应用程序具有访问SD的权限
			if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
				File fl = new File(getFilesDir() + filename);
				if (!fl.exists()) {
					fl.createNewFile();
				}

				FileOutputStream fos = new FileOutputStream(fl, true);
				PrintStream ps = new PrintStream(fos);// 输出流包装为打印流
				ps.print(content + ",");// 打印流的内容，名叫 content的string数据
				fos.close();
				ps.close();

				/*
				 * // 获取SD卡的目录 File sdCardDir =
				 * Environment.getExternalStorageDirectory(); File targetFile =
				 * new File(sdCardDir.getCanonicalPath() + filename); // 以指定文件创建
				 * RandomAccessFile对象 RandomAccessFile raf = new
				 * RandomAccessFile(targetFile, "rw"); // 将文件记录指针移动到最后
				 * raf.seek(targetFile.length()); // 输出文件内容
				 * raf.write(content.getBytes()); // 关闭RandomAccessFile
				 * raf.close();
				 */
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}