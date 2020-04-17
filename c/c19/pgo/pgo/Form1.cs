using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;


namespace pgo
{
	public partial class Form1 : Form
	{
		private int columns = 11;
		private int rows = 11;
		public int score = 0;
		int timeuse = 0;
		int timepoint = -1;
		int during = 0;
		int[,] arr;
		public string csvfile = "";
		StreamReader sr;
		string[] headrow = null;
		int x;
		int y;
		int z;
		float xu = 5;
		float yu = 5;
		float dx = 0;
		float dy = 0;
		Point pos;
		bool c21 = true;
		bool aicontrol = false;
		int ai = 0;
		bool cfq = false;
		bool stop = false;
		int[] grade = { 388, 317, 258, 193, 159, 141, 87, 73, 45, 51, 49, 41, 22, 22, 21, 11, 9, 4, 4, 7 };
		int[] appear = { 4, 1, 5, 1, 4, 3, 3, 2, 9, 6, 11, 21, 16, 20, 17, 27, 25, 39, 44, 45, 66, 56, 69, 83, 85, 63, 95, 86, 76, 1, 80, 77, 75, 75, 71, 52, 54, 57, 45, 39, 49, 45, 26, 31, 24, 18, 16, 12, 13, 7, 4, 5, 3, 6, 4, 2, 2, 1, 1 };
		//StreamReader sr2;
		public Form1()
		{
			InitializeComponent();
			arr = new int[columns, rows];
			pos = new Point(5 * 40, 5 * 40);
			//Console.WriteLine(Environment.CurrentDirectory + "\\" + DateTime.Now.ToString("MM-dd-hh-mm-ss") + ".csv");
		}

		private void pictureBox1_Paint(object sender, PaintEventArgs e)
		{
			Graphics g = e.Graphics;
			for (int i = 0; i <= 10; i++)
			{
				g.DrawLine(Pens.LightGreen, 40 * i + 5, 0 + 5, 40 * i + 5, 400 + 5);
				g.DrawLine(Pens.LightGreen, 0 + 5, 40 * i + 5, 400 + 5, 40 * i + 5);
			}
			//for (int i = 0; i < columns; i++)
			//	for (int j = 0; j < rows; j++)
			//	{
			//		if (arr[i, j] == 1)
			//		{
			g.FillRectangle(Brushes.LightBlue, 40 * xu - 4 + 5, 40 * yu - 4 + 5, 8, 8);

			//	}
			//}
			for (int i = 0; i < columns; i++)
				for (int j = 0; j < rows; j++)
				{
					if (arr[i, j] == 2)
					{
						g.FillRectangle(Brushes.Yellow, 40 * i - 4 + 5, 40 * j - 4 + 5, 8, 8);
						g.DrawString(z.ToString(), Font, Brushes.Black, 40 * i + 5, 40 * j + 5);
					}
				}

		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			if (timeuse >= 50000) timer1.Stop();

			if (during == 0)
			{

				if (x >= 0 && y >= 0)
				{
					arr[x, y] = 0;
					stop = true;
				}

				if (checkBox1.Checked)
				{
					string next = sr.ReadLine();
					if (next == null)
					{
						save();
						Application.Exit();
						return;
					}
					headrow = next.Split(',');

					x = int.Parse(headrow[0]) - 1;
					y = int.Parse(headrow[1]) - 1;
					z = int.Parse(headrow[2]);
					timepoint = int.Parse(headrow[3]);
					during = 15;
				}
				else
					scq();
			}
			if (timeuse == timepoint)
			{
				arr[x, y] = 2;
				cfq = true;
			}
			if (timeuse >= timepoint && Math.Abs(xu - x) < 0.1 && Math.Abs(yu - y) < 0.1)
			{
				arr[x, y] = 0;
				score += z;
				label2.Text = score.ToString();
				x = y = -1;
				cfq = true;
			}

			if (aicontrol && timeuse >= timepoint) aia(ai);
//			if (!aicontrol && checkBox3.Checked) ppt();
			//arr[(int)xu, (int)yu] = 0;
			d();

			if (ai == 3 && timeuse < timepoint)
				dx = dy = 0;
			if (ai == 3 && stop)
			{
				textBox1.Text += xu + "," + yu + "," + timeuse + Environment.NewLine;
				stop = false;
			}
			float tx = xu + dx;
			float ty = yu + dy;
			//Console.Write(tx + ",");
			//Console.Write(c21 + ",");
			//Console.WriteLine(ty);

			if (c21)
			{
				yu = ty;
				if (Math.Abs(ty - Math.Round(ty)) < 0.1 && Math.Abs(Math.Round(pos.Y / 40f) - Math.Round(ty)) < 0.1)
				{
					ty = (float)Math.Round(ty);
					c21 = false;
				}
			}
			else
			{
				xu = tx;
				if (Math.Abs(tx - Math.Round(tx)) < 0.1 && Math.Abs(Math.Round(pos.X / 40f) - Math.Round(tx)) < 0.1)
				{
					tx = (float)Math.Round(tx);
					c21 = true;
				}
			}

			//arr[(int)xu, (int)yu] = 1;

			if (timeuse >= timepoint && during > 0)
			{
				during--;
			}
			pictureBox1.Refresh();
			timeuse++;
			label3.Text = timeuse.ToString();
			label4.Text = during.ToString();
		}

