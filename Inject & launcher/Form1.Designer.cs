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
            this.groupBox1 = new GroupBox();
            this.radioButton2 = new RadioButton();
            this.radioButton1 = new RadioButton();
            this.checkBox1 = new CheckBox();
            this.groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // button1
            // 
            this.button1.Font = new Font("SDK_SC_Web", 10.4999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.button1.Location = new Point(181, 126);
            this.button1.Name = "button1";
            this.button1.Size = new Size(96, 39);
            this.button1.TabIndex = 0;
            this.button1.Text = "启动#注入";
            this.button1.UseVisualStyleBackColor = true;
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
            this.button2.Font = new Font("SDK_SC_Web", 8.999999F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.button2.Location = new Point(228, 31);
            this.button2.Name = "button2";
            this.button2.Size = new Size(50, 24);
            this.button2.TabIndex = 3;
            this.button2.Text = "选择";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButton2);
            this.groupBox1.Controls.Add(this.radioButton1);
            this.groupBox1.Font = new Font("SDK_SC_Web", 11.9999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.groupBox1.Location = new Point(12, 60);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new Size(266, 60);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "启动方式";
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Font = new Font("SDK_SC_Web", 10.4999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.radioButton2.Location = new Point(142, 26);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new Size(110, 21);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "本地启动方式";
            this.radioButton2.UseVisualStyleBackColor = true;

            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Font = new Font("SDK_SC_Web", 10.4999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.radioButton1.Location = new Point(6, 26);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new Size(130, 21);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Steam 启动方式";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Font = new Font("SDK_SC_Web", 10.4999981F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.checkBox1.Location = new Point(12, 126);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new Size(111, 21);
            this.checkBox1.TabIndex = 5;
            this.checkBox1.Text = "剔除进程检测";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 17F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(289, 381);
            Controls.Add(this.checkBox1);
            Controls.Add(this.groupBox1);
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
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button button1;
        private TextBox textBox1;
        private Label label1;
        private Button button2;
        private GroupBox groupBox1;
        private RadioButton radioButton2;
        private RadioButton radioButton1;
        private CheckBox checkBox1;
    }
}
