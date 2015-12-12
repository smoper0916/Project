using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace Assign_3
{
    public partial class BrushForm : Form
    {
        public Brush selectedBrush;
        public MainForm.BrushStyle selectedBrushStyle;
        public Color bColor, bColor2;
        public Image img = null;
        public string imgPath="";

        public BrushForm(Brush dBrush, MainForm.BrushStyle dBrushStyle, Color bColor, Color bColor2)
        {
            InitializeComponent();
            this.bColor = bColor;
            this.bColor2 = bColor2;
            selectedBrush = (Brush)dBrush.Clone();
            colorPanel.BackColor = bColor;
            color1_Panel.BackColor = bColor;
            color2_Panel.BackColor = bColor2;
            switch (dBrushStyle)
            {
                case MainForm.BrushStyle.NONE:
                    comboBox1.Text = "None";
                    break;

                case MainForm.BrushStyle.HatchBrush:
                    comboBox1.Text = "HatchBrush";
                    switchingPanel(twoColor_Panel, img_Panel, oneColor_Panel);
                    
                    previewLabel.Text = "사각형예제";
                    turnOnPanel(drawingPanel);
                    turnOffPanel(imageView);
                    break;

                case MainForm.BrushStyle.LinearGradientBrush:
                    comboBox1.Text = "LinearGradientBrush";
                    switchingPanel(twoColor_Panel, img_Panel, oneColor_Panel);
                    
                    previewLabel.Text = "사각형예제";
                    turnOnPanel(drawingPanel);
                    turnOffPanel(imageView);
                    break;

                case MainForm.BrushStyle.SolidBrush:
                    comboBox1.Text = "SolidBrush";
                    switchingPanel(oneColor_Panel, img_Panel, twoColor_Panel);
                    
                    previewLabel.Text = "사각형예제";
                    turnOnPanel(drawingPanel);
                    turnOffPanel(imageView);
                    break;
                case MainForm.BrushStyle.TextureBrush:
                    comboBox1.Text = "TextureBrush";
                    switchingPanel(img_Panel, oneColor_Panel, twoColor_Panel);

                    previewLabel.Text = "그림 미리보기";
                    turnOnPanel(imageView);
                    turnOffPanel(drawingPanel);
                    break;
            }
            selectedBrushStyle = dBrushStyle;
        }
        private void turnOnPanel(Panel p)
        {
            p.Enabled = true;
            p.Visible = true;
        }
        private void turnOffPanel(Panel p)
        {
            p.Enabled = false;
            p.Visible = false;
        }
        private void switchingPanel(Panel main, Panel sub, Panel sub2)
        {
            turnOnPanel(main);
            turnOffPanel(sub);
            turnOffPanel(sub2);

        }

        private void cancelBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void okBtn_Click(object sender, EventArgs e)
        {
            if (img != null && selectedBrushStyle == MainForm.BrushStyle.TextureBrush)
                selectedBrush = new TextureBrush(img);

            this.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Close();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBox1.Text)
            {
                case "None":
                    comboBox1.Text = "None";
                    selectedBrushStyle = MainForm.BrushStyle.NONE;
                    break;

                case "HatchBrush":
                    selectedBrush = new HatchBrush(HatchStyle.Vertical, bColor, bColor2);
                    selectedBrushStyle = MainForm.BrushStyle.HatchBrush;
                    
                    switchingPanel(twoColor_Panel, img_Panel, oneColor_Panel);
                    
                    previewLabel.Text = "선예제";
                    turnOnPanel(drawingPanel);
                    turnOffPanel(imageView);
                    break;

                case "LinearGradientBrush":
                    Rectangle nowRect = new Rectangle(10, drawingPanel.Height / 2, drawingPanel.Width, drawingPanel.Height / 2);
                    comboBox1.Text = "LinearGradientBrush";
                    selectedBrush = new LinearGradientBrush(nowRect, bColor, bColor2, LinearGradientMode.Horizontal);
                    selectedBrushStyle = MainForm.BrushStyle.LinearGradientBrush;

                    switchingPanel(twoColor_Panel, img_Panel, oneColor_Panel);
                    
                    previewLabel.Text = "선예제";
                    turnOnPanel(drawingPanel);
                    turnOffPanel(imageView);
                    break;

                case "SolidBrush":
                    comboBox1.Text = "SolidBrush";
                    selectedBrushStyle = MainForm.BrushStyle.SolidBrush;
                    selectedBrush = new SolidBrush(bColor);

                    switchingPanel(oneColor_Panel, img_Panel, twoColor_Panel);
                    
                    previewLabel.Text = "선예제";
                    turnOnPanel(drawingPanel);
                    turnOffPanel(imageView);
                    break;
                case "TextureBrush":
                    comboBox1.Text = "TextureBrush";
                    selectedBrushStyle = MainForm.BrushStyle.TextureBrush;
                    if(img != null)
                        selectedBrush = new TextureBrush(img);
                    switchingPanel(img_Panel, oneColor_Panel, twoColor_Panel);

                    previewLabel.Text = "그림 미리보기";
                    turnOnPanel(imageView);
                    turnOffPanel(drawingPanel);
                    imageView.Invalidate();
                    return;
            }
            drawingPanel.Invalidate();
        }

        private void drawingPanel_Paint(object sender, PaintEventArgs e)
        {
            Graphics gHandle = drawingPanel.CreateGraphics();

            switch (selectedBrushStyle)
            {
                case MainForm.BrushStyle.HatchBrush:
                    selectedBrush = new HatchBrush(HatchStyle.Vertical, bColor, bColor2);
                    break;

                case MainForm.BrushStyle.LinearGradientBrush:
                    Rectangle nowRect = new Rectangle(10, drawingPanel.Height / 2, drawingPanel.Width, drawingPanel.Height / 2);
                    selectedBrush = new LinearGradientBrush(nowRect, bColor, bColor2, LinearGradientMode.Horizontal);
                    break;

                case MainForm.BrushStyle.SolidBrush:
                    selectedBrush = new SolidBrush(bColor);
                    break;
            }
            gHandle.FillRectangle(selectedBrush, 10, drawingPanel.Height / 2, drawingPanel.Width, drawingPanel.Height / 2+10);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog of = new OpenFileDialog();
            of.InitialDirectory = "c:\\";
            // Filter에서 Or 기호는 2개씩 페어링 됨. txt파일 | 모든 파일
            of.Filter = "img files (*.png, *.jpg, *.bmp, *.gif)|*.png;*.jpg;*.bmp;*.gif";
            of.FilterIndex = 1;
            of.RestoreDirectory = true;

            if(of.ShowDialog() == System.Windows.Forms.DialogResult.OK){
                img = Image.FromFile(of.FileName);
                imgPath = of.FileName;
                imageView.Invalidate();
            }
        }

        private void BrushForm_Load(object sender, EventArgs e)
        {

        }

        private void color1_Panel_Click(object sender, EventArgs e)
        {
            ColorDialog cDialog = new ColorDialog();
            if (cDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                bColor = cDialog.Color;
                color1_Panel.BackColor = bColor;
                drawingPanel.Invalidate();
            }
        }

        private void color2_Panel_Click(object sender, EventArgs e)
        {
            ColorDialog cDialog = new ColorDialog();
            if (cDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                bColor2 = cDialog.Color;
                color2_Panel.BackColor = bColor2;
                drawingPanel.Invalidate();
            }
        }

        private void colorPanel_Click(object sender, EventArgs e)
        {
            ColorDialog cDialog = new ColorDialog();
            if (cDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                bColor = cDialog.Color;
                colorPanel.BackColor = bColor;
                drawingPanel.Invalidate();
            }
        }

        private void imageView_Paint(object sender, PaintEventArgs e)
        {
            Graphics gHandle = e.Graphics;
            if(img != null)
                gHandle.DrawImage(img, 0, 0, imageView.Width, imageView.Height);
        }
    }
}