		private void ppt()
		{
			throw new NotImplementedException();
		}

		private void scq()
		{
			Random rd;
			byte[] buffer = Guid.NewGuid().ToByteArray();//生成字节数组
			int iRoot = BitConverter.ToInt32(buffer, 0);//利用BitConvert方法把字节数组转换为整数
			rd = new Random(iRoot);//以这个生成的整数为种子

			x = rd.Next(0, 10);
			buffer = Guid.NewGuid().ToByteArray();//生成字节数组
			iRoot = BitConverter.ToInt32(buffer, 0);//利用BitConvert方法把字节数组转换为整数
			rd = new Random(iRoot);//以这个生成的整数为种子
			y = rd.Next(0, 10);

			z = cj(grade);
			timepoint += cj(appear);

			Console.Write(x + ",");
			Console.Write(y + ",");
			Console.Write(z + ",");
			Console.WriteLine(timepoint);

			//Console.Read();
			during = 15;
		}

		private int cj(int[] grade)
		{
			Random rd;
			byte[] buffer = Guid.NewGuid().ToByteArray();//生成字节数组
			int iRoot = BitConverter.ToInt32(buffer, 0);//利用BitConvert方法把字节数组转换为整数
			rd = new Random(iRoot);//以这个生成的整数为种子
			int amt = 0;
			for (int i = 0; i < grade.Length; i++)
			{
				amt += grade[i];                                   //获取总数
			}
			for (int i = 0; i < grade.Length; i++)
			{
				
				int rdint = rd.Next(0, amt);       //获取 0-总数 之间的一个随随机整数
				if (rdint < grade[i])
				{
					return i + 1;                                    //如果在当前的概率范围内,得到的就是当前概率
				}
				else
				{
					amt -= grade[i];                              //否则减去当前的概率范围,进入下一轮循环
				}
				buffer = Guid.NewGuid().ToByteArray();//生成字节数组
				iRoot = BitConverter.ToInt32(buffer, 0);//利用BitConvert方法把字节数组转换为整数
				rd = new Random(iRoot);//以这个生成的整数为种子
			}
			return 0;
		}

		private void button1_Click(object sender, EventArgs e)
		{
			timer1.Start();
			button1.Enabled = !button1.Enabled;
			button2.Enabled = !button2.Enabled;
		}

		private void button2_Click(object sender, EventArgs e)
		{
			timer1.Stop();
			button2.Enabled = !button2.Enabled;
			button1.Enabled = !button1.Enabled;
		}

		private void button3_Click(object sender, EventArgs e)
		{
			if (checkBox1.Checked)
			{
				OpenFileDialog dialog = new OpenFileDialog();
				dialog.Multiselect = true;//该值确定是否可以选择多个文件
				dialog.Title = "请选择文件夹";
				dialog.Filter = "csv文件|*.csv";
				if (dialog.ShowDialog() == DialogResult.OK)
				{
					csvfile = dialog.FileName;
					Console.WriteLine(csvfile);
					sr = new StreamReader(csvfile);
					button1.Enabled = true;
					button3.Enabled = false;
					checkBox1.Enabled = false;
				}

			}
			else
			{
				arr = new int[columns, rows];
				button1.Enabled = true;
				button3.Enabled = false;
				checkBox1.Enabled = false;
			}

			timer1.Stop();
			timeuse = 0;
			textBox1.Text = "";
			score = 0;
			during = 0;

		}
		private void cleanarr()
		{
			arr = new int[rows, columns];
		}
		private void d()
		{
			if (Math.Round(pos.X / 40f) - xu > 0.1) dx = 0.167f;
			else if (Math.Abs(Math.Round(pos.X / 40f) - xu) <= 0.1) dx = 0;
			else dx = -0.167f;

			if (Math.Round(pos.Y / 40f) - yu > 0.1) dy = 0.167f;
			else if (Math.Abs(Math.Round(pos.Y / 40f) - yu) <= 0.1) dy = 0;
			else dy = -0.167f;

		}

		private void trackBar1_Scroll(object sender, EventArgs e)
		{
			if (trackBar1.Value > 0)
				timer1.Interval = trackBar1.Value * trackBar1.Value * 100;
			else
				timer1.Interval = 10;
		}

