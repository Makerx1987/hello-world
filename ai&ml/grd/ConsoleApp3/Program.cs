using System;
namespace testapp
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("hello world");
			grd.pool mpool = new grd.pool("1.txt");
			foreach (double item in mpool.next(3)) Console.WriteLine(item.ToString());
			Console.ReadLine();
		}
	}
}
