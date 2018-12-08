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

        public string CompileBoolLang(string sourcePath)
        {
            var outputFile = sourcePath + ".cpp";
            Process.Start(bool_lang_compile_path, sourcePath + " -o " + outputFile);
            return outputFile;
        }

        private string GetPathWithLastVersion(string path) => Directory.GetDirectories(path).Last();

        private string GetVSLastVsVersion()
        {
            string path = Path.Combine(vs_path, "VC", "Tools", "MSVC");
            return GetPathWithLastVersion(path);
        }

        public void CompileMSC(string sourcePath)
        {
            var VSVerPath = GetVSLastVsVersion();

        }

    }
}
