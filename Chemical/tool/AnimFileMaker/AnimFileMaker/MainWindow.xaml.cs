using Microsoft.SqlServer.Server;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Forms = System.Windows.Forms;
using System.IO;

namespace AnimFileMaker
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void FilePathButton_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new Forms.FolderBrowserDialog();
            dialog.Description = "出力先を指定してください。";

            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                // 選択されたフォルダーパスをメッセージボックスに表示
                textBox1.Text = dialog.SelectedPath;
            }
        }

        private bool DataCheck()
        {
            if (integrationTextureHeight.Text == "" ||
                integrationTextureWidth.Text == "")
            {
                MessageBox.Show("統合ファイルの幅が指定されていません");
                return false;
            }

            if(textureHeight.Text == "" ||
                textureWidth.Text == "")
            {
                MessageBox.Show("テクスチャの幅が指定されていません");
                return false;
            }

            if (textureXPos.Text == "" ||
                textureYPos.Text == "")
            {
                MessageBox.Show("左上の頂点位置が指定されていません");
                return false;
            }

            if (animNum.Text == "")
            {
                MessageBox.Show("アニメーション数が指定されていません");
                return false;
            }

            if (textBox1.Text == "")
            {
                MessageBox.Show("パスが指定されていません");
                return false;
            }

            if (textBox.Text == "")
            {
                MessageBox.Show("ファイル名が指定されていません");
                return false;
            }

            return true;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string Filename = textBox1.Text + "\\" + textBox.Text + ".anim";
            string Str = "{\n";
            int AnimNum, AnimNum2;
            float IntegrationTextureHeight, IntegrationTextureWidth;
            float TextureHeight, TextureWidth;
            float TextureLeft, TextureTop;
            float TextureLeft2, TextureTop2;

            // 必要なデータが揃っているかチェック
            if(!DataCheck()) return;

            IntegrationTextureHeight = float.Parse(integrationTextureHeight.Text);
            IntegrationTextureWidth = float.Parse(integrationTextureWidth.Text);
            TextureHeight = float.Parse(textureHeight.Text);
            TextureWidth = float.Parse(textureWidth.Text);
            TextureLeft = float.Parse(textureXPos.Text);
            TextureTop = float.Parse(textureYPos.Text);
            AnimNum = int.Parse(animNum.Text);
            float AddU = (TextureWidth / IntegrationTextureWidth);
            int digit;
            float tmp;
            for (int i = 0; i < AnimNum; i++)
            {
                Str += i.ToString() + ",";

                tmp = ((TextureLeft / IntegrationTextureWidth) + (AddU * i));
                digit = tmp.ToString().Length;
                if (digit != 1) digit -= 2;
                Str += ((TextureLeft / IntegrationTextureWidth) + (AddU * i)).ToString("f" + digit.ToString()) + ",";

                tmp = (TextureTop / IntegrationTextureHeight);
                digit = tmp.ToString().Length;
                if (digit != 1) digit -= 2;
                Str += (TextureTop / IntegrationTextureHeight).ToString("f" + digit.ToString()) + ",";

                tmp = (TextureLeft / IntegrationTextureWidth) + (AddU * (i + 1));
                digit = tmp.ToString().Length;
                if (digit != 1) digit -= 2;
                Str += ((TextureLeft / IntegrationTextureWidth) + (AddU * (i + 1))).ToString("f" + digit.ToString()) + ",";

                tmp = TextureHeight / IntegrationTextureHeight;
                digit = tmp.ToString().Length;
                if (digit != 1) digit -= 2;
                Str += (TextureHeight / IntegrationTextureHeight).ToString("f" + digit.ToString()) + "\n";
            }

            if(textureXPos2.Text != "" &&
               textureYPos2.Text != "" &&
               animNum2.Text != "")
            {
                TextureLeft2 = float.Parse(textureXPos2.Text);
                TextureTop2 = float.Parse(textureYPos2.Text);
                AnimNum2 = int.Parse(animNum2.Text);

                for (int i = 0; i < AnimNum2; i++)
                {
                    Str += (i + AnimNum).ToString() + ",";

                    tmp = ((TextureLeft2 / IntegrationTextureWidth) + (AddU * i));
                    digit = tmp.ToString().Length;
                    if (digit != 1) digit -= 2;
                    Str += ((TextureLeft2 / IntegrationTextureWidth) + (AddU * i)).ToString("f" + digit.ToString()) + ",";

                    tmp = (TextureTop2 / IntegrationTextureHeight);
                    digit = tmp.ToString().Length;
                    if (digit != 1) digit -= 2;
                    Str += (TextureTop2 / IntegrationTextureHeight).ToString("f" + digit.ToString()) + ",";

                    tmp = (TextureLeft2 / IntegrationTextureWidth) + (AddU * (i + 1));
                    digit = tmp.ToString().Length;
                    if (digit != 1) digit -= 2;
                    Str += ((TextureLeft2 / IntegrationTextureWidth) + (AddU * (i + 1))).ToString("f" + digit.ToString()) + ",";

                    tmp = TextureHeight / IntegrationTextureHeight;
                    digit = tmp.ToString().Length;
                    if (digit != 1) digit -= 2;
                    Str += (TextureHeight / IntegrationTextureHeight).ToString("f" + digit.ToString()) + "\n";
                }
            }

            Str += "}";

            File.WriteAllText(Filename, Str, Encoding.UTF8);
        }
    }
}
