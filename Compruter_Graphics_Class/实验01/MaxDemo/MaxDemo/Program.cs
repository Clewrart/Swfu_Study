using System;

namespace MaxDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            Random random = new Random();

            // 生成[1,10)之间的随机数
            int x1 = random.Next(1, 10);
            int x2 = random.Next(1, 10);
            int maxi = 0;

            /**
             * 实验：使用if-else语句完成计算两个整数之间较大数的功能
             */
            if (x1 >= x2)
            {
                maxi = x1;
            }
            else 
            {
                maxi = x2;
            }

            Console.WriteLine("x1 = {0}, x2 = {1}, maxi = {2}", x1, x2, maxi);
        }
    }
}
