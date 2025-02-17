namespace ConsoleDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            // 三角形的三条边
            double x1 = 2.7;
            double x2 = 3.2;
            double x3 = 1.5;

            /**
             * 实验内容：计算三角形的面积。
             * 三角形的三条边分别是x1，x2和x3；
             * 三角形的半边用变量s保存。
             */
            double s= 0.0;
            s =(x1 + x2 + x3)/2;


            // 计算三角形的面积并保存到变量area中
            double area = 0.0;
            area = Math.Sqrt(s * (s - x1) * (s - x2) * (s - x3));

            Console.WriteLine("三角形的面积是{0}。", area);
        }
    }
}

