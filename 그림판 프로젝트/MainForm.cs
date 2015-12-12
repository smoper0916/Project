using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.IO;
using System.Runtime.InteropServices;
using System.Drawing.Drawing2D;

           
namespace Assign_3
{
    public partial class MainForm : Form
    {
        public enum ShapeStyle { NONE, LINE, RECT, CIRCLE, POLYGON, TEXT };
        public enum BrushStyle { NONE, SolidBrush, HatchBrush, LinearGradientBrush, TextureBrush};
        public enum Mode { BORDER_LINE, FILL };
        ArrayList points = new ArrayList();
        ArrayList shapeList = new ArrayList();
        Font dFont = DefaultFont;
        Pen dPen = Pens.Black;
        Brush dBrush = (Brush)Brushes.Black.Clone();
        Color bColor = Color.Black; // 브러쉬 색상
        Color bColor2 = Color.Red; // 2번째 색상
        ShapeStyle s_style= ShapeStyle.LINE; // 기본값
        BrushStyle b_style = BrushStyle.SolidBrush; // 기본값
        Mode m_mode = Mode.BORDER_LINE; // 기본값
        string imgPath="NONE";
        bool isMouseDown = false;
        

        public MainForm()
        {
            InitializeComponent();
            
//            DrawingInfo.font = new Font("맑은 고딕", 12);
            //pcb.Push()
            t_pen_color.Text = dPen.Color.ToString();
            t_brush_color.Text = bColor.ToString();
            t_shape_status.Text = s_style.ToString();


           
        }

        private void 선ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FontDialog f = new FontDialog();
            f.ShowDialog();
            dFont = f.Font;
        }

