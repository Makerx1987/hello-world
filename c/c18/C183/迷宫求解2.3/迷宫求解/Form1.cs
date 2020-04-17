using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;

namespace 迷宫求解
{
    public partial class Form1 : Form
    {
        int i, j, k, lim = 0;
        int columnlen = 10;
        float a = 360 / 10;
        int tick = 810 / 10;
        bool b;
        int[,] gridbks = new int[32, 32];
        int[,] tracks = new int[900, 2];
        SolidBrush mouse = new SolidBrush(Color.DeepSkyBlue);
        SolidBrush distination = new SolidBrush(Color.Black);
        SolidBrush block = new SolidBrush(Color.Gray);
        SolidBrush track = new SolidBrush(Color.LightGreen);
        SolidBrush blank = new SolidBrush(Color.GhostWhite);
        SolidBrush back = new SolidBrush(Color.GreenYellow);
        public Form1()
        {
            InitializeComponent();
        }



        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton senderRB = (RadioButton)sender;
            if (senderRB.Checked)
            {
                columnlen = (senderRB.TabIndex + 1) * 10;
                a = 360 / columnlen;
                tick = 810 / columnlen;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            b = true;
            Worldbuilder();
            pictureBox1.Refresh();
            this.radioButton1.Enabled = false;
            this.radioButton2.Enabled = false;
            this.radioButton3.Enabled = false;
            this.button1.Enabled = false;
            this.button2.Enabled = true;
            this.button3.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            b = false;
            Antiworldbuilder();
            pictureBox1.Refresh();
            this.radioButton1.Enabled = true;
            this.radioButton2.Enabled = true;
            this.radioButton3.Enabled = true;
            this.button2.Enabled = false;
            this.button1.Enabled = true;
            this.button3.Enabled = false;
            this.textBox1.Enabled = false;
            textBox1.Text = "";
        }

        private void button3_Click(object sender, EventArgs e)
        {

            Thread ftproc = new Thread(new ThreadStart(Enderprint));
            ftproc.IsBackground = false;
            ftproc.Start();
        }
        private void Enderprint()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            this.button3.Enabled = false;
            this.button2.Enabled = false;
            i = j = k = 0;
            Graphics gr = pictureBox1.CreateGraphics();
            Thread bgproc = new Thread(new ParameterizedThreadStart(Explore));
            bgproc.IsBackground = true;
            bgproc.Start(gr);
            bgproc.Join();
            textBox1.Text += Environment.NewLine + Environment.NewLine + "得到路径如下：" + Environment.NewLine;
            for (i = 0; i < k + 1; i++)
            {
                textBox1.Text += "(";
                textBox1.Text += tracks[i, 0].ToString();
                textBox1.Text += ",";
                textBox1.Text += tracks[i, 1].ToString();
                textBox1.Text += ")-->";
            }
            textBox1.Text += "终点";
            textBox1.SelectionStart = textBox1.Text.Length;
            textBox1.ScrollToCaret();
            this.button2.Enabled = true;
            this.textBox1.Enabled = true;
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            if (b == false) return;
            int ni, nj, nk;
            Graphics gr = e.Graphics;
            textBox1.Text += "*****运行日志---开始渲染" + "---";
            textBox1.Text += "初始化成功" + "---";
            for (ni = 0; ni < columnlen; ni++)
            {
                for (nj = 0; nj < columnlen; nj++)
                {
                    if (gridbks[ni, nj] == 1) gr.FillRectangle(block, ni * a, nj * a, a, a);
                    else if (gridbks[ni, nj] == 9) gr.FillRectangle(back, ni * a, nj * a, a, a);
                    else gr.FillRectangle(blank, ni * a, nj * a, a, a);
                    gr.DrawRectangle(Pens.Gold, ni * a, nj * a, a, a);
                }
            }
            
            for (nk = 0; nk <= k; nk++)
            {
                gr.FillRectangle(track, tracks[nk, 0] * a, tracks[nk, 1] * a, a, a);
                gr.DrawRectangle(Pens.Gold, tracks[nk, 0] * a, tracks[nk, 1] * a, a, a);
            }

            gr.FillRectangle(mouse, i * a, j * a, a, a);
            gr.DrawRectangle(Pens.Gold, 0, 0, a, a);
            gr.FillRectangle(distination, (columnlen - 1) * a, (columnlen - 1) * a, a, a); gridbks[columnlen - 1, columnlen - 1] = 0;
            gr.DrawRectangle(Pens.Gold, (columnlen - 1) * a, (columnlen - 1) * a, a, a);
            textBox1.Text += "构造成功" + "---";
        }

