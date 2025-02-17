using ShellProgressBar;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;
using System.Numerics;

namespace RayTracing05
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
         * 计算光线交点的颜色
         */
        private Vector3 GetRayColor(Ray ray, Scene world)
        {
            HitRecord rec = HitRecord.Empty;

            // 判断光线是否和场景中的物体相交
            if (world.Hit(ray, 0, float.MaxValue, rec))
            {
                return 0.5f * new Vector3(
                    rec.N.X + 1,
                    rec.N.Y + 1,
                    rec.N.Z + 1);
            }
            else
            {
                // 计算光线方向向量对应的单位向量
                Vector3 unitDirection = Vector3.Normalize(ray.Direction);
                // -1.0 <= Y <= 1.0
                // 0.0 <= t <= 1.0
                float t = 0.5f * (unitDirection.Y + 1.0f);
                Vector3 A = new Vector3(1.0f, 1.0f, 1.0f);
                Vector3 B = new Vector3(0.5f, 0.7f, 1.0f);
                return (1.0f - t) * A + t * B;  // 颜色融合
            }
        }

        /**
         * 使用光线跟踪算法对场景进行渲染
         */
        public void RenderScene(Camera cam, Scene world)
        {
            // 添加命令行控制台进度显示
            int totalTicks = height;
            var options = new ProgressBarOptions
            {
                ProgressCharacter = '-',
                ProgressBarOnBottom = true
            };

            using (var pbar = new ProgressBar(totalTicks, "", options))
            {   // 对投影平面中的每一个元素进行遍历
                for (int j = 0; j < height; j++)
                {
                    for (int i = 0; i < width; i++)
                    {
                        // 计算纹理坐标
                        float u = (float)i / (width - 1);
                        float v = (float)j / (height - 1);

                        // 生成一条新的光线
                        Ray ray = cam.GetRay(u, v);

                        // 计算光线的颜色
                        Vector3 color = GetRayColor(ray, world);

                        // 计算光线和投影平面交点对应像素的索引值
                        // 投影平面坐标系原点在左下角，而图像坐标系原点在左上角。
                        pixels[height - j - 1, i] = new Rgb24(
                            (byte)(color.X * 255.99f),
                            (byte)(color.Y * 255.99f),
                            (byte)(color.Z * 255.99f));
                    }

                    // 进度加1
                    pbar.Tick();
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

                image.SaveAsPng(filename);
            }
        }
    }
}
