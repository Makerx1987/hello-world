using Microsoft.CSharp;
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public class Class1
    {
		private object _compiled;

		private void constructEvaluator(string formula)
		{
			ICodeCompiler compiler = (new CSharpCodeProvider().CreateCompiler());
			CompilerParameters cp = new CompilerParameters();
			cp.ReferencedAssemblies.Add("system.dll");

			cp.GenerateExecutable = false;
			cp.GenerateInMemory = true;

			StringBuilder str = new StringBuilder();
			str.Append("using   System;   \n");
			str.Append("namespace   Stoway   {   \n");
			str.Append("public   class   Formula   {   \n");

			str.AppendFormat(" public   {0}   GetValue()", "Double");
			str.Append("{");
			str.AppendFormat(" return   Convert.ToDouble({0});   ", formula);
			str.Append("}\n");
			str.Append("}\n");
			str.Append("}");

			CompilerResults cr = compiler.CompileAssemblyFromSource(cp, str.ToString());
			if (cr.Errors.HasErrors)
			{
				throw new Exception("不是正确的表达式");
			}
			Assembly a = cr.CompiledAssembly;
			_compiled = a.CreateInstance("Stoway.Formula");
		}
	}
}
