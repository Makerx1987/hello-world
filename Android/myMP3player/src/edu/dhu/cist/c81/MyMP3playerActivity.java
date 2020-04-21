package edu.dhu.cist.c81;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;

import android.app.Activity;
import android.graphics.Color;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebSettings.LayoutAlgorithm;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.TextView;

public class MyMP3playerActivity extends Activity implements OnClickListener// 监听全局点击
{
	private Button mNext, mBefore, mStart, mStop;
	private TextView mTextView1;
	private WebView mWebView;// 声明控件变量

	private MediaPlayer myPlayer1 = new MediaPlayer();// 声明实例化播放器对象
	private ArrayList<String> files = new ArrayList<String>();// 声明实例化动态数组用以存放播放列表
	private int now = 0;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		findv();// 查询控件子函数
		bindbutton();// 绑定点击事件子函数

		files = getAllMusicPath();// 获取播放列表
		 if (!files.isEmpty())
		 {
		 now = readNow();
		 Log.i("TEST", now + "now is the read");
		 // else now=0;
		 }

		/* 当音乐播完会执行的Listener */
		myPlayer1.setOnCompletionListener(new OnCompletionListener()// 监听音乐播放结束，执行操作
				{
					// @Override
					public void onCompletion(MediaPlayer arg0)
					{
						mTextView1.setText("播放结束");
						mStart.setText("播放");
						// mImageView1.setImageResource(R.drawable.start);
						startjpg();
					}
				});

	}

	private void bindbutton()
	{
		// TODO Auto-generated method stub
		mStart.setOnClickListener(this);
		mStop.setOnClickListener(this);
		mBefore.setOnClickListener(this);
		mNext.setOnClickListener(this);
	}

	private void findv()
	{
		// TODO Auto-generated method stub
		mStart = (Button) findViewById(R.id.myButton2);
		mStop = (Button) findViewById(R.id.myButton5);
		mNext = (Button) findViewById(R.id.myButton4);
		mBefore = (Button) findViewById(R.id.myButton1);
		mWebView = (WebView) findViewById(R.id.webView1);
		mTextView1 = (TextView) findViewById(R.id.myTextView1);
		startjpg();
	}

	private ArrayList<String> getAllMusicPath()
	{
		files = new ArrayList<String>();
		String path = null;
		if (Environment.getExternalStorageState().equals(
				android.os.Environment.MEDIA_MOUNTED))// 判断sd卡是否存在
		{
			path = Environment.getExternalStorageDirectory().getPath()
					+ "/Music";// 确定是播放music文件夹下的mp3文件
		}
		File file = new File(path);
		File[] tempList = file.listFiles();// 列出目标文件夹下所有文件和目录

		for (int i = 0; i < tempList.length; i++)
		{
			if (tempList[i].isDirectory())// 如果是目录则舍弃
			{
				// System.out.println("文件夹：" + tempList[i]);
			}
			if (tempList[i].isFile())// 如果是文件则判断是否是mp3，若是则保留计入list中
			{
				if (tempList[i].toString().contains(".mp3")
						| tempList[i].toString().contains(".MP3")
						| tempList[i].toString().contains(".Mp3"))
				{
					files.add(tempList[i].toString());
					Log.i("FORTEST", tempList[i].toString());
				}
			}
		}
		return files;// 返回播放列表
	}

	public void startgif() // 用以在webview中播放gif的函数, 仅供参考
	{
		String gifFilePath = "file:///android_asset/playing.gif";// 首先将一张gif格式的动图放置在assets中
		mWebView.getSettings()
				.setLayoutAlgorithm(LayoutAlgorithm.SINGLE_COLUMN);
		String data = "<HTML><Div align=\"center\" margin=\"0px\"><IMG src=\""
				+ gifFilePath + "\" margin=\"0px\"/></Div>";// 设置图片位于webview的中间位置
		mWebView.loadDataWithBaseURL(gifFilePath, data, "text/html", "utf-8",
				null);

		mWebView.setBackgroundColor(Color.BLACK);
		// mWebView.getSettings().setSupportZoom(true);
		// mWebView.getSettings().setLayoutAlgorithm(LayoutAlgorithm.NARROW_COLUMNS);//适应内容大小
		// mWebView.getSettings().setLoadWithOverviewMode(true);
	}

	public void startjpg() // 用以在webview中展示图片的方法, 仅供参考
	{
		String gifFilePath = "file:///android_asset/start.jpg";// 首先将一张gif格式的动图放置在assets中
		mWebView.getSettings()
				.setLayoutAlgorithm(LayoutAlgorithm.SINGLE_COLUMN);
		String data = "<HTML><Div align=\"center\" margin=\"0px\"><IMG src=\""
				+ gifFilePath + "\" margin=\"0px\"/></Div>";// 设置图片位于webview的中间位置
		mWebView.loadDataWithBaseURL(gifFilePath, data, "text/html", "utf-8",
				null);

		mWebView.setBackgroundColor(Color.BLACK);
		// mWebView.getSettings().setSupportZoom(true);
		// mWebView.getSettings().setLayoutAlgorithm(LayoutAlgorithm.NARROW_COLUMNS);//适应内容大小
		// mWebView.getSettings().setLoadWithOverviewMode(true);
	}

	@Override
	protected void onPause()
	{
		// TODO Auto-generated method stub
		super.onPause();
		saveNow();// 记住当前正播放的曲目
	}

	@Override
	protected void onDestroy()
	{
		// TODO Auto-generated method stub
		super.onDestroy();
		myPlayer1.stop();// 关闭、释放播放器
		myPlayer1.release();
	}

	private void saveNow()// 当前曲目记录如txt文件
	{
		String string = null;
		string = this.getFilesDir() + "/MP3Player_now.txt";
		Log.i("TEST", string);
		FileOutputStream out;
		try
		{
			out = new FileOutputStream(string);
			PrintStream p = new PrintStream(out);
			p.print(now + "");
		} catch (FileNotFoundException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	private int readNow()// 读取上次正播放的mp3曲目
	{
		StringBuffer sb = new StringBuffer("");
		int now = 0;
		String string = this.getFilesDir() + "/MP3Player_now.txt";
		File file = new File(string);
		if (!file.exists())
		{
			try
			{
				file.createNewFile();
			} catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			now = 0;
			Log.i("TEST", "filenotexit");
		} else
		{
			try
			{
				FileInputStream in = new FileInputStream(string);
				byte buffer[] = new byte[1024];
				int hasread = 0;
				while ((hasread = in.read(buffer)) != -1)
				{
					sb.append(new String(buffer), 0, hasread);
				}
				in.close();

			} catch (FileNotFoundException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e)
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			now = Integer.parseInt(sb.toString());
			//string转换成int的
			// System.out.println(sb.toString());
			// System.out.println(sb.toString().length()+"");
			// System.out.println(Integer.parseInt(sb.toString())+"");
		}
		return now;
	}

	public void onClick(View arg0)
	{// 点击响应合集
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		if (!files.isEmpty())
		{
			switch (arg0.getId())
			{
			case R.id.myButton1: // before
				try
				{
					if (now == 0)
					{
						// myPlayer1.seekTo(0);
						// myPlayer1.start();
					} else
					{
						now = now - 1;
						Log.i("TEST", now + "");
						myPlayer1.reset();
						myPlayer1.setDataSource(files.get(now));
						myPlayer1.prepare();
						/* 启动MediaPlayer */
						myPlayer1.start();
						
						mStart.setText("暂停");
						mTextView1.setText(files.get(now));
						startgif();
					}

				} catch (IllegalStateException e)
				{
					// TODO Auto-generated catch block
					mTextView1.setText(e.toString());
					e.printStackTrace();
					myPlayer1.reset();
				} catch (IOException e)
				{
					// TODO Auto-generated catch block
					mTextView1.setText(e.toString());
					e.printStackTrace();
					myPlayer1.reset();
				}
				break;
			case R.id.myButton2: // start
				if (myPlayer1 != null)
				{

					if (myPlayer1.isPlaying() == true)
					{
						Log.i("TEST", now + "");
						/* 设定 MediaPlayer暂停播放 */
						myPlayer1.pause();
						// bIsPaused = true;
						mStart.setText("播放");
						mTextView1.setText("已暂停");
						startjpg();
					} else if (myPlayer1.isPlaying() == false)
					{
						/* 设定 MediaPlayer播放 */
						Log.i("TEST", now + "");
						try
						{
							myPlayer1.reset();
							myPlayer1.setDataSource(files.get(now));
							myPlayer1.prepare();

							myPlayer1.start();
							// bIsPaused = false;
							mStart.setText("暂停");
							mTextView1.setText(files.get(now));
							startgif();
						} catch (IllegalStateException e)
						{
							// TODO Auto-generated catch block
							e.printStackTrace();
						} catch (IOException e)
						{
							// TODO Auto-generated catch block
							e.printStackTrace();
						}

					}

				}
				break;
			case R.id.myButton4: // next
				try
				{
					if (now == (files.size() - 1))
					{
						// myPlayer1.seekTo(0);
						// myPlayer1.start();
					} else
					{
						now = now + 1;
						Log.i("TEST", now + "");
						myPlayer1.reset();
						myPlayer1.setDataSource(files.get(now));
						myPlayer1.prepare();
						/* 启动MediaPlayer */
						myPlayer1.start();
						mStart.setText("暂停");
						mTextView1.setText(files.get(now));
						startgif();
					}

				} catch (IllegalStateException e)
				{
					// TODO Auto-generated catch block
					mTextView1.setText(e.toString());
					e.printStackTrace();
					myPlayer1.reset();
				} catch (IOException e)
				{
					// TODO Auto-generated catch block
					mTextView1.setText(e.toString());
					e.printStackTrace();
					myPlayer1.reset();
				}
				break;
			case R.id.myButton5:// stop
				// TODO Auto-generated method stub

				/* 将 MediaPlayer重设 */

				Log.i("TEST", now + "");
				myPlayer1.reset();
				mStart.setText("播放");
				mTextView1.setText("当前未播放");
				startjpg();
				break;
			default:
				break;
			}
		}

	}
}