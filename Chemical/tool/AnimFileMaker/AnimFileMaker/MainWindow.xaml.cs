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

            // 必要なデータが揃っているかチェック
            if(!DataCheck()) return;

            float IntegrationTextureHeight = float.Parse(integrationTextureHeight.Text);
            float IntegrationTextureWidth = float.Parse(integrationTextureWidth.Text);
            float TextureHeight = float.Parse(textureHeight.Text);
            float TextureWidth = float.Parse(textureWidth.Text);
            float TextureLeft = float.Parse(textureXPos.Text);
            float TextureTop = float.Parse(textureYPos.Text);
            float AnimNum = float.Parse(animNum.Text);
            float AddU = (TextureWidth / IntegrationTextureWidth);
            int Digit;
            float UvPos;

            for (int i = 0; i < AnimNum; i++)
            {
                Str += i.ToString() + ",";
                UvPos = ((TextureLeft / IntegrationTextureWidth) + (AddU * i));
                //UvPos += TextureLeft / IntegrationTextureWidth;
                Digit = UvPos.ToString().Length;
                if (Digit != 1) Digit -= 2;
                Str += UvPos.ToString("f" + Digit.ToString()) + ",";

                UvPos = (TextureTop / IntegrationTextureHeight);
                Digit = UvPos.ToString().Length;
                if (Digit != 1) Digit -= 2;
                Str += UvPos.ToString("f" + Digit.ToString()) + ",";

                UvPos = (TextureLeft / IntegrationTextureWidth) + (AddU * (i + 1));
                //UvPos += TextureLeft / IntegrationTextureWidth;
                Digit = UvPos.ToString().Length;
                if (Digit != 1) Digit -= 2;
                Str += UvPos.ToString("f" + Digit.ToString()) + ",";

                UvPos = (TextureHeight + TextureTop) / IntegrationTextureHeight;
                Digit = UvPos.ToString().Length;
                if (Digit != 1) Digit -= 2;
                Str += UvPos.ToString("f" + Digit.ToString()) + "\n";
            }

            if(textureXPos2.Text != "" &&
               textureYPos2.Text != "" &&
               animNum2.Text != "")
            {
                float TextureLeft2 = float.Parse(textureXPos2.Text);
                float TextureTop2 = float.Parse(textureYPos2.Text);
                int AnimNum2 = int.Parse(animNum2.Text);

                for (int i = 0; i < AnimNum2; i++)
                {
                    Str += (i + AnimNum).ToString() + ",";

                    UvPos = ((TextureLeft2 / IntegrationTextureWidth) + (AddU * i));
                    Digit = UvPos.ToString().Length;
                    if (Digit != 1) Digit -= 2;
                    Str += UvPos.ToString("f" + Digit.ToString()) + ",";

                    UvPos = (TextureTop2 / IntegrationTextureHeight);
                    Digit = UvPos.ToString().Length;
                    if (Digit != 1) Digit -= 2;
                    Str += UvPos.ToString("f" + Digit.ToString()) + ",";

                    UvPos = (TextureLeft2 / IntegrationTextureWidth) + (AddU * (i + 1));
                    Digit = UvPos.ToString().Length;
                    if (Digit != 1) Digit -= 2;
                    Str += UvPos.ToString("f" + Digit.ToString()) + ",";

                    UvPos = (TextureHeight + TextureTop2) / IntegrationTextureHeight;
                    Digit = UvPos.ToString().Length;
                    if (Digit != 1) Digit -= 2;
                    
                    Str += UvPos.ToString("f" + Digit.ToString()) + "\n";
                }
            }

            Str += "}";

            File.WriteAllText(Filename, Str);
        }
    }
}
