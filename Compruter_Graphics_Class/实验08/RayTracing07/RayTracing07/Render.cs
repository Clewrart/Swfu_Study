using ShellProgressBar;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;
using System.Numerics;

namespace RayTracing07
{
    /**
     * 光线跟踪渲染器
     */
    public class Render
    {
        private readonly int width;     // 图像宽度
        private readonly int height;    // 图像高度
        private Rgb24[,] pixels;        // 像素数组
        private readonly int samples;   // 每个像素采样数
        private readonly int maxDepth;  // 最大递归深度

        // 保存图像文件名
        private readonly string filename = "render.png";

        public Render(int width, int height, int samples, int depth)
        {
            pixels = new Rgb24[height, width];
            this.height = height;
            this.width = width;
            this.samples = samples;
            this.maxDepth = depth;
        }

        /**
         * 计算光线交点的颜色
         */
        private Vector3 GetRayColor(Ray ray, Scene world, int depth)
        {
            HitRecord rec = HitRecord.Empty;

            if (depth <= 0)
            {
                return Vector3.Zero;
            }
   
                // 判断光线是否和场景中的物体相交
                if (world.Hit(ray, 0.001f, float.MaxValue, rec))
                {
                    if (rec.M.Scatter(ray, rec, out Vector3 attenuation, out Ray scattered))
                { 
                        return attenuation * GetRayColor(scattered, world, depth - 1);
                }
                else
                {
                    return Vector3.Zero;
                }
                
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
            // 随机数
            Random random = new Random();

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
                        // 像素的颜色累加器
                        Vector3 color = Vector3.Zero;

                        // 超采样
                        for (int s = 0; s < samples; s++)
                        {
                            // 计算纹理坐标
                            float u = (float)(i + random.NextDouble()) / (width - 1);
                            float v = (float)(j + random.NextDouble()) / (height - 1);

                            // 生成一条新的光线
                            Ray ray = cam.GetRay(u, v);

                            // 计算光线的颜色
                            color += GetRayColor(ray, world, maxDepth);
                        }

                        // 像素的颜色为所有样本颜色的平均值
                        color /= samples;

                        // 伽马校正
                        float r = MathF.Sqrt(color.X);
                        float g = MathF.Sqrt(color.Y);
                        float b = MathF.Sqrt(color.Z);

                        // 计算光线和投影平面交点对应像素的索引值
                        // 投影平面坐标系原点在左下角，而图像坐标系原点在左上角。
                        pixels[height - j - 1, i] = new Rgb24(
                            (byte)(256 * Math.Clamp(r, 0, 0.999)),
                            (byte)(256 * Math.Clamp(g, 0, 0.999)),
                            (byte)(256 * Math.Clamp(b, 0, 0.999)));
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
