using ShellProgressBar;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;

namespace RayTracing02
{
    /**
     * 光线跟踪渲染器
     */
    public class Render
    {
        private readonly int width;     // 图像宽度
        private readonly int height;    // 图像高度
        private Rgb24[,] pixels;        // 像素数组

        // 保存图像文件名
        private readonly string filename = "render.png";

        public Render(int width, int height)
        {
            pixels = new Rgb24[height, width];
            this.height = height;
            this.width = width;
        }

        /**
         * 渲染场景
         */
        public void RenderScene()
        {
            // 添加命令行控制台进度显示
            int totalTicks = height;
            var options = new ProgressBarOptions
            {
                ProgressCharacter = '-',
                ProgressBarOnBottom = true
            };

            using (var pbar = new ProgressBar(totalTicks, "", options))
            {
               for(int j = 0; j < height; j++)
                {
                    for(int i = 0; i < width; i++)
                    {
                        float r = (float)i / (width - 1);
                        float g = (float)j / (height - 1);
                        float b = 0.2f;
                        pixels[j, i] = new Rgb24((byte)(255.99*r), (byte)(255.99*g), (byte)(255.99*b));
                    }
                }
            }

            // 保存图像
            SaveImage();
        }

        /**
         * 将像素数组保存为图像
         */
        private void SaveImage()
        {
            using (var image = new Image<Rgb24>(width, height))
            {
                image.ProcessPixelRows(pixelAccessor =>
                {
                    for (int y = 0; y < pixelAccessor.Height; y++)
                    {
                        Span<Rgb24> row = pixelAccessor.GetRowSpan(y);
                        for (int x = 0; x < row.Length; x++)
                        {
                            row[x] = pixels[y, x];
                        }
                    }
                });

                // 将图像保存为png文件
                image.SaveAsPng(filename);
            }
        }
    }
}
