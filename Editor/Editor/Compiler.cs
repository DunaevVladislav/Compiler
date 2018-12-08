using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    public class Compiler
    {
        private const string config_path = ".config";

        private  const string bool_lang_arg = "BOOLLANG";
        private string bool_lang_compile_path = "C:\\Program Files (x86)\\BoolLang\\bool-lang.exe";


        private const string vs_lang_arg = "VS";
        private string vs_path = "C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community";

        private const string windows_tools_arg = "WINDOWS_TOOLS";
        private string windows_tools_path = "C:\\Program Files (x86)\\Windows Kits\\10";

        public Compiler() {
            if (File.Exists(config_path))
            {
                ReadConfig();
            }
            else
            {
                CreateDefaultConfig();
            }
        }

        private void ReadConfig()
        {
            var configs = File.ReadAllLines(config_path);
            foreach(var config in configs)
            {
                var pos = config.IndexOf(':');
                if (pos == -1 || pos == config.Length - 1) continue;
                string argName = config.Substring(0, pos);
                string arg = config.Substring(pos + 1);
                switch (argName)
                {
                    case bool_lang_arg:
                        bool_lang_compile_path = arg;
                        break;
                    case vs_lang_arg:
                        vs_path = arg;
                        break;
                    case windows_tools_arg:
                        windows_tools_path = arg;
                        break;
                }
            }
        }

        private void CreateDefaultConfig()
        {
            StreamWriter config = new StreamWriter(config_path);
            config.WriteLine(bool_lang_arg + ":" + bool_lang_compile_path);
            config.WriteLine(vs_lang_arg + ":" + vs_path);
            config.WriteLine(windows_tools_arg + ":" + windows_tools_path);
            config.Close();
        }

        public string CompileBoolLang(string sourcePath, out StreamReader output, out StreamReader error)
        {
            var outputFile = sourcePath.Substring(0, sourcePath.Length - 4) + "cpp";
            Process process = new Process();
            process.StartInfo.Arguments = sourcePath + " -o " + outputFile;
            process.StartInfo.FileName = bool_lang_compile_path;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.RedirectStandardError = true;
            process.Start();
            output = process.StandardOutput;
            error = process.StandardError;
            return outputFile;
        }

        private string GetPathWithLastVersion(string path)
        {
            foreach(var dir in Directory.GetDirectories(path).Reverse())
            { 
                for (int i = dir.Length - 1; i >= 0; --i) {
                    if (dir[i] == '\\') return dir;
                    if (!(dir[i] >= '0' && dir[i] <= '9' || dir[i] == '.')) break;
                }
            }
            return path;
        }

        private string GetVSLastVsVersion()
        {
            string path = Path.Combine(vs_path, "VC", "Tools", "MSVC");
            return GetPathWithLastVersion(path);
        }

        public void CompileMSC(string sourcePath, out StreamReader output, out StreamReader error)
        {
            var VSVerPath = GetVSLastVsVersion();
            var CLPath = Path.Combine(VSVerPath, "bin", "Hostx86", "x86", "cl.exe");
            var VSInludes = Path.Combine(VSVerPath, "include");
            var WindowsInludes = Path.Combine(GetPathWithLastVersion(Path.Combine(windows_tools_path, "Include")), "ucrt");

            var LinkVS = Path.Combine(VSVerPath, "lib", "x86");
            var LinkWin1 = Path.Combine(GetPathWithLastVersion(Path.Combine(windows_tools_path, "lib")), "um", "x86");
            var LinkWin2 = Path.Combine(GetPathWithLastVersion(Path.Combine(windows_tools_path, "lib")), "ucrt", "x86");

            var arguments = "/EHsc" +
                " /I " + "\"" + VSInludes + "\"" +
                " /I " + "\"" + WindowsInludes + "\"" +
                " " + "\"" + sourcePath + "\"" +
                " /link" +
                " /LIBPATH:" + "\"" + LinkVS + "\"" +
                " /LIBPATH:" + "\"" + LinkWin1 + "\"" +
                " /LIBPATH:" + "\"" + LinkWin2 + "\"";

            Process process = new Process();
            process.StartInfo.Arguments = arguments;
            process.StartInfo.FileName = CLPath;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.RedirectStandardError = true;
            process.Start();
            output = process.StandardOutput;
            error = process.StandardError;
        }

    }
}
