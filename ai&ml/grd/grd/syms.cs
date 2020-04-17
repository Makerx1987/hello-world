using System;
using System.Collections.Generic;

namespace grd
{
	public class syms
	{
		public string name;
		public static map tempmap;
		public static syms tempsyms;
		private map data;
		public readonly int index;
		public void init(int columns, int rows)
		{
			tempmap = new map(columns, rows);
			sess.maps[index] = tempmap;
		}
		public void rename(string cname= "")
		{
			name = cname;
		}
		public void feed(List<double> list)
		{
			data.feed(list);
			sess.code.Append($"sess.maps[{index}].feed({list});");			
		}
		public void feedonce(double[] list)
		{
			data.feedonce(list);
			sess.code.Append($"sess.maps[{index}].feedonce({list});");
		}
		public void feed(pool datapool)
		{
			data.feed(datapool);
			sess.code.Append($"sess.maps[{index}].feed({datapool});");
		}

		public syms(string cname = "")
		{
			name = cname;
			index = sess.maps.Count;			
			sess.maps.Add(data);
		}
		public syms(int columns, int rows, string cname = "")
		{
			tempmap = new map(columns, rows);
			name = cname;
			index = sess.maps.Count;
			sess.maps.Add(data);
		}

		public syms(map cmap, string cname = "")
		{
			name = cname;
			data = cmap;
			index = sess.maps.Count;
			sess.maps.Add(data);
		}


		public static syms operator *(syms a, syms b)
		{
			tempsyms = new syms(a.data * b.data);
			sess.code.Append($"sess.maps[{a.index}]*sess.maps[{b.index}];");
			return tempsyms;
		}

		public static syms operator +(syms a, syms b)
		{
			tempsyms = new syms(a.data + b.data);
			sess.code.Append($"sess.maps[{a.index}]+sess.maps[{b.index}];");
			return tempsyms;
		}

		public static syms operator -(syms a, syms b)
		{
			tempsyms = new syms(a.data - b.data);
			sess.code.Append($"sess.maps[{a.index}]-sess.maps[{b.index}];");
			return tempsyms;
		}

		public syms T()
		{
			tempsyms = new syms(data.T());
			sess.code.Append($"sess.maps[{index}].T();");
			return tempsyms;
		}

		public static syms mul(syms a, syms b)
		{
			tempsyms = new syms(map.mul(a.data, b.data));
			sess.code.Append($"map.mul(sess.maps[{a.index}],sess.maps[{b.index}]);");
			return tempsyms;
		}

		public static syms log(syms a)
		{
			tempsyms = new syms(map.log(a.data));
			sess.code.Append($"map.log(sess.maps[{a.index}]);");
			return tempsyms;
		}

		public syms change(double a)
		{
			tempsyms = new syms(data.change(a));
			sess.code.Append($"sess.maps[{index}]).change({a});");
			return tempsyms;
		}

		public syms rev()
		{
			tempsyms = new syms(data.rev());
			sess.code.Append($"sess.maps[{index}]).rev();");
			return tempsyms;
		}

		public double sum()
		{
			sess.code.Append($"sess.maps[{index}]).sum();");
			return data.sum();
		}
	}
}
