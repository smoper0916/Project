namespace Assign_3
{
    partial class BrushForm
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
            this.cancelBtn = new System.Windows.Forms.Button();
            this.colorPanel = new System.Windows.Forms.Panel();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.drawingPanel = new System.Windows.Forms.Panel();
            this.previewLabel = new System.Windows.Forms.Label();
            this.okBtn = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.oneColor_Panel = new System.Windows.Forms.Panel();
            this.img_Panel = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.twoColor_Panel = new System.Windows.Forms.Panel();
            this.label5 = new System.Windows.Forms.Label();
            this.color2_Panel = new System.Windows.Forms.Panel();
            this.color1_Panel = new System.Windows.Forms.Panel();
            this.imageView = new System.Windows.Forms.Panel();
            this.oneColor_Panel.SuspendLayout();
            this.img_Panel.SuspendLayout();
            this.twoColor_Panel.SuspendLayout();
            this.SuspendLayout();
            // 
            // cancelBtn
            // 
            this.cancelBtn.Location = new System.Drawing.Point(314, 316);
            this.cancelBtn.Name = "cancelBtn";
            this.cancelBtn.Size = new System.Drawing.Size(84, 41);
            this.cancelBtn.TabIndex = 19;
            this.cancelBtn.Text = "취소";
            this.cancelBtn.UseVisualStyleBackColor = true;
            this.cancelBtn.Click += new System.EventHandler(this.cancelBtn_Click);
            // 
            // colorPanel
            // 
            this.colorPanel.BackColor = System.Drawing.Color.Black;
            this.colorPanel.Location = new System.Drawing.Point(95, 3);
            this.colorPanel.Name = "colorPanel";
            this.colorPanel.Size = new System.Drawing.Size(234, 40);
            this.colorPanel.TabIndex = 17;
            this.colorPanel.Click += new System.EventHandler(this.colorPanel_Click);
            // 
            // comboBox1
            // 
            this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "SolidBrush",
            "HatchBrush",
            "LinearGradientBrush",
            "TextureBrush"});
            this.comboBox1.Location = new System.Drawing.Point(385, 89);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(234, 26);
            this.comboBox1.TabIndex = 16;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // drawingPanel
            // 
            this.drawingPanel.Location = new System.Drawing.Point(47, 105);
            this.drawingPanel.Name = "drawingPanel";
            this.drawingPanel.Size = new System.Drawing.Size(188, 100);
            this.drawingPanel.TabIndex = 15;
            this.drawingPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.drawingPanel_Paint);
            // 
            // previewLabel
            // 
            this.previewLabel.AutoSize = true;
            this.previewLabel.Location = new System.Drawing.Point(44, 52);
            this.previewLabel.Name = "previewLabel";
            this.previewLabel.Size = new System.Drawing.Size(98, 18);
            this.previewLabel.TabIndex = 14;
            this.previewLabel.Text = "사각형예제";
            // 
            // okBtn
            // 
            this.okBtn.Location = new System.Drawing.Point(212, 316);
            this.okBtn.Name = "okBtn";
            this.okBtn.Size = new System.Drawing.Size(84, 41);
            this.okBtn.TabIndex = 13;
            this.okBtn.Text = "확인";
            this.okBtn.UseVisualStyleBackColor = true;
            this.okBtn.Click += new System.EventHandler(this.okBtn_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(311, 92);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 18);
            this.label3.TabIndex = 12;
            this.label3.Text = "형태";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 18);
            this.label1.TabIndex = 10;
            this.label1.Text = "색상";
            // 
            // oneColor_Panel
            // 
            this.oneColor_Panel.Controls.Add(this.colorPanel);
            this.oneColor_Panel.Controls.Add(this.label1);
            this.oneColor_Panel.Location = new System.Drawing.Point(293, 121);
            this.oneColor_Panel.Name = "oneColor_Panel";
            this.oneColor_Panel.Size = new System.Drawing.Size(338, 59);
            this.oneColor_Panel.TabIndex = 20;
            // 
            // img_Panel
            // 
            this.img_Panel.Controls.Add(this.button1);
            this.img_Panel.Controls.Add(this.label2);
            this.img_Panel.Location = new System.Drawing.Point(301, 118);
            this.img_Panel.Name = "img_Panel";
            this.img_Panel.Size = new System.Drawing.Size(329, 64);
            this.img_Panel.TabIndex = 21;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(86, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(231, 44);
            this.button1.TabIndex = 1;
            this.button1.Text = "찾아보기";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 17);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 18);
            this.label2.TabIndex = 0;
            this.label2.Text = "이미지";
            // 
            // twoColor_Panel
            // 
            this.twoColor_Panel.Controls.Add(this.label5);
            this.twoColor_Panel.Controls.Add(this.color2_Panel);
            this.twoColor_Panel.Controls.Add(this.color1_Panel);
            this.twoColor_Panel.Location = new System.Drawing.Point(286, 121);
            this.twoColor_Panel.Name = "twoColor_Panel";
            this.twoColor_Panel.Size = new System.Drawing.Size(338, 59);
            this.twoColor_Panel.TabIndex = 22;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(24, 12);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 18);
            this.label5.TabIndex = 23;
            this.label5.Text = "색상";
            // 
            // color2_Panel
            // 
            this.color2_Panel.BackColor = System.Drawing.Color.Black;
            this.color2_Panel.Location = new System.Drawing.Point(221, 3);
            this.color2_Panel.Name = "color2_Panel";
            this.color2_Panel.Size = new System.Drawing.Size(108, 40);
            this.color2_Panel.TabIndex = 19;
            this.color2_Panel.Click += new System.EventHandler(this.color2_Panel_Click);
            // 
            // color1_Panel
            // 
            this.color1_Panel.BackColor = System.Drawing.Color.Black;
            this.color1_Panel.Location = new System.Drawing.Point(95, 3);
            this.color1_Panel.Name = "color1_Panel";
            this.color1_Panel.Size = new System.Drawing.Size(110, 40);
            this.color1_Panel.TabIndex = 18;
            this.color1_Panel.Click += new System.EventHandler(this.color1_Panel_Click);
            // 
            // imageView
            // 
            this.imageView.Location = new System.Drawing.Point(25, 89);
            this.imageView.Name = "imageView";
            this.imageView.Size = new System.Drawing.Size(255, 197);
            this.imageView.TabIndex = 16;
            this.imageView.Paint += new System.Windows.Forms.PaintEventHandler(this.imageView_Paint);
            // 
            // BrushForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(634, 369);
            this.Controls.Add(this.twoColor_Panel);
            this.Controls.Add(this.imageView);
            this.Controls.Add(this.img_Panel);
            this.Controls.Add(this.oneColor_Panel);
            this.Controls.Add(this.cancelBtn);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.drawingPanel);
            this.Controls.Add(this.previewLabel);
            this.Controls.Add(this.okBtn);
            this.Controls.Add(this.label3);
            this.Name = "BrushForm";
            this.Text = "BrushForm";
            this.Load += new System.EventHandler(this.BrushForm_Load);
            this.oneColor_Panel.ResumeLayout(false);
            this.oneColor_Panel.PerformLayout();
            this.img_Panel.ResumeLayout(false);
            this.img_Panel.PerformLayout();
            this.twoColor_Panel.ResumeLayout(false);
            this.twoColor_Panel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cancelBtn;
        private System.Windows.Forms.Panel colorPanel;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Panel drawingPanel;
        private System.Windows.Forms.Label previewLabel;
        private System.Windows.Forms.Button okBtn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel oneColor_Panel;
        private System.Windows.Forms.Panel img_Panel;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel twoColor_Panel;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Panel color2_Panel;
        private System.Windows.Forms.Panel color1_Panel;
        private System.Windows.Forms.Panel imageView;
    }
}