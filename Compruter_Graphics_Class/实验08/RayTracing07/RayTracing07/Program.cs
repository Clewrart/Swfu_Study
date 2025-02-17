using System.Diagnostics;
using System.Numerics;

namespace RayTracing07
{
    public class Program
    {
        private const int width = 2000;     // 图像宽度
        private const int height = 1000;    // 图像高度
        private const int samples = 10;    // 采样数目
        private const int depth = 50;       // 递归深度

        public static void Main(string[] args)
        {
            // 创建相机
            Camera cam = new Camera();

            // 创建虚拟场景
            Scene world = Scene.CreateScene();

            // 创建渲染器
            Render render = new Render(width, height, samples, depth);

            // 启用计时器
            Stopwatch sw = new Stopwatch();
            sw.Start();

            // 开始渲染场景
            render.RenderScene(cam, world);

            // 停止计时器
            sw.Stop();
            Console.WriteLine("渲染时间：{0}秒", sw.ElapsedMilliseconds / 1000.0);
        }
    }
}
