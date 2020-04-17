using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace grd
{
	public class pool
	{
		private string filename;
		string ss;
		private List<double> data;
		public pool(string cfilename, string css = ",")
		{
			ss = css;
			filename = cfilename;
			data = new List<double>();
		}
		public double[] next(int number = 1)
		{
			// 创建一个 StreamReader 的实例来读取文件 
			// using 语句也能关闭 StreamReader
			using (StreamReader sr = new StreamReader(Environment.CurrentDirectory + "\\" + filename))
			{
				string line;
				Console.WriteLine(Environment.CurrentDirectory + "\\" + filename);
				// 从文件读取并显示行，直到文件的末尾 
				while ((line = sr.ReadLine()) != null)
				{
					foreach (string item in Regex.Split(line, ss))
						data.Add((double)decimal.Parse(item));
				}
			}
			if (data == null) throw new Exception("no data in file");
			if (number < 1) throw new Exception("wrong number ,must 1+");
			if (data.Count < number) throw new Exception("poor data");
			double[] outer = new double[number];
			for (int n = 0; n < number; n++)
				outer[n] = data[n];
			data.RemoveRange(0, number);
			return outer;
		}
	}
}
