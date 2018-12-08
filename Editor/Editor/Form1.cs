using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor
{
    public partial class Form1 : Form
    {
        private string fileName = "Source.blng";
        Compiler compiler = new Compiler();
        public Form1()
        {
            InitializeComponent();
            Timer timer = new Timer();
            timer.Tick += new EventHandler((o, a) => Hightlight());
            timer.Interval = 200;
            timer.Start();
            if (!File.Exists(fileName)) File.Create(fileName).Close();
            loadFromFile();
            Timer timer2 = new Timer();
            timer2.Tick += new EventHandler((o, a) => File.WriteAllLines(fileName, richTextBox1.Lines));
            timer2.Interval = 1000;
            timer2.Start();
        }

        private void loadFromFile()
        {
            richTextBox1.Lines = File.ReadAllLines(fileName);
            textHandled = false;
            prevPress.Restart();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            StreamReader output, error;
            var outFile = compiler.CompileBoolLang(fileName, out output, out error);
            string outStr = output.ReadToEnd();
            richTextBox3.Text = outStr + "\n" + error.ReadToEnd();
            richTextBox3.Select(outStr.Length, richTextBox3.Text.Length - outStr.Length + 1);
            richTextBox3.SelectionColor = Color.Red;
            if (outStr.StartsWith("Success"))
            {
                richTextBox2.Lines = File.ReadAllLines(outFile);
                compiler.CompileMSC(outFile, out output, out error);
                richTextBox3.Text += output.ReadToEnd() + "\n" + error.ReadToEnd();
                string ff = Path.GetFileName(fileName);
                Process.Start("CMD.exe", "/k " + ff.Substring(0, ff.Length - 4) + "exe");
            }
        }

        private bool textHandled = false;

        private Stopwatch prevPress = new Stopwatch();

        private void Hightlight()
        {
            if (prevPress.ElapsedMilliseconds < 800 || textHandled || richTextBox1.SelectedText.Length != 0) return;
            int current_position = richTextBox1.SelectionStart;
            string code = richTextBox1.Text;
            var separators = HightligthingText.punctations.Select(o => o[0]).ToArray();
            richTextBox1.SelectAll();
            richTextBox1.SelectionColor = Color.Black;
            foreach (var pair in HightligthingText.hightligthings)
            {
                var color = pair.Key;
                foreach (var word in pair.Value)
                {
                    if (word == " " || word == "\t" || word == "\n") continue;
                    int pos = -1;
                    while ((pos = code.IndexOf(word, pos + 1)) != -1)
                    {
                        if (word.Length == 1 || (pos == 0 || separators.Contains(code[pos - 1])) &&
                            (pos + word.Length == code.Length || separators.Contains(code[pos + word.Length])))
                        {
                            richTextBox1.Select(pos, word.Length);
                            richTextBox1.SelectionColor = color;
                        }
                    }
                }
            }
            richTextBox1.Select(current_position, 0);
            richTextBox1.SelectionColor = Color.Black;
            textHandled = true;
            prevPress.Reset();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            richTextBox1.Font = new Font("consolas", 14);
            prevPress.Restart();
            textHandled = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            StreamReader output, error;
            var outFile = compiler.CompileBoolLang(fileName, out output, out error);
            string outStr = output.ReadToEnd();
            richTextBox3.Text = outStr + "\n" + error.ReadToEnd();
            if (outStr.StartsWith("Success"))
            {
                richTextBox2.Lines = File.ReadAllLines(outFile);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.Cancel) return;
            fileName = openFileDialog1.FileName;
            loadFromFile();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.Cancel) return;
            fileName = saveFileDialog1.FileName;
            File.WriteAllText(fileName, richTextBox1.Text);
        }
    }
}
