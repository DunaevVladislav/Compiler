using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class HightligthingText
    {
        public static Dictionary<Color, List<string>> hightligthings = new Dictionary<Color, List<string>>();

        public static List<string> keyWords;

        public static List<string> punctations;

        public static List<string> signs;

        static HightligthingText()
        {
            keyWords = new List<string>{
                "logical",
                "read",
                "write",
                "if",
                "then",
                "else",
                "end_if",
                "var",
                "begin",
                "end",
            };
            punctations = new List<string>
            {
                " ",
                "\t",
                "\n",
                ",",
                ":",
                ";",
                "(",
                ")",
            };
            signs = new List<string>
            {
                "not",
                "and",
                "equ",
                "or"
            };
            hightligthings.Add(Color.Blue, keyWords);
            hightligthings.Add(Color.DarkGreen, punctations);
            hightligthings.Add(Color.Purple, signs);
        }
    }
}
