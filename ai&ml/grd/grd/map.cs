using System;
using System.Collections.Generic;
using System.Text;

namespace grd
{
	public partial class map
	{
		/// <summary>
		/// 名称
		/// </summary>
		public string name;
		/// <summary>
		/// 形状，先列数后行数
		/// </summary>
		public int[] shape;
		/// <summary>
		/// 数据，二维数组
		/// </summary>
		public double[,] data;
		/// <summary>
		/// 改变形状
		/// </summary>
		public map Reshape()
		{
			map c = new map(shape[0] * shape[1], 1);
			double[,] new_data = new double[shape[0] * shape[1], 1];
			for (int cl = 0; cl < shape[0]; cl++)
				for (int r = 0; r < shape[1]; r++)
					new_data[cl * shape[1] + r, 0] = data[cl, r];
			c.data = new_data;
			return c;
		}
		/// <summary>
		/// 绑定数据来源
		/// </summary>
		/// <param name="arr">一个必须符合data大小的二维数组</param>
		public void feed(List<double> list)
		{
			for (int cl = 0; cl < shape[0]; cl++)
				for (int r = 0; r < shape[1]; r++)
					if (shape[1] * cl + r < list.Count) data[cl, r] = list[shape[1] * cl + r]; else throw new Exception("poor data");
			list.RemoveRange(0, shape[0] * shape[1]);
		}
		public void feedonce(double[] list)
		{
			if(list.Length !=shape[0]*shape[1]) throw new Exception("poor data");
			for (int cl = 0; cl < shape[0]; cl++)
				for (int r = 0; r < shape[1]; r++)
					data[cl, r] = list[shape[1] * cl + r];			
		}
		public void feed(pool datapool)
		{
			feedonce(datapool.next(shape[0] * shape[1]));
		}
		/// <summary>
		/// 图的构造函数
		/// </summary>
		/// <param name="columns">列数</param>
		/// <param name="rows">行数</param>
		/// <param name="cname">名字</param>
		public map(int columns = 1, int rows = 1, string cname = "")
		{
			name = cname;
			if (columns > 0 && rows > 0) shape = new int[] { columns, rows };
			data = new double[columns, rows];
		}
		/// <summary>
		/// 重载*运算，矩阵乘法
		/// </summary>
		/// <param name="a">图类型</param>
		/// <param name="b">图类型</param>
		/// <returns>一个矩阵乘法的结果图</returns>
		public static map operator *(map a, map b)
		{
			map c;
			if (a.shape[1] != b.shape[0])
			{
				throw new Exception("检查矩阵形状");
			}
			else
			{
				c = new map(a.shape[0], b.shape[1]);
				for (int cl = 0; cl < c.shape[0]; cl++)
					for (int r = 0; r < c.shape[1]; r++)
						for (int co = 0; co < a.shape[1]; co++)
							c.data[cl, r] += a.data[cl, co] * b.data[co, r];
				return c;
			}
		}
		/// <summary>
		/// 重载+运算，矩阵乘法
		/// </summary>
		/// <param name="a">图类型</param>
		/// <param name="b">图类型</param>
		/// <returns>一个矩阵加法的结果图</returns>
		public static map operator +(map a, map b)
		{
			map c;
			if (a.shape[0] == b.shape[0] && a.shape[1] == b.shape[1])
			{
				c = new map(a.shape[0], b.shape[1]);
				for (int cl = 0; cl < c.shape[0]; cl++)
					for (int r = 0; r < c.shape[1]; r++)
						c.data[cl, r] = a.data[cl, r] + b.data[cl, r];
				return c;
			}
			else
			{
				throw new Exception("检查矩阵形状");
			}
		}
		public static map operator -(map a, map b)
		{
			map c;
			if (a.shape[0] == b.shape[0] && a.shape[1] == b.shape[1])
			{
				c = new map(a.shape[0], b.shape[1]);
				for (int cl = 0; cl < c.shape[0]; cl++)
					for (int r = 0; r < c.shape[1]; r++)
						c.data[cl, r] = a.data[cl, r] - b.data[cl, r];
				return c;
			}
			else
			{
				throw new Exception("检查矩阵形状");
			}
		}
		public map T()
		{
			map c = new map(shape[1], shape[0]);
			for (int cl = 0; cl < c.shape[0]; cl++)
				for (int r = 0; r < c.shape[1]; r++)
					c.data[r, cl] = data[cl, r];
			return c;
		}
		public static map mul(map a, map b)
		{
			map c;
			if (a.shape[0] == b.shape[0] && a.shape[1] == b.shape[1])
			{
				c = new map(a.shape[0], b.shape[1]);
				for (int cl = 0; cl < c.shape[0]; cl++)
					for (int r = 0; r < c.shape[1]; r++)
						c.data[cl, r] = a.data[cl, r] * b.data[cl, r];
				return c;
			}
			else
			{
				throw new Exception("检查矩阵形状");
			}
		}
		public static map log(map a)
		{
			map c;

			c = new map(a.shape[0], a.shape[1]);
			for (int cl = 0; cl < c.shape[0]; cl++)
				for (int r = 0; r < c.shape[1]; r++)
					c.data[cl, r] = Math.Log(a.data[cl, r]);
			return c;

		}
		public map change(double a)
		{
			map c;

			c = new map(shape[0], shape[1]);
			for (int cl = 0; cl < c.shape[0]; cl++)
				for (int r = 0; r < c.shape[1]; r++)
					c.data[cl, r] += a;
			return c;
		}
		public map rev()
		{
			map c;

			c = new map(shape[0], shape[1]);
			for (int cl = 0; cl < c.shape[0]; cl++)
				for (int r = 0; r < c.shape[1]; r++)
					c.data[cl, r] = -c.data[cl, r];
			return c;
		}
		public double sum()
		{
			double c = 0;
			for (int cl = 0; cl < shape[0]; cl++)
				for (int r = 0; r < shape[1]; r++)
					c += data[cl, r];
			return c;
		}
	}
}
