using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Threading;

namespace Display
{
    class Displayer : FrameworkElement
    {
        private List<EllipseGeometry> points;

        private List<EllipseGeometry> boundary;

        private FilereadtoPoints f;       

        private int sz = 0;

        private DispatcherTimer t;

        private const int n = 10;

        public Displayer()
        {
            points = new List<EllipseGeometry>();
            boundary = new List<EllipseGeometry>();
            f = new FilereadtoPoints("SmallestBoundaryPolygon_HillClimbingStochastic.txt");            
            Point();
            Boundarycreate();
            t = new DispatcherTimer();
            t.Interval = new TimeSpan(0, 0, 0, 0, 1);
            t.Tick += T_Tick;
            t.Start();
        }

        private void T_Tick(object sender, EventArgs e)
        {
            BoundaryRefresh();
            InvalidateVisual();
        }

        protected override void OnRender(DrawingContext drawingContext)
        {
            base.OnRender(drawingContext);

            if (points != null)
            {
                foreach (var i in points)
                {
                    drawingContext.DrawGeometry(Brushes.Blue, null, i);
                }
            }

            if (boundary != null)
            {
                for (int i = 0; i < boundary.Count; i++)
                {
                    drawingContext.DrawGeometry(Brushes.Red, null, boundary.ElementAt(i));
                    if (i < boundary.Count - 1)
                    {
                        drawingContext.DrawLine(new Pen(Brushes.Black, 1), boundary.ElementAt(i).Center, boundary.ElementAt(i + 1).Center);
                    }
                    else
                    {
                        drawingContext.DrawLine(new Pen(Brushes.Black, 1), boundary.ElementAt(i).Center, boundary.ElementAt(0).Center);
                    }
                }
            }
        }

        private void Point()
        {
            foreach (var f in f.Points)
            {
                EllipseGeometry e = new EllipseGeometry(f, 10, 10);
                points.Add(e);
            }
        }

        private void Boundarycreate()
        {
            for (int i = 0; i < n; i++)
            {
                boundary.Add(new EllipseGeometry());
            }
        }

        private void BoundaryRefresh()
        {           
            int i = 0;
            int c = sz;
            for (int j = c ; j < f.Boundary.Count && j < c + n; j++)
            {
                boundary.ElementAt(i).Center = new Point(f.Boundary.ElementAt(j).X, f.Boundary.ElementAt(j).Y);
                boundary.ElementAt(i).RadiusX = 8;
                boundary.ElementAt(i).RadiusY = 8;
                sz++;
                i++;
            }
        }
    }
}
