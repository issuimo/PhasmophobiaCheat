namespace Inject___launcher {
    partial class Form1 {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.button1 = new Button();
            this.textBox1 = new TextBox();
            this.label1 = new Label();
            this.button2 = new Button();
            this.checkBox1 = new CheckBox();
            this.linkLabel1 = new LinkLabel();
            this.listBox1 = new ListBox();
            this.button3 = new Button();
            SuspendLayout();
            // 
            // button1
            // 
            this.button1.BackColor = Color.Turquoise;
            this.button1.FlatAppearance.BorderColor = Color.Turquoise;
            this.button1.FlatStyle = FlatStyle.Flat;
            this.button1.Font = new Font("SDK_SC_Web", 10.4999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.button1.Location = new Point(112, 333);
            this.button1.Name = "button1";
            this.button1.Size = new Size(80, 39);
            this.button1.TabIndex = 0;
            this.button1.Text = "启动";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += button1_Click;
            // 
            // textBox1
            // 
            this.textBox1.Font = new Font("SDK_SC_Web", 8.999999F);
            this.textBox1.Location = new Point(12, 32);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new Size(210, 22);
            this.textBox1.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new Font("SDK_SC_Web", 11.9999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.label1.Location = new Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new Size(41, 20);
            this.label1.TabIndex = 2;
            this.label1.Text = "路径";
            // 
            // button2
            // 
            this.button2.BackColor = Color.Turquoise;
            this.button2.FlatAppearance.BorderColor = Color.Turquoise;
            this.button2.FlatStyle = FlatStyle.Flat;
            this.button2.Font = new Font("SDK_SC_Web", 8.999999F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.button2.Location = new Point(228, 31);
            this.button2.Name = "button2";
            this.button2.Size = new Size(50, 24);
            this.button2.TabIndex = 3;
            this.button2.Text = "选择";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += button2_Click;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Font = new Font("SDK_SC_Web", 10.4999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.checkBox1.Location = new Point(12, 60);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new Size(111, 21);
            this.checkBox1.TabIndex = 5;
            this.checkBox1.Text = "剔除进程检测";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.Font = new Font("SDK_SC_Web", 10.4999981F);
            this.linkLabel1.Location = new Point(12, 352);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new Size(89, 17);
            this.linkLabel1.TabIndex = 6;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "Github 开源";
            this.linkLabel1.LinkClicked += linkLabel1_LinkClicked;
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 17;
            this.listBox1.Location = new Point(12, 85);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new Size(266, 242);
            this.listBox1.TabIndex = 7;
            this.listBox1.SelectedIndexChanged += listBox1_SelectedIndexChanged;
            // 
            // button3
            // 
            this.button3.BackColor = Color.Turquoise;
            this.button3.FlatAppearance.BorderColor = Color.Turquoise;
            this.button3.FlatStyle = FlatStyle.Flat;
            this.button3.Font = new Font("SDK_SC_Web", 10.4999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.button3.Location = new Point(198, 333);
            this.button3.Name = "button3";
            this.button3.Size = new Size(80, 39);
            this.button3.TabIndex = 8;
            this.button3.Text = "注入";
            this.button3.UseVisualStyleBackColor = false;
            this.button3.Click += button3_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 17F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(289, 381);
            Controls.Add(this.button3);
            Controls.Add(this.listBox1);
            Controls.Add(this.linkLabel1);
            Controls.Add(this.checkBox1);
            Controls.Add(this.button2);
            Controls.Add(this.label1);
            Controls.Add(this.textBox1);
            Controls.Add(this.button1);
            Icon = (Icon)resources.GetObject("$this.Icon");
            MaximizeBox = false;
            MaximumSize = new Size(305, 420);
            MinimumSize = new Size(305, 420);
            Name = "Form1";
            Opacity = 0.8D;
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Inject & launcher";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private TextBox textBox1;
        private Label label1;
        private Button button2;
        private CheckBox checkBox1;
        private LinkLabel linkLabel1;
        private ListBox listBox1;
        private Button button3;
    }
}
