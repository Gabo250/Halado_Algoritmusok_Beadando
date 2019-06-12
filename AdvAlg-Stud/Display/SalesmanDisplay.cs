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
    class SalesmanDisplay : FrameworkElement
    {
        private FilereadtoPoints f;

        private List<EllipseGeometry> elips;

        private DispatcherTimer t;

        private const int m = 26;

        private int n = 0;

        private int k = 0;

        public SalesmanDisplay()
        {
            f = new FilereadtoPoints("TravellingSalesman.txt");
            elips = new List<EllipseGeometry>();
            t = new DispatcherTimer();            
            t.Interval = new TimeSpan(0, 0, 0, 0, 10);
            t.Tick += T_Tick;
            t.Start();
        }

        private void T_Tick(object sender, EventArgs e)
        {
            Refresh();
            InvalidateVisual();
        }

        protected override void OnRender(DrawingContext drawingContext)
        {
            base.OnRender(drawingContext);
            if (elips != null)
            {
                foreach (var i in elips)
                {
                    drawingContext.DrawGeometry(Brushes.Black, null, i);
                    drawingContext.DrawGeometry(Brushes.Green, null, elips.ElementAt(0));
                }

                for (int i = 0; i < elips.Count - 1; i++)
                {
                    drawingContext.DrawLine(new Pen(Brushes.Red, 2), elips.ElementAt(i).Center, elips.ElementAt(i + 1).Center);                    
                }
            }
        }    

        private void Refresh()
        {
            int kc = k;
            for (int i = kc; i < f.Boundary.Count && i < kc + m; i++)
            {
                if (i < m)
                {
                    elips.Add(new EllipseGeometry(f.Boundary.ElementAt(i), 10, 10));                   
                }
                else
                {
                    if (n == 26)
                    {
                        n = 0;
                    }
                    elips.ElementAt(n).Center = f.Boundary.ElementAt(i);
                }

                k++;
                n++;
            }
        }
    }
}
