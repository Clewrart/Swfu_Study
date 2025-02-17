using System;

namespace MaxDemoExt
{
    class Program
    {
        static void Main(string[] args)
        {
            Random random = new Random();

            // 生成[1,10)之间的随机数
            int x1 = random.Next(1, 10);
            int x2 = random.Next(1, 10);
            int x3 = random.Next(1, 10);
            int maxi = 0;

            /**
             * 实验：使用if-else语句完成计算三个整数之间较大数的功能
             */

            if ((x1 >= x2) && (x1 >= x3))
            {
                maxi = x1;
            }
            else if ((x2 >= x1) && (x2 >= x3))
            {
                maxi = x2;
            }
            else
            { 
                maxi = x3; 
            }

            Console.WriteLine("x1 = {0}, x2 = {1}, x3 = {2}, maxi = {3}", x1, x2, x3, maxi);
        }
    }
}