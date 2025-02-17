using System.Diagnostics;

namespace RayTracing03
{
    public class Program
    {
        const int width = 2000;
        const int height = 1000;

        public static void Main(string[] args)
        {
            // 创建相机
            Camera cam = new Camera();

            // 创建渲染器
            Render render = new Render(width, height);

            // 启用计时器
            Stopwatch sw = new Stopwatch();
            sw.Start();

            // 开始渲染场景
            render.RenderScene(cam);

            // 停止计时器
            sw.Stop();
            Console.WriteLine("渲染时间：{0}毫秒", sw.ElapsedMilliseconds);
        }
    }
}