        private void 색상ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ColorDialog c = new ColorDialog();
            c.ShowDialog();
            dPen.Color = c.Color;
        }

        private void MainForm_MouseDown(object sender, MouseEventArgs e)
        {
            if(s_style != ShapeStyle.POLYGON)
                points.Add(new Point(e.X, e.Y));
            isMouseDown = true;
        }

        private void MainForm_MouseUp(object sender, MouseEventArgs e)
        {
            if (!isMouseDown)
                return;
            Shape newShape = null;

            switch (e.Button)
            {
                case System.Windows.Forms.MouseButtons.Left:

                    points.Add(new Point(e.X, e.Y));
                    switch (s_style)
                    {
                        case ShapeStyle.LINE:
                            newShape = new Line();
                            break;
                        case ShapeStyle.RECT:
                            newShape = new Rect();
                            break;
                        case ShapeStyle.CIRCLE:
                            newShape = new Circle();
                            break;
                        case ShapeStyle.POLYGON:
                            if (points.Count > 19)
                            {
                                MessageBox.Show("20개까지만 점 찍을 수 있습니다.");
                                points.Clear();
                            }
                            return;
                        case ShapeStyle.TEXT:
                            newShape = new Text();
                            ((Text)newShape).setFont(dFont);
                            break;
                    }
                    newShape.addPoint((Point)points[0]);
                    newShape.addPoint((Point)points[1]);

                    newShape.setMode(m_mode);
                    newShape.setBrush(dBrush);
                    newShape.setBrushStyle(b_style);
                    newShape.setImagePath(imgPath);
                    newShape.setBrushColor(bColor);
                    newShape.setBrushColor2(bColor2);
                    newShape.setPen(dPen);
                    shapeList.Add(newShape);
                    Invalidate();
                    points.Clear();
                    break;

                case System.Windows.Forms.MouseButtons.Right:
                    if (s_style == ShapeStyle.POLYGON)
                    {
                        points.Add(new Point(e.X, e.Y));
                        newShape = new Polygon(points);
                        newShape.setMode(m_mode);

                        newShape.setBrush(dBrush);
                        newShape.setBrushStyle(b_style);
                        newShape.setImagePath(imgPath);
                        newShape.setBrushColor(bColor);
                        newShape.setBrushColor2(bColor2);
                        newShape.setPen(dPen);
                        shapeList.Add(newShape);
                        Invalidate();
                        points.Clear();
                    }
                    break;
            }
            isMouseDown = false;
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {

            for(int i=0; i<shapeList.Count; i++)
            {
                ((Shape)shapeList[i]).draw(e.Graphics);
            }

        }
        private void choiceMode(object sender, EventArgs e)
        {
            string tag = "";
            if(sender is ToolStripMenuItem)
            {
                tag = (string)((ToolStripMenuItem)sender).Tag; 
            }
            else
            {
                tag = (string)((ToolStripButton)sender).Tag;
            }

            if(tag == "borderline")
            {
                m_mode = Mode.BORDER_LINE;
                윤곽선ToolStripMenuItem.Checked = true;
                채움ToolStripMenuItem.Checked = false;
            }
            else
            {
                m_mode = Mode.FILL;
                윤곽선ToolStripMenuItem.Checked = false;
                채움ToolStripMenuItem.Checked = true;
            }
        }
        private void choiceShapeStyle(object sender, EventArgs e)
        {
            string tag = "";
            if (sender is ToolStripMenuItem)
            {
                tag = (string)((ToolStripMenuItem)sender).Tag;
            }
            else
            {
                tag = (string)((ToolStripButton)sender).Tag;
            }

            switch(tag)
            {
                case "line":
                    s_style = ShapeStyle.LINE;

                    선ToolStripMenuItem.Checked = true;
                    사각형ToolStripMenuItem.Checked = false;
                    원ToolStripMenuItem.Checked = false;
                    다각형ToolStripMenuItem.Checked = false;
                    글자ToolStripMenuItem.Checked = false;
                    break;
                case "rect":
                    s_style = ShapeStyle.RECT;

                    사각형ToolStripMenuItem.Checked = true;
                    선ToolStripMenuItem1.Checked = false;
                    원ToolStripMenuItem.Checked = false;
                    다각형ToolStripMenuItem.Checked = false;
                    글자ToolStripMenuItem.Checked = false;
                    break;
                case "circle":
                    s_style = ShapeStyle.CIRCLE;

                    원ToolStripMenuItem.Checked = true;
                    선ToolStripMenuItem1.Checked = false;
                    사각형ToolStripMenuItem.Checked = false;
                    다각형ToolStripMenuItem.Checked = false;
                    글자ToolStripMenuItem.Checked = false;
                    break;
                case "polygon":
                    s_style = ShapeStyle.POLYGON;

                    다각형ToolStripMenuItem.Checked = true;
                    선ToolStripMenuItem1.Checked = false;
                    사각형ToolStripMenuItem.Checked = false;
                    원ToolStripMenuItem.Checked = false;
                    글자ToolStripMenuItem.Checked = false;
                    break;
                case "text":
                    s_style = ShapeStyle.TEXT;

                    글자ToolStripMenuItem.Checked = true;
                    선ToolStripMenuItem1.Checked = false;
                    사각형ToolStripMenuItem.Checked = false;
                    원ToolStripMenuItem.Checked = false;
                    다각형ToolStripMenuItem.Checked = false;
                    break;
            }
            t_shape_status.Text = s_style.ToString();
        }

        private void 펜ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PenForm pForm = new PenForm(dPen);
            if (pForm.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                dPen = pForm.selectedPen;
                t_pen_color.Text = dPen.Color.ToString();
            }
        }

        private void 브러ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BrushForm bForm = new BrushForm(dBrush, b_style, bColor, bColor2);
            if (bForm.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                dBrush = bForm.selectedBrush;
                bColor = bForm.bColor;
                bColor2 = bForm.bColor2;
                b_style = bForm.selectedBrushStyle;
                t_brush_color.Text = bColor.ToString() + ", Brush2 " + bColor2.ToString();
                imgPath = bForm.imgPath;
            }
        }

        private void undoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (shapeList.Count - 1 >= 0)
            {
                shapeList.RemoveAt(shapeList.Count - 1);
                Invalidate();
            }
            
        }

        private void 모두삭제ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            shapeList.Clear();
            Invalidate();
        }

        private void MainForm_MouseMove(object sender, MouseEventArgs e)
        {
            t_mouse_status.Text = "X : " + e.X + " Y : " + e.Y;
        }

        private void 종료ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }


        public void save(string fileName)
        {
            int count = shapeList.Count;
            StreamWriter sw = new StreamWriter(fileName);
            if (count == 0)
                sw.Write("");

            Shape nowShape = null;
            for (int i = 0; i < count; i++)
            {
                nowShape = (Shape)shapeList[i];
                string shapeName = "";
                if (nowShape is Line)
                    shapeName = "Line";
                else if (nowShape is Rect)
                    shapeName = "Rect";
                else if (nowShape is Circle)
                    shapeName = "Circle";
                else if (nowShape is Polygon)
                    shapeName = "Polygon";
                else
                    shapeName = "Text";
                sw.Write(shapeName);

                ArrayList points = nowShape.getPoints();
                Pen sPen = nowShape.getPen();
                
                switch(shapeName){
                    case "Line":

                        sw.Write("," + sPen.Color.R.ToString());
                        sw.Write("," + sPen.Color.G.ToString());
                        sw.Write("," + sPen.Color.B.ToString());
                        sw.Write("," + sPen.DashStyle.ToString());
                        sw.Write("," + sPen.Width);
                        break;
                    case "Text":
                        sw.Write("," + nowShape.getBrushStyle().ToString());
                        sw.Write("," + nowShape.getBrushColor().R.ToString());
                        sw.Write("," + nowShape.getBrushColor().G.ToString());
                        sw.Write("," + nowShape.getBrushColor().B.ToString());
                        sw.Write("," + nowShape.getBrushColor2().R.ToString());
                        sw.Write("," + nowShape.getBrushColor2().G.ToString());
                        sw.Write("," + nowShape.getBrushColor2().B.ToString());
                        sw.Write("," + nowShape.getImagePath());

                        Font nowFont = ((Text)nowShape).getFont();
                        sw.Write("," + nowFont.Name);
                        sw.Write("," + nowFont.Size);
                       
                        sw.Write("," + nowFont.Style.ToString()); // 폰트 속성. 0이 나오면 속성 끝
                        sw.Write("," + "0");
                        break;

                    case "Rect":
                    case "Circle":
                    case "Polygon":
                        sw.Write("," + nowShape.getMode().ToString());
                        sw.Write("," + sPen.Color.R.ToString());
                        sw.Write("," + sPen.Color.G.ToString());
                        sw.Write("," + sPen.Color.B.ToString());
                        sw.Write("," + sPen.DashStyle.ToString());
                        sw.Write("," + sPen.Width);
                        sw.Write("," + nowShape.getBrushStyle().ToString());
                        sw.Write("," + nowShape.getBrushColor().R.ToString());
                        sw.Write("," + nowShape.getBrushColor().G.ToString());
                        sw.Write("," + nowShape.getBrushColor().B.ToString());
                        sw.Write("," + nowShape.getBrushColor2().R.ToString());
                        sw.Write("," + nowShape.getBrushColor2().G.ToString());
                        sw.Write("," + nowShape.getBrushColor2().B.ToString());
                        sw.Write("," + nowShape.getImagePath());
                        break;

                }
                for (int j = 0; j < points.Count; j++)
                {
                    sw.Write("," + ((Point)points[j]).X);
                    sw.Write("," + ((Point)points[j]).Y);
                }
                sw.WriteLine("");
            }

            sw.Close();
        }
        public void read(string fileName)
        {
            FileInfo FI = new FileInfo(@fileName);
            if (FI.Exists)
            {
                StreamReader sr = new StreamReader(fileName);
                while (sr.Peek() >= 0)
                {
                    string[] arr = sr.ReadLine().Split(',');
                    ArrayList points = new ArrayList();
                    Color brushColor1, brushColor2;
                    switch (arr[0])
                    {
                        case "Line":
                            // Pen Color, Pen DashStyle, Pen Width
                            Color lineColor = Color.FromArgb(int.Parse(arr[1]), int.Parse(arr[2]), int.Parse(arr[3]));
                            Pen p = (Pen)Pens.Black.Clone();
                            if (arr[4] == System.Drawing.Drawing2D.DashStyle.Dash.ToString())
                                p.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                            else if (arr[4] == System.Drawing.Drawing2D.DashStyle.DashDot.ToString())
                                p.DashStyle = System.Drawing.Drawing2D.DashStyle.DashDot;
                            else if (arr[4] == System.Drawing.Drawing2D.DashStyle.Dot.ToString())
                                p.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;
                            else
                                p.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
                            p.Width = float.Parse(arr[5]);
                            p.Color = lineColor;
                            Line newLine = new Line();
                            newLine.setPen(p);

                            
                            for (int i = 6; i < arr.Length; i+=2)
                            {
                                newLine.addPoint(new Point(int.Parse(arr[i]), int.Parse(arr[i + 1])));
                            }
                            shapeList.Add(newLine);
                            break;
                        case "Text":
                            // Brush Style, Brush Color, Brush Color2, imgPath, Font Name, Font Size, Font Style
                            Text t = new Text();
                            Brush tBrush = (Brush)Brushes.Black.Clone();
                            BrushStyle tBrushStyle = BrushStyle.SolidBrush;

                            brushColor1 = Color.FromArgb(int.Parse(arr[2]), int.Parse(arr[3]), int.Parse(arr[4]));
                            brushColor2 = Color.FromArgb(int.Parse(arr[5]), int.Parse(arr[6]), int.Parse(arr[7]));

                            if (arr[1] == BrushStyle.SolidBrush.ToString())
                            {
                                tBrush = new SolidBrush(brushColor1);
                                tBrushStyle = BrushStyle.SolidBrush;
                            }
                            else if (arr[1] == BrushStyle.HatchBrush.ToString())
                            {
                                tBrush = new HatchBrush(HatchStyle.Vertical, brushColor1, brushColor2);
                                tBrushStyle = BrushStyle.HatchBrush;
                            }
                            else if (arr[1] == BrushStyle.LinearGradientBrush.ToString())
                            {
                                tBrush = new LinearGradientBrush(new Rectangle(10, 100 / 2, 188, 100 / 2), brushColor1, brushColor2, LinearGradientMode.Horizontal);
                                tBrushStyle = BrushStyle.LinearGradientBrush;
                            }
                            else
                            {
                                if (arr[8] != "NONE")
                                {
                                    tBrush = new TextureBrush(Image.FromFile(arr[8]));
                                    tBrushStyle = BrushStyle.TextureBrush;
                                    t.setImagePath(arr[8]);
                                }
                            }
  

                            string t_fontName = arr[9], t_fontSize = arr[10];

                            FontStyle fs = FontStyle.Regular;

                            //bool isBold=false, isItalic=false, isStikeOut=false, isUnderLine=false;
                            int lastIndex = 11;

                            String[] fontStr = new String[5];

                            int index = 0;

                            while (arr[lastIndex] != "0")
                            {
                                fontStr[index++] = arr[lastIndex++].Trim();

                                /*if (arr[lastIndex] == "Bold")
                                    isBold = true;
                                else if (arr[lastIndex] == "Italic")
                                    isItalic = true;
                                else if (arr[lastIndex] == "Strikeout")
                                    isStikeOut = true;
                                lastIndex++;*/
                            }
                            
                            for(int i = 0;i<index;i++)
                            {
                                switch(fontStr[i])
                                {
                                    case "Bold":
                                        fs = fs | FontStyle.Bold;
                                        break;
                                    case "Italic":
                                        fs = fs | FontStyle.Italic;
                                        break;
                                    case "Strikeout":
                                        fs = fs | FontStyle.Strikeout;
                                        break;
                                    case "Underline":
                                        fs = fs | FontStyle.Underline;
                                        break;
                                }
                            }
                            /*
                            if (!isBold && !isItalic)
                                fs = FontStyle.Regular;
                            else if (isBold && isItalic)
                                fs = FontStyle.Bold | FontStyle.Italic;
                            else if (isBold)
                                fs = FontStyle.Bold;
                            else
                                fs = FontStyle.Italic;

                            if (isStikeOut)
                                fs = fs|FontStyle.Strikeout;
                            else if (isUnderLine)
                                fs = fs|FontStyle.Underline;
                            */
                            Font tFont = new Font(t_fontName, float.Parse(t_fontSize), fs);

                            for (int i = lastIndex+1; i < arr.Length; i+=2)
                            {
                                t.addPoint(new Point(int.Parse(arr[i]), int.Parse(arr[i + 1])));
                            }
                            t.setFont(tFont);
                            t.setBrush(tBrush);
                            t.setBrushColor(brushColor1);
                            t.setBrushColor2(brushColor2);
                            t.setBrushStyle(tBrushStyle);
                            shapeList.Add(t);
                            break;

                        case "Rect":
                        case "Circle":
                        case "Polygon":
                            // Mode, Pen Color, Pen DashStyle, Pen Width,  Brush Style, Brush Color, Brush Color2, imgPath
                            Shape s;
                            if(arr[0] == "Rect")
                                s = new Rect();
                            else if(arr[0] == "Circle")
                                s = new Circle();
                            else
                                s = new Polygon();

                            Mode m;
                            if (arr[1] == "FILL")
                                m = Mode.FILL;
                            else
                                m = Mode.BORDER_LINE;

                            Color anColor = Color.FromArgb(int.Parse(arr[2]), int.Parse(arr[3]), int.Parse(arr[4]));
                            Pen sPen = (Pen)Pens.Black.Clone();
                            Brush bBrush = (Brush)Brushes.Black.Clone();
                            BrushStyle tmpBrushStyle = BrushStyle.SolidBrush;
                            if (arr[5] == System.Drawing.Drawing2D.DashStyle.Dash.ToString())
                                sPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                            else if (arr[5] == System.Drawing.Drawing2D.DashStyle.DashDot.ToString())
                                sPen.DashStyle = System.Drawing.Drawing2D.DashStyle.DashDot;
                            else if (arr[5] == System.Drawing.Drawing2D.DashStyle.Dot.ToString())
                                sPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;
                            else
                                sPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
                            sPen.Color = anColor;
                            sPen.Width = float.Parse(arr[6]);

                            brushColor1 = Color.FromArgb(int.Parse(arr[8]), int.Parse(arr[9]), int.Parse(arr[10]));
                            brushColor2 = Color.FromArgb(int.Parse(arr[11]), int.Parse(arr[12]), int.Parse(arr[13]));

                            if (arr[7] == BrushStyle.SolidBrush.ToString()){
                                bBrush = new SolidBrush(brushColor1);
                                tmpBrushStyle = BrushStyle.SolidBrush;
                            }
                            else if (arr[7] == BrushStyle.HatchBrush.ToString()){
                                bBrush = new HatchBrush(HatchStyle.Vertical, brushColor1, brushColor2);
                                tmpBrushStyle = BrushStyle.HatchBrush;
                            }
                            else if (arr[7] == BrushStyle.LinearGradientBrush.ToString()){
                                bBrush = new LinearGradientBrush(new Rectangle(10, 100 / 2, 188, 100 / 2), brushColor1, brushColor2, LinearGradientMode.Horizontal);
                                tmpBrushStyle = BrushStyle.LinearGradientBrush;
                            }
                            else {
                                if (arr[14] != "NONE")
                                {
                                    bBrush = new TextureBrush(Image.FromFile(arr[14]));
                                    tmpBrushStyle = BrushStyle.TextureBrush;
                                    s.setImagePath(arr[14]);
                                }
                            }
                            s.setMode(m);
                            s.setPen(sPen);
                            s.setBrush(bBrush);
                            s.setBrushColor(brushColor1);
                            s.setBrushColor2(brushColor2);
                            s.setBrushStyle(tmpBrushStyle);
                            

                            for (int i = 15; i < arr.Length; i+=2)
                            {
                                s.addPoint(new Point(int.Parse(arr[i]), int.Parse(arr[i + 1])));
                            }
                            shapeList.Add(s);
                            break;

                    }
                }
                sr.Close();
            }
        }

        private void 저장ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sDialog = new SaveFileDialog();
            sDialog.InitialDirectory = "c:\\";
            // Filter에서 Or 기호는 2개씩 페어링 됨. txt파일 | 모든 파일
            sDialog.Filter = "csv file(*.csv)|*.csv|txt file(*.txt)|*.txt";
            sDialog.FilterIndex = 1;
            sDialog.RestoreDirectory = true;

            if (sDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                save(sDialog.FileName);
            }
        }

        private void 읽기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog of = new OpenFileDialog();
            of.InitialDirectory = "c:\\";
            // Filter에서 Or 기호는 2개씩 페어링 됨. txt파일 | 모든 파일
            of.Filter = "csv file(*.csv)|*.csv|txt file(*.txt)|*.txt";
            of.FilterIndex = 1;
            of.RestoreDirectory = true;

            if (of.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                shapeList.Clear();
                points.Clear();
                read(of.FileName);
                Invalidate();
            }
        }

        private void 인쇄ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (printDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                CaptureScreen();
                printDocument1.Print();
            }
        }
        //Print Code
        [System.Runtime.InteropServices.DllImport("gdi32.dll")]
        public static extern long BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight,
            IntPtr hdcSrc, int nXSrc, int nYSrc, int dwRop);

        private Bitmap memoryImage;
        private void CaptureScreen() //Capture Screen
        {
            Graphics mygraphics = this.CreateGraphics(); //this Form's Graphics
            Size s = this.Size; //this's Form Size
            memoryImage = new Bitmap(s.Width, s.Height, mygraphics); //Screen Graphics -> Bitmap
            Graphics memoryGraphics = Graphics.FromImage(memoryImage); //Bitmap -> Graphics
            IntPtr dc1 = mygraphics.GetHdc(); //Get Handler related Graphics
            IntPtr dc2 = memoryGraphics.GetHdc();
            BitBlt(dc2, 0, 0, this.ClientRectangle.Width, this.ClientRectangle.Height, dc1, 0, 0, 13369376);
            mygraphics.ReleaseHdc(dc1);
            memoryGraphics.ReleaseHdc(dc2);
        }

        private void printDocument1_PrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            e.Graphics.DrawImage(memoryImage, 0, 0);
        } // 화면을 캡쳐한 뒤에

    }
}