using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Display
{
    class FilereadtoPoints
    {
        StreamReader r;

        StreamReader r1;

        private List<Point> points;

        private List<Point> boundary;   

        public FilereadtoPoints(string f1)
        {            r = new StreamReader(f1);
            r1 = new StreamReader("Points.txt");
            points = new List<Point>();
            boundary = new List<Point>();
            ReadPoints();
            ReadBoundary();
        }

        public List<Point> Boundary
        {
            get { return boundary; }
            set { boundary = value; }
        }

        public List<Point> Points
        {
            get { return points; }
            set { points = value; }
        }

        private void ReadBoundary()
        {
            string s = r.ReadToEnd();
            string[] c = s.Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);
            for (int i = 0; i < c.Length; i++)
            {
                string[] d = c[i].Split('\t');
                double x = double.Parse(d[0].Replace('.', ','));
                double y = double.Parse(d[1].Replace('.', ','));
                boundary.Add(new Point(x, y));
            }
        }

        private void ReadPoints()
        {            
            string s = r1.ReadToEnd();            
            string[] c = s.Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries);
            for (int i = 0; i < c.Length; i++)
            {
                
                string[] d = c[i].Split('\t');
                double x = double.Parse(d[0].Replace('.', ','));
                double y = double.Parse(d[1].Replace('.', ','));
                points.Add(new Point(x, y));
            }
        }
    }
}
