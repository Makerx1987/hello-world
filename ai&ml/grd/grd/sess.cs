using System;
using System.Collections.Generic;
using System.Text;
using System.CodeDom.Compiler;
using System.Reflection;

namespace grd
{
	public static class sess
	{
		static CodeDomProvider provider = CodeDomProvider.CreateProvider("cs");
		static CompilerParameters p = new CompilerParameters
		{
			GenerateExecutable = true,
			OutputAssembly = "testapp.exe",
		};
		public static StringBuilder code = new StringBuilder();
		public static bool hasstart = false;
		public static bool hasend = false;
		public static List<map> maps;
		public static void start()
		{
			if (hasstart) throw new Exception("start twice error");
			p.ReferencedAssemblies.Add("System.dll");
			p.ReferencedAssemblies.Add("grd.dll");
			code.Append("using System; \n");
			code.Append("using System.Collections.Generic; \n");
			code.Append("using System.Text; \n");
			code.Append("using grd; \n");
			code.Append("namespace testapp { \n");
			code.Append("class Program {");
			code.Append("static void Main(string[] args){\n ");
			hasstart = true;
		}
		public static void end()
		{
			if (hasend) throw new Exception("end twice error");
			if (!hasstart) throw new Exception("no start error");
			code.Append("}");
			code.Append("}");
			code.Append("}");
			Console.WriteLine(code.ToString());
			hasend = true;
		}
		public static void run()
		{
			if (!hasend) throw new Exception("incomplete sess");
			foreach(map item in maps)if(item==null) throw new Exception("null map has been found");
			CompilerResults res = provider.CompileAssemblyFromSource(p, code.ToString());
			if (res.Errors.Count == 0)
			{
				Console.WriteLine("编译成功。");
				// 启动它
				System.Diagnostics.Process.Start(res.CompiledAssembly.Location);
			}
			else
			{
				Console.WriteLine("错误信息：");
				foreach (CompilerError er in res.Errors)
				{
					Console.WriteLine(er.ErrorText);
				}
			}
		}
	}
}
