﻿namespace ModbusTCPUpdate
{
        partial class Form1
        {
                /// <summary>
                /// 必需的设计器变量。
                /// </summary>
                private System.ComponentModel.IContainer components = null;

                /// <summary>
                /// 清理所有正在使用的资源。
                /// </summary>
                /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
                protected override void Dispose(bool disposing)
                {
                        if (disposing && (components != null))
                        {
                                components.Dispose();
                        }
                        base.Dispose(disposing);
                }

                #region Windows 窗体设计器生成的代码

                /// <summary>
                /// 设计器支持所需的方法 - 不要修改
                /// 使用代码编辑器修改此方法的内容。
                /// </summary>
                private void InitializeComponent()
                {
            this.btx_open_server = new System.Windows.Forms.Button();
            this.function_area = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.button1 = new System.Windows.Forms.Button();
            this.txb_info = new System.Windows.Forms.RichTextBox();
            this.tab_update = new System.Windows.Forms.TabPage();
            this.tab_setting = new System.Windows.Forms.TabPage();
            this.lb_modbus_slave = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.function_area.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tab_setting.SuspendLayout();
            this.SuspendLayout();
            // 
            // btx_open_server
            // 
            this.btx_open_server.Location = new System.Drawing.Point(198, 339);
            this.btx_open_server.Name = "btx_open_server";
            this.btx_open_server.Size = new System.Drawing.Size(75, 23);
            this.btx_open_server.TabIndex = 0;
            this.btx_open_server.Text = "open";
            this.btx_open_server.UseVisualStyleBackColor = true;
            this.btx_open_server.Click += new System.EventHandler(this.btx_open_server_Click);
            // 
            // function_area
            // 
            this.function_area.Controls.Add(this.tabPage1);
            this.function_area.Controls.Add(this.tab_update);
            this.function_area.Controls.Add(this.tab_setting);
            this.function_area.Location = new System.Drawing.Point(12, 12);
            this.function_area.Multiline = true;
            this.function_area.Name = "function_area";
            this.function_area.SelectedIndex = 0;
            this.function_area.Size = new System.Drawing.Size(504, 418);
            this.function_area.TabIndex = 3;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox2);
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Controls.Add(this.button1);
            this.tabPage1.Controls.Add(this.txb_info);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(496, 392);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Modbus";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(168, 167);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // txb_info
            // 
            this.txb_info.Location = new System.Drawing.Point(24, 18);
            this.txb_info.Name = "txb_info";
            this.txb_info.Size = new System.Drawing.Size(427, 119);
            this.txb_info.TabIndex = 2;
            this.txb_info.Text = "";
            // 
            // tab_update
            // 
            this.tab_update.Location = new System.Drawing.Point(4, 22);
            this.tab_update.Name = "tab_update";
            this.tab_update.Padding = new System.Windows.Forms.Padding(3);
            this.tab_update.Size = new System.Drawing.Size(496, 392);
            this.tab_update.TabIndex = 1;
            this.tab_update.Text = "固件更新";
            this.tab_update.UseVisualStyleBackColor = true;
            // 
            // tab_setting
            // 
            this.tab_setting.Controls.Add(this.lb_modbus_slave);
            this.tab_setting.Controls.Add(this.btx_open_server);
            this.tab_setting.Location = new System.Drawing.Point(4, 22);
            this.tab_setting.Name = "tab_setting";
            this.tab_setting.Padding = new System.Windows.Forms.Padding(3);
            this.tab_setting.Size = new System.Drawing.Size(496, 392);
            this.tab_setting.TabIndex = 2;
            this.tab_setting.Text = "设置";
            this.tab_setting.UseVisualStyleBackColor = true;
            // 
            // lb_modbus_slave
            // 
            this.lb_modbus_slave.FormattingEnabled = true;
            this.lb_modbus_slave.ItemHeight = 12;
            this.lb_modbus_slave.Location = new System.Drawing.Point(6, 11);
            this.lb_modbus_slave.Name = "lb_modbus_slave";
            this.lb_modbus_slave.Size = new System.Drawing.Size(484, 112);
            this.lb_modbus_slave.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(6, 247);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 100);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "读数据";
            // 
            // groupBox2
            // 
            this.groupBox2.Location = new System.Drawing.Point(278, 247);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 100);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "写数据";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(525, 558);
            this.Controls.Add(this.function_area);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.function_area.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tab_setting.ResumeLayout(false);
            this.ResumeLayout(false);

                }

                #endregion

                private System.Windows.Forms.Button btx_open_server;
                private System.Windows.Forms.TabControl function_area;
                private System.Windows.Forms.TabPage tabPage1;
                private System.Windows.Forms.TabPage tab_update;
                private System.Windows.Forms.RichTextBox txb_info;
                private System.Windows.Forms.TabPage tab_setting;
                private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ListBox lb_modbus_slave;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}

