using System.Diagnostics;

namespace Inject___launcher {
    using System.ComponentModel;
    using System.Runtime.InteropServices;

    public partial class Form1 : Form {
        public Form1() {
            this.InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
            if (File.Exists("path")) {
                this.textBox1.Text = File.ReadAllText("path");
            }
        }

        [DllImport("kernel32.dll")]
        public static extern int VirtualAllocEx(IntPtr hwnd, int lpaddress, int size, int type, int tect);

        [DllImport("kernel32.dll")]
        public static extern int WriteProcessMemory(IntPtr hwnd, int baseaddress, string buffer, int nsize, int filewriten);

        [DllImport("kernel32.dll")]
        public static extern int GetProcAddress(int hwnd, string lpname);

        [DllImport("kernel32.dll")]
        public static extern int GetModuleHandleA(string name);

        [DllImport("kernel32.dll")]
        public static extern IntPtr CreateRemoteThread(IntPtr hwnd, int attrib, int size, int address, int par, int flags, int threadid);

        [DllImport("KERNEL32.DLL ")]
        public static extern int CloseHandle(IntPtr handle);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e) {
            this.listBox1.Items.Clear();
            this.button1.Enabled = false;
            try {
                new Thread(
                           () => {
                               this.listBox1.Items.Add(Log.FormatLog("准备启动游戏..."));
                               this.listBox1.Items.Add(Log.FormatLog("启动模式: " + (this.radioButton1.Checked ? "Steam启动" : "本地启动")));
                               this.listBox1.Items.Add(Log.FormatLog("剔除检测: " + (this.checkBox1.Checked ? "已启用" : "未启用")));
                               if (this.checkBox1.Checked) {
                                   this.listBox1.Items.Add(Log.FormatLog("正在剔除检测..."));
                                   if (this.textBox1.Text == "") {
                                       this.listBox1.Items.Add(Log.FormatLog("未选择游戏目录!"));
                                       return;
                                   }

                                   this.listBox1.Items.Add(Log.FormatLog("正在替换文件..."));
                                   try { File.Copy("KS_Diagnostics_Process.dll", this.textBox1.Text + "\\Phasmophobia_Data\\Plugins\\x86_64"); } catch (UnauthorizedAccessException ex) {
                                       // TODO: Handle the System.UnauthorizedAccessException
                                       MessageBox.Show("复制文件出错\n" + ex.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                                       this.listBox1.Items.Add(Log.FormatLog("复制文件出错!"));
                                       this.button1.Enabled = true;
                                   }

                                   this.listBox1.Items.Add(Log.FormatLog("复制文件成功!"));
                                   this.listBox1.Items.Add(Log.FormatLog("剔除检测成功!"));

                                   this.listBox1.Items.Add(Log.FormatLog("正在启动游戏..."));
                                   if (this.radioButton1.Checked) {
                                       Process.Start("steam://rungameid/739630");
                                   } else {
                                       Process.Start(this.textBox1.Text + "Phasmophobia.exe");
                                   }

                               findProcess:
                                   Thread.Sleep(1000);
                                   var process = Process.GetProcessesByName("Phasmophobia.exe");
                                   if (process != null && (process.Length == 0 || process[0].Handle == 0)) {
                                       goto findProcess;
                                   }

                                   this.listBox1.Items.Add(Log.FormatLog("正在注入..."));
                                   Int32 AllocBaseAddress = VirtualAllocEx(process[0].Handle, 0, "Phasmophobia.dll".Length + 1, 4096, 4);
                                   if (AllocBaseAddress == 0) {
                                       MessageBox.Show("内存分配失败", "错误");
                                       this.listBox1.Items.Add(Log.FormatLog("内存分配失败!"));
                                       this.button1.Enabled = true;
                                       return;
                                   }

                                   //写入dll路径到微信进程
                                   if (WriteProcessMemory(process[0].Handle, AllocBaseAddress, "Phasmophobia.dll", "Phasmophobia.dll".Length + 1, 0) == 0) {
                                       MessageBox.Show("DLL写入失败", "错误", 0);
                                       this.listBox1.Items.Add(Log.FormatLog("DLL写入失败!"));
                                       this.button1.Enabled = true;
                                       return;
                                   }

                                   Int32 loadaddr = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
                                   if (loadaddr == 0) {
                                       MessageBox.Show("取得LoadLibraryA的地址失败");
                                       this.listBox1.Items.Add(Log.FormatLog("取得LoadLibraryA的地址失败!"));
                                       this.button1.Enabled = true;
                                       return;
                                   }

                                   IntPtr ThreadHwnd = CreateRemoteThread(process[0].Handle, 0, 0, loadaddr, AllocBaseAddress, 0, 0);
                                   if (ThreadHwnd == IntPtr.Zero) {
                                       MessageBox.Show("创建远程线程失败");
                                       this.listBox1.Items.Add(Log.FormatLog("创建远程线程失败!"));
                                       this.button1.Enabled = true;
                                       return;
                                   }

                                   CloseHandle(ThreadHwnd);

                                   this.listBox1.Items.Add(Log.FormatLog("注入成功!"));
                                   this.button1.Enabled = true;
                               }
                           }).Start();
            } catch (ThreadStateException ex) {
                // TODO: Handle the System.Threading.ThreadStateException
                MessageBox.Show("创建启动线程失败\n" + ex.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                this.listBox1.Items.Add(Log.FormatLog("创建启动线程失败!"));
                this.button1.Enabled = true;
            } catch (Win32Exception ex) {
                // TODO: Handle the System.ComponentModel.Win32Exception
                MessageBox.Show("启动游戏失败\n" + ex.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
                this.listBox1.Items.Add(Log.FormatLog("启动游戏失败!"));
                this.button1.Enabled = true;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e) {
            this.textBox1.PlaceholderText = "路径...";
            this.listBox1.Items.Add(Log.FormatLog("启动器启动!"));
        }

        private void button2_Click(object sender, EventArgs e) {
            System.Windows.Forms.FolderBrowserDialog dialog = new System.Windows.Forms.FolderBrowserDialog();
            dialog.Description         = "请选择一个目录作为路径：";
            dialog.ShowNewFolderButton = true;
            dialog.RootFolder          = Environment.SpecialFolder.ApplicationData;
            System.Windows.Forms.DialogResult result = dialog.ShowDialog();
            this.textBox1.Text = result.ToString();
            try {
                if (!File.Exists("path")) {
                    File.Create("path");
                }
                File.WriteAllText("path", this.textBox1.Text);
            } catch (DirectoryNotFoundException ex) {
                // TODO: Handle the System.IO.DirectoryNotFoundException
                MessageBox.Show("写出目录失败\n" + ex.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
            }
        }
    }
}