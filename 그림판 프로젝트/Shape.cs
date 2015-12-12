using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.Drawing;

namespace Assign_3
{
    abstract class Shape
    {
        private ArrayList points = new ArrayList();

        private Pen dPen = null;
        private Brush dBrush = null;
        private Color bColor, bColor2;
        private string imgPath = "NONE";
        private MainForm.Mode dMode;
        private MainForm.BrushStyle bStyle;

        public Shape() { }
        public Shape(ArrayList points)
        {
            this.points = (ArrayList)points.Clone();
        }

        public Point[] getPointsAsArr() { return (Point[])(points.ToArray(typeof(Point))); }
        public ArrayList getPoints() { return points; }
        public void setPoints(ArrayList points) { this.points = points; }
        public void addPoint(Point p) { points.Add(p); }
        public void removePoint(Point p) { points.Remove(p); }

        public Pen getPen() { return dPen; }
        public void setPen(Pen dPen) { this.dPen = (Pen)dPen.Clone(); }
        public Brush getBrush() { return dBrush; }
        public void setBrush(Brush dBrush) { this.dBrush = (Brush)dBrush.Clone(); }
        public Color getBrushColor() { return bColor; }
        public Color getBrushColor2() { return bColor2; }
        public string getImagePath() { return imgPath; }
        public void setBrushColor(Color c) { bColor = c; }
        public void setBrushColor2(Color c) { bColor2 = c; }
        public MainForm.BrushStyle getBrushStyle() { return bStyle; }
        public void setBrushStyle(MainForm.BrushStyle bStyle) { this.bStyle = bStyle; }
        public void setImagePath(string imgPath) { this.imgPath = imgPath; }
        public MainForm.Mode getMode() { return dMode; }
        public void setMode(MainForm.Mode dMode) { this.dMode = dMode; }
        public abstract void draw(Graphics gHandle);
    }
    class Line : Shape
    {
        
        public Line()
        {
            
        }
        public Line(ArrayList points):base(points)
        {
            
        }
        public override void draw(Graphics gHandle)
        {
            gHandle.DrawLine(getPen(), (Point)getPoints()[0], (Point)getPoints()[1]);
        }
    }
    class Rect : Shape
    {
        public override void draw(Graphics gHandle)
        {
            Point pt1 = (Point)getPoints()[0], pt2 = (Point)getPoints()[1];
            Rectangle nowRect = new Rectangle(pt1.X, pt1.Y, (pt2.X - pt1.X), (pt2.Y - pt1.Y));
            
            if (getMode() == MainForm.Mode.BORDER_LINE)
            {
                gHandle.DrawRectangle(getPen(), nowRect);
            }
            else
            {
                gHandle.FillRectangle(getBrush(), nowRect);
            }
        }
    }
    class Circle : Shape
    {
        public override void draw(Graphics gHandle)
        {
            Point pt1 = (Point)getPoints()[0], pt2 = (Point)getPoints()[1];
            Rectangle nowRect = new Rectangle(pt1.X, pt1.Y, (pt2.X - pt1.X), (pt2.Y - pt1.Y));

            if (getMode() == MainForm.Mode.BORDER_LINE)
            {
                gHandle.DrawEllipse(getPen(), nowRect);
            }
            else
            {
                gHandle.FillEllipse(getBrush(), nowRect);
            }
        }
    }
    class Polygon : Shape
    {
        public Polygon()
        {
            
        }
        public Polygon(ArrayList points):base(points)
        {
            
        }
        public override void draw(Graphics gHandle)
        {
            Point[] arr = (Point[])getPoints().ToArray(typeof(Point));

            if (getMode() == MainForm.Mode.BORDER_LINE)
            {
                gHandle.DrawPolygon(getPen(), arr);
            }
            else
            {
                gHandle.FillPolygon(getBrush(), arr);
            }
        }
    }
    class Text : Shape
    {
        private Font dFont;

        public Text()
        {
            dFont = null;
            
        }
        public Font getFont() { return dFont; }
        public void setFont(Font dFont) { this.dFont = (Font)dFont.Clone(); }

        public override void draw(Graphics gHandle)
        {
            gHandle.DrawString("20141345 최재혁", dFont, getBrush(), (Point)getPoints()[1]);
        }
    }
}
