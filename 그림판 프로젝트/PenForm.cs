using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Assign_3
{
    public partial class PenForm : Form
    {
        public Pen selectedPen;
        

        public PenForm(Pen dPen)
        {
            InitializeComponent();
            selectedPen = (Pen)dPen.Clone();
            colorPanel.BackColor = dPen.Color;
            comboBox2.Text = ""+dPen.Width;
            switch(dPen.DashStyle)
            {
                case System.Drawing.Drawing2D.DashStyle.Dash:
                    comboBox1.Text = "Dash";
                    break;

                case System.Drawing.Drawing2D.DashStyle.DashDot:
                    comboBox1.Text = "DashDot";
                    break;

                case System.Drawing.Drawing2D.DashStyle.Dot:
                    comboBox1.Text = "Dot";
                    break;

                case System.Drawing.Drawing2D.DashStyle.Solid:
                    comboBox1.Text = "Solid";
                    break;
            }

        }

        private void panel1_Paint_1(object sender, PaintEventArgs e)
        {
            Graphics gHandle = drawingPanel.CreateGraphics();
            gHandle.DrawLine(selectedPen, 10, drawingPanel.Height/2, drawingPanel.Width,drawingPanel.Height/2);
            
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (((ComboBox)sender).Text)
            {
                case "Solid":
                    selectedPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
                    break;
                case "Dot":
                    selectedPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;
                    break;
                case "Dash":
                    selectedPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                    break;
                case "DashDot":
                    selectedPen.DashStyle = System.Drawing.Drawing2D.DashStyle.DashDot;
                    break;
            }
            drawingPanel.Invalidate();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectedPen.Width = Convert.ToInt32(((ComboBox)sender).Text);
            drawingPanel.Invalidate();
        }

        private void panel2_Click(object sender, EventArgs e)
        {
            ColorDialog cDialog = new ColorDialog();
            if(cDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                selectedPen.Color = cDialog.Color;
                colorPanel.BackColor = cDialog.Color;
                drawingPanel.Invalidate();
            }
        }

        private void okBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Close();
        }

        private void cancelBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }
    }
}
