namespace Assign_3
{
    partial class PenForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.okBtn = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.drawingPanel = new System.Windows.Forms.Panel();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.colorPanel = new System.Windows.Forms.Panel();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.cancelBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(319, 140);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 18);
            this.label1.TabIndex = 0;
            this.label1.Text = "색상";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(319, 189);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 18);
            this.label2.TabIndex = 1;
            this.label2.Text = "두께";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(319, 86);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 18);
            this.label3.TabIndex = 2;
            this.label3.Text = "형태";
            // 
            // okBtn
            // 
            this.okBtn.Location = new System.Drawing.Point(220, 254);
            this.okBtn.Name = "okBtn";
            this.okBtn.Size = new System.Drawing.Size(84, 41);
            this.okBtn.TabIndex = 3;
            this.okBtn.Text = "확인";
            this.okBtn.UseVisualStyleBackColor = true;
            this.okBtn.Click += new System.EventHandler(this.okBtn_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(52, 42);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(62, 18);
            this.label4.TabIndex = 4;
            this.label4.Text = "선예제";
            // 
            // drawingPanel
            // 
            this.drawingPanel.Location = new System.Drawing.Point(55, 95);
            this.drawingPanel.Name = "drawingPanel";
            this.drawingPanel.Size = new System.Drawing.Size(188, 100);
            this.drawingPanel.TabIndex = 5;
            this.drawingPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint_1);
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "Solid",
            "Dot",
            "Dash",
            "DashDot"});
            this.comboBox1.Location = new System.Drawing.Point(393, 83);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(234, 26);
            this.comboBox1.TabIndex = 6;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // colorPanel
            // 
            this.colorPanel.BackColor = System.Drawing.Color.Black;
            this.colorPanel.Location = new System.Drawing.Point(393, 131);
            this.colorPanel.Name = "colorPanel";
            this.colorPanel.Size = new System.Drawing.Size(234, 40);
            this.colorPanel.TabIndex = 7;
            this.colorPanel.Click += new System.EventHandler(this.panel2_Click);
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "1",
            "2",
            "4",
            "8"});
            this.comboBox2.Location = new System.Drawing.Point(393, 189);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(234, 26);
            this.comboBox2.TabIndex = 8;
            this.comboBox2.Text = "4";
            this.comboBox2.SelectedIndexChanged += new System.EventHandler(this.comboBox2_SelectedIndexChanged);
            // 
            // cancelBtn
            // 
            this.cancelBtn.Location = new System.Drawing.Point(322, 254);
            this.cancelBtn.Name = "cancelBtn";
            this.cancelBtn.Size = new System.Drawing.Size(84, 41);
            this.cancelBtn.TabIndex = 9;
            this.cancelBtn.Text = "취소";
            this.cancelBtn.UseVisualStyleBackColor = true;
            this.cancelBtn.Click += new System.EventHandler(this.cancelBtn_Click);
            // 
            // PenForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(661, 307);
            this.Controls.Add(this.cancelBtn);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.colorPanel);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.drawingPanel);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.okBtn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "PenForm";
            this.Text = "PenForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button okBtn;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Panel drawingPanel;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Panel colorPanel;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Button cancelBtn;
    }
}