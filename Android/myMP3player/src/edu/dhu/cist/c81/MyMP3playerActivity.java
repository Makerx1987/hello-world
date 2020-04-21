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

public class MyMP3playerActivity extends Activity implements OnClickListener// ����ȫ�ֵ��
{
	private Button mNext, mBefore, mStart, mStop;
	private TextView mTextView1;
	private WebView mWebView;// �����ؼ�����

	private MediaPlayer myPlayer1 = new MediaPlayer();// ����ʵ��������������
	private ArrayList<String> files = new ArrayList<String>();// ����ʵ������̬�������Դ�Ų����б�
	private int now = 0;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		findv();// ��ѯ�ؼ��Ӻ���
		bindbutton();// �󶨵���¼��Ӻ���

		files = getAllMusicPath();// ��ȡ�����б�
		 if (!files.isEmpty())
		 {
		 now = readNow();
		 Log.i("TEST", now + "now is the read");
		 // else now=0;
		 }

		/* �����ֲ����ִ�е�Listener */
		myPlayer1.setOnCompletionListener(new OnCompletionListener()// �������ֲ��Ž�����ִ�в���
				{
					// @Override
					public void onCompletion(MediaPlayer arg0)
					{
						mTextView1.setText("���Ž���");
						mStart.setText("����");
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
				android.os.Environment.MEDIA_MOUNTED))// �ж�sd���Ƿ����
		{
			path = Environment.getExternalStorageDirectory().getPath()
					+ "/Music";// ȷ���ǲ���music�ļ����µ�mp3�ļ�
		}
		File file = new File(path);
		File[] tempList = file.listFiles();// �г�Ŀ���ļ����������ļ���Ŀ¼

		for (int i = 0; i < tempList.length; i++)
		{
			if (tempList[i].isDirectory())// �����Ŀ¼������
			{
				// System.out.println("�ļ��У�" + tempList[i]);
			}
			if (tempList[i].isFile())// ������ļ����ж��Ƿ���mp3��������������list��
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
		return files;// ���ز����б�
	}

	public void startgif() // ������webview�в���gif�ĺ���, �����ο�
	{
		String gifFilePath = "file:///android_asset/playing.gif";// ���Ƚ�һ��gif��ʽ�Ķ�ͼ������assets��
		mWebView.getSettings()
				.setLayoutAlgorithm(LayoutAlgorithm.SINGLE_COLUMN);
		String data = "<HTML><Div align=\"center\" margin=\"0px\"><IMG src=\""
				+ gifFilePath + "\" margin=\"0px\"/></Div>";// ����ͼƬλ��webview���м�λ��
		mWebView.loadDataWithBaseURL(gifFilePath, data, "text/html", "utf-8",
				null);

		mWebView.setBackgroundColor(Color.BLACK);
		// mWebView.getSettings().setSupportZoom(true);
		// mWebView.getSettings().setLayoutAlgorithm(LayoutAlgorithm.NARROW_COLUMNS);//��Ӧ���ݴ�С
		// mWebView.getSettings().setLoadWithOverviewMode(true);
	}

	public void startjpg() // ������webview��չʾͼƬ�ķ���, �����ο�
	{
		String gifFilePath = "file:///android_asset/start.jpg";// ���Ƚ�һ��gif��ʽ�Ķ�ͼ������assets��
		mWebView.getSettings()
				.setLayoutAlgorithm(LayoutAlgorithm.SINGLE_COLUMN);
		String data = "<HTML><Div align=\"center\" margin=\"0px\"><IMG src=\""
				+ gifFilePath + "\" margin=\"0px\"/></Div>";// ����ͼƬλ��webview���м�λ��
		mWebView.loadDataWithBaseURL(gifFilePath, data, "text/html", "utf-8",
				null);

		mWebView.setBackgroundColor(Color.BLACK);
		// mWebView.getSettings().setSupportZoom(true);
		// mWebView.getSettings().setLayoutAlgorithm(LayoutAlgorithm.NARROW_COLUMNS);//��Ӧ���ݴ�С
		// mWebView.getSettings().setLoadWithOverviewMode(true);
	}

	@Override
	protected void onPause()
	{
		// TODO Auto-generated method stub
		super.onPause();
		saveNow();// ��ס��ǰ�����ŵ���Ŀ
	}

	@Override
	protected void onDestroy()
	{
		// TODO Auto-generated method stub
		super.onDestroy();
		myPlayer1.stop();// �رա��ͷŲ�����
		myPlayer1.release();
	}

	private void saveNow()// ��ǰ��Ŀ��¼��txt�ļ�
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

	private int readNow()// ��ȡ�ϴ������ŵ�mp3��Ŀ
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
			//stringת����int��
			// System.out.println(sb.toString());
			// System.out.println(sb.toString().length()+"");
			// System.out.println(Integer.parseInt(sb.toString())+"");
		}
		return now;
	}

	public void onClick(View arg0)
	{// �����Ӧ�ϼ�
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
						/* ����MediaPlayer */
						myPlayer1.start();
						
						mStart.setText("��ͣ");
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
						/* �趨 MediaPlayer��ͣ���� */
						myPlayer1.pause();
						// bIsPaused = true;
						mStart.setText("����");
						mTextView1.setText("����ͣ");
						startjpg();
					} else if (myPlayer1.isPlaying() == false)
					{
						/* �趨 MediaPlayer���� */
						Log.i("TEST", now + "");
						try
						{
							myPlayer1.reset();
							myPlayer1.setDataSource(files.get(now));
							myPlayer1.prepare();

							myPlayer1.start();
							// bIsPaused = false;
							mStart.setText("��ͣ");
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
						/* ����MediaPlayer */
						myPlayer1.start();
						mStart.setText("��ͣ");
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

				/* �� MediaPlayer���� */

				Log.i("TEST", now + "");
				myPlayer1.reset();
				mStart.setText("����");
				mTextView1.setText("��ǰδ����");
				startjpg();
				break;
			default:
				break;
			}
		}

	}
}