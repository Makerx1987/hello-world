using System;
using System.CodeDom.Compiler;
using System.Text;

namespace ConsoleApp2
{
	class Program
	{
		static void Main(string[] args)
		{

			CodeDomProvider provider = CodeDomProvider.CreateProvider("cs");
			
			CompilerParameters p = new CompilerParameters
			{
				GenerateExecutable = true,
				OutputAssembly = "testapp.exe",
			};
			
			p.ReferencedAssemblies.Add("System.dll");
			p.ReferencedAssemblies.Add("grd.dll");

			StringBuilder code = new StringBuilder();
			code.Append("using System; \n");
			code.Append("using System.Collections.Generic; \n");
			code.Append("using System.Text; \n");
			code.Append("using grd; \n");
			code.Append("namespace testapp { \n");
			code.Append("class Program {");
			code.Append("static void Main(string[] args){\n ");

			code.Append("Console.WriteLine(\"hello world\");\n");
			code.Append("grd.pool mpool=new grd.pool(\"1.txt\");\n");
			code.Append("foreach(double item in mpool.next(3))Console.WriteLine(item.ToString());\n");
			code.Append("Console.ReadLine();\n");

			code.Append("}");
			code.Append("}");
			code.Append("}");
			Console.WriteLine(code.ToString());

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
			Console.ReadLine();
		}
	}
}