        public void Worldbuilder()
        {
            Random rd = new Random();

            for (i = 0; i < columnlen; i++)
            {
                for (j = 0; j < columnlen; j++)
                {
                    gridbks[i, j] = (int)rd.Next(0, 4);
                }
            }
            i = j = 0;
        }
        public void Antiworldbuilder()
        {

            for (i = 0; i < 30; i++)
            {
                for (j = 0; j < 30; j++)
                {
                    gridbks[i, j] = 0;
                }
            }
            for (i = 0; i < 900; i++)
            {
                for (j = 0; j < 2; j++)
                {
                    tracks[i, j] = 0;
                }
            }
            lim = 0;
            progressBar1.Value = 0;
        }
        public void Explore(object mgr)
        {
            Graphics gr = (Graphics)mgr;
            lim++;
            progressBar1.Value = lim / 3;
            if (lim > 300)
            {
                MessageBox.Show("？？？可能迷宫没有通路，程序停止。");
                for (i = 0; i < 900; i++)
                {
                    for (j = 0; j < 2; j++)
                    {
                        tracks[i, j] = 0;
                    }
                }
                i = j = columnlen - 1;
                k = -1;
                return;
            }
            System.Threading.Thread.Sleep(tick);
            if (i + 1 < columnlen)
            {
                if (gridbks[i + 1, j] != 1 && gridbks[i + 1, j] != 9)
                {

                    gr.FillRectangle(mouse, (i + 1) * a, j * a, a, a);
                    gr.DrawRectangle(Pens.Gold, (i + 1) * a, j * a, a, a);
                    gr.FillRectangle(track, i * a, j * a, a, a);
                    gr.DrawRectangle(Pens.Gold, i * a, j * a, a, a);
                    gridbks[i + 1, j] = 9;
                    tracks[k, 0] = i;
                    tracks[k, 1] = j;
                    i++;
                    if (i >= columnlen - 1 && j >= columnlen - 1)
                    {
                        if (progressBar1.Value < 25) progressBar1.Value = 25;
                        if (progressBar1.Value < 50) progressBar1.Value = 50;
                        progressBar1.Value = 100;
                        MessageBox.Show("迷宫求解成功！路径数据量" + k.ToString() + "个位置。按确定输出数据，若数据量大请耐心等待。");
                        return;
                    }
                    k++;
                    textBox1.Text += "右行成功" + "---";
                    Explore(gr);
                    if (i >= columnlen - 1 && j >= columnlen - 1) return;
                }
                else
                {
                    textBox1.Text += "右行失败" + "---";
                }
            }
            System.Threading.Thread.Sleep(tick);
            if (j + 1 < columnlen)
            {
                if (gridbks[i, j + 1] != 1 && gridbks[i, j + 1] != 9)
                {

                    gr.FillRectangle(mouse, i * a, (j + 1) * a, a, a);
                    gr.DrawRectangle(Pens.Gold, i * a, (j + 1) * a, a, a);
                    gr.FillRectangle(track, i * a, j * a, a, a);
                    gr.DrawRectangle(Pens.Gold, i * a, j * a, a, a);
                    gridbks[i, j + 1] = 9;
                    tracks[k, 0] = i;
                    tracks[k, 1] = j;
                    j++;
                    if (i >= columnlen - 1 && j >= columnlen - 1)
                    {
                        if (progressBar1.Value < 25) progressBar1.Value = 25;
                        if (progressBar1.Value < 50) progressBar1.Value = 50;
                        progressBar1.Value = 100;
                        MessageBox.Show("迷宫求解成功！路径数据量" + k.ToString() + "个位置。按确定输出数据，若数据量大请耐心等待。");
                        return;
                    }
                    k++;
                    textBox1.Text += "下行成功" + "---";
                    Explore(gr);
                    if (i >= columnlen - 1 && j >= columnlen - 1) return;

                }
                else
                {
                    textBox1.Text += "下行失败" + "---";
                }
            }
            System.Threading.Thread.Sleep(tick);
            if (i - 1 >= 0)
            {
                if (gridbks[i - 1, j] != 1 && gridbks[i - 1, j] != 9)
                {

                    gr.FillRectangle(mouse, i * a - a, j * a, a, a);
                    gr.DrawRectangle(Pens.Gold, i * a - a, j * a, a, a);
                    gr.FillRectangle(track, i * a, j * a, a, a);
                    gr.DrawRectangle(Pens.Gold, i * a, j * a, a, a);
                    gridbks[i - 1, j] = 9;
                    tracks[k, 0] = i;
                    tracks[k, 1] = j;
                    i--;
                    k++;
                    textBox1.Text += "左行成功" + "---";
                    Explore(gr);
                    if (i >= columnlen - 1 && j >= columnlen - 1) return;
                }
                else
                {
                    textBox1.Text += "左行失败" + "---";
                }
            }
            System.Threading.Thread.Sleep(tick);
            if (j - 1 >= 0)
            {
                if (gridbks[i, j - 1] != 1 && gridbks[i, j - 1] != 9)
                {

                    gr.FillRectangle(mouse, i * a, j * a - a, a, a);
                    gr.DrawRectangle(Pens.Gold, i * a, j * a - a, a, a);
                    gr.FillRectangle(track, i * a, j * a, a, a);
                    gr.DrawRectangle(Pens.Gold, i * a, j * a, a, a);
                    gridbks[i, j - 1] = 9;
                    tracks[k, 0] = i;
                    tracks[k, 1] = j;
                    j--;
                    k++;
                    textBox1.Text += "上行成功" + "---";
                    Explore(gr);
                    if (i >= columnlen - 1 && j >= columnlen - 1) return;
                }
                else
                {
                    textBox1.Text += "上行失败" + "---";
                }
            }
            k--;
            gr.FillRectangle(back, i * a, j * a, a, a);
            gr.DrawRectangle(Pens.Gold, i * a, j * a, a, a);
            textBox1.Text += "回到上一个可信点" + "---";
            if (k < 0)
            {
                if (progressBar1.Value < 25) progressBar1.Value = 25;
                if (progressBar1.Value < 50) progressBar1.Value = 50;
                progressBar1.Value = 100;
                MessageBox.Show("迷宫求解失败！原因：没有通路。");
                textBox1.Text += "结束";
                return;
            }
            else
            {
                i = tracks[k, 0];
                j = tracks[k, 1];
                gr.FillRectangle(mouse, i * a, j * a, a, a);
                gr.DrawRectangle(Pens.Gold, i * a, j * a, a, a);
            }

        }


    }
}

