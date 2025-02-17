using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;
using static System.Net.Mime.MediaTypeNames;

namespace RayTracing01
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
                            row[x] = new Rgb24(255, 0, 0);
                            row[x] = pixels[y, x];
                        }
                    }
                });

                //将图像保存为png文件
                image.SaveAsPng(filename);

            }
        }
    }
}