		private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
		{
			if (aicontrol == false)
			{
				pos = e.Location;
				if (pos.X > 400) pos.X = 400;
				if (pos.Y > 400) pos.Y = 400;
				d();
				textBox1.Text += Math.Round(pos.X / 40f) + "," + Math.Round(pos.Y / 40f) + "," + timeuse + Environment.NewLine;
			}
		}
		private void aia(int ai = 1)
		{
			if (ai == 1)
			{
				if (x >= 0 && y >= 0 && cfq)
				{
					pos.X = x * 40;
					pos.Y = y * 40;
					textBox1.Text += x + "," + y + "," + z + "," + timeuse + Environment.NewLine;
					cfq = false;
				}

			}
			else if (ai == 2)
			{
				float lx = Math.Abs(x - xu);
				float ly = Math.Abs(y - yu);

				if (x >= 0 && y >= 0 && lx + ly <= 2.5 && cfq)
				{
					pos.X = x * 40;
					pos.Y = y * 40;
					textBox1.Text += x + "," + y + "," + timeuse + Environment.NewLine;
					cfq = false;
				}
			}
			else if (ai == 3)
			{
				if (x >= 0 && y >= 0 && cfq)
				{
					pos.X = x * 40;
					pos.Y = y * 40;
					textBox1.Text += x + "," + y + "," + timeuse + Environment.NewLine;
					cfq = false;
				}

			}
			else if (ai == 4)
			{
				float la = Math.Abs(x - xu) + Math.Abs(y - yu);

				if (x >= 0 && y >= 0 && la <= 2.5 && cfq)
				{
					pos.X = x * 40;
					pos.Y = y * 40;
					textBox1.Text += x + "," + y + "," + timeuse + Environment.NewLine;
					cfq = false;
				}
				else if (x >= 0 && y >= 0 && la > 2.5 && cfq)
				{
					pos.X = (int)Math.Round(xu * 40f + (x - xu) * 40f / la);
					pos.Y = (int)Math.Round(yu * 40f + (y - yu) * 40f / la);
					textBox1.Text += Math.Round(pos.X / 40f) + "," + Math.Round(pos.Y / 40f) + "," + timeuse + Environment.NewLine;
					cfq = false;
				}
			}
		}

		private void trackBar2_Scroll(object sender, EventArgs e)
		{
			if (trackBar2.Value == 0) aicontrol = false;
			else
			{
				aicontrol = true;
				ai = trackBar2.Value;
			}
		}

		private void Form1_FormClosing(object sender, FormClosingEventArgs e)
		{
			if (textBox1.Text != "")
			{
				DialogResult dr;
				dr=MessageBox.Show("检测到数据，是否保存？", "提示", MessageBoxButtons.YesNoCancel);
				if (dr == DialogResult.Yes)
				{
					save();
					e.Cancel = true;
				}
				else if (dr == DialogResult.No)
					return;
				else if (dr == DialogResult.Cancel)
					e.Cancel = true;
				else
					e.Cancel = true;
			}
		}

		private void checkBox2_CheckedChanged(object sender, EventArgs e)
		{
			trackBar2.Enabled = checkBox2.Checked;
		}

		private void button4_Click(object sender, EventArgs e)
		{
			save();
		}

		private void save()
		{
			SaveFileDialog sfd = new SaveFileDialog();
			//设置文件类型 
			sfd.Filter = "csv文件（*.csv）|*.csv";

			//设置默认文件类型显示顺序 
			sfd.FilterIndex = 1;

			//保存对话框是否记忆上次打开的目录 
			sfd.RestoreDirectory = true;

			sfd.FileName = "data.csv";

			//点了保存按钮进入 
			if (sfd.ShowDialog() == DialogResult.OK)
			{
				string localFilePath = "";
				//string localFilePath, fileNameExt, newFileName, FilePath; 
				localFilePath = sfd.FileName.ToString(); //获得文件路径 
				if (localFilePath == "") MessageBox.Show("没有文件名！", "提示");
				textBox1.Text += "score," + score;
				StreamWriter sw = new StreamWriter(localFilePath);
				sw.Write(textBox1.Text);
				sw.Close();
			}
		}

		private void checkBox1_CheckedChanged(object sender, EventArgs e)
		{
			if (checkBox1.Checked)
			{
				button3.Text = "导入以开始";
			}
			else
				button3.Text = "使用随机数";

		}

		//private void checkBox3_CheckedChanged(object sender, EventArgs e)
		//{
		//	button5.Enabled = checkBox3.Checked;
		//}

		//private void button5_Click(object sender, EventArgs e)
		//{
		//	OpenFileDialog dialog = new OpenFileDialog();
		//	dialog.Multiselect = true;//该值确定是否可以选择多个文件
		//	dialog.Title = "请选择文件夹";
		//	dialog.Filter = "csv文件|*.csv";
		//	if (dialog.ShowDialog() == DialogResult.OK)
		//	{
		//		string csvfile2 = dialog.FileName;
		//		Console.WriteLine(csvfile2);
		//		sr2 = new StreamReader(csvfile2);
		//		button5.Enabled = checkBox3.Enabled = false;
		//	}
		//}
	}
}
