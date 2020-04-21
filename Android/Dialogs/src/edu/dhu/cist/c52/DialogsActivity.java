package edu.dhu.cist.c52;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class DialogsActivity extends Activity implements OnClickListener {

	private TextView tv1, tv2;
	private Button btn1, btn2, btn3;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		findv();
		bindbutton();
	}

	private void findv() {
		tv1 = (TextView) findViewById(R.id.textViewId1);
		tv2 = (TextView) findViewById(R.id.textViewId2);

		btn1 = (Button) findViewById(R.id.buttonId1);
		btn2 = (Button) findViewById(R.id.buttonId2);
		btn3 = (Button) findViewById(R.id.buttonId3);
	}

	private void bindbutton() {
		btn1.setOnClickListener(this);
		btn2.setOnClickListener(this);
		btn3.setOnClickListener(this);
	}

	public void onClick(View v) {// ��Ӧ implements onclicklistener�ĵ���¼�����
		// TODO Auto-generated method stub
		int id = v.getId();
		AlertDialog.Builder builder = new AlertDialog.Builder(DialogsActivity.this);
		builder.setIcon(R.drawable.ic_launcher);

		switch (id) {
		case R.id.buttonId1:
			builder.setTitle("ȷ��ȡ���Ի���");
			builder.setMessage("���ȷ����ȡ����������Ӧ����ʾ����");
			builder.setPositiveButton("ȷ��", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface arg0, int arg1) {
					tv1.setText("�򵥶Ի���:�û������\"ȷ��\"��ť!");
				}
			});
			builder.setNegativeButton("ȡ��", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface arg0, int arg1) {
					tv1.setText("�򵥶Ի���:�û������\"ȡ��\"��ť!");
				}
			});
			// builder.setCancelable(false);
			builder.create().show();
			break;

		case R.id.buttonId2:
			final String[] colors = { "��ɫ", "��ɫ", "��ɫ", "��ɫ" };
			builder.setTitle("�б�Ի���");
			//
			builder.setItems(colors, new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface arg0, int index) {
					tv2.setText("��ѡ�����ɫ��:" + colors[index]);
					switch (index) {
					case 0:
						// tv3.setBackgroundColor(Color.RED);
						tv2.setBackgroundColor(Color.RED);
						break;
					case 1:
						tv2.setBackgroundColor(Color.BLUE);
						break;
					case 2:
						tv2.setBackgroundColor(Color.GREEN);
						break;
					case 3:
						tv2.setBackgroundColor(Color.YELLOW);
						break;
					}
				}
			});
			// builder.setMessage("hi");
			builder.setPositiveButton("ȷ��", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface arg0, int arg1) {
					tv1.setText("�򵥶Ի���:�û������\"ȷ��\"��ť!");
				}
			});
			builder.setNegativeButton("ȡ��", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface arg0, int arg1) {
					tv1.setText("�򵥶Ի���:�û������\"ȡ��\"��ť!");
				}
			});

			builder.create();
			builder.show();
			break;

		case R.id.buttonId3:
			final String[] games = { "dota", "war3", "sc2", "lol", "cs", "cf" };
			final boolean[] initChoose = { false, false, true, false, false, false };
			builder.setTitle("��ѡ��ť�Ի���");
			builder.setMultiChoiceItems(games, initChoose, new DialogInterface.OnMultiChoiceClickListener() {
				public void onClick(DialogInterface dialog, int which, boolean isChecked) {

				}
			});
			builder.setPositiveButton("ȷ��", new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int which) {
					StringBuffer s = new StringBuffer("");
					for (int i = 0; i < initChoose.length; i++) {
						if (initChoose[i]) {
							s.append(games[i] + " ");
						}
					}

					Toast.makeText(DialogsActivity.this, "��ϲ������Ϸ��" + s, Toast.LENGTH_SHORT).show();
				}
			});
			builder.setNegativeButton("ȡ��", new DialogInterface.OnClickListener() {

				public void onClick(DialogInterface dialog, int which) {
					dialog.dismiss();
					// TODO Auto-generated method stub

				}
			});
			builder.create().show();
			break;

		}

	}
}
