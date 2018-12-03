using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            richTextBox1.Select(0, 5);
            richTextBox1.SelectionColor = Color.Red;

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            richTextBox1.Font = new Font("consolas", 14);
            if (richTextBox1.SelectedText.Length != 0) return;
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
        }
    }
}
