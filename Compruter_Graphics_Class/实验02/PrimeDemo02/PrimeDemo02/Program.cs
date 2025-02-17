using System.Runtime.InteropServices;

namespace PrimeDemo02
{
    class Program
    {
        /**
         * 判断整数n是否是素数。
         * 如果n是素数，返回true；否则返回false。
         */
        static bool Prime(int n)
        {
            int i;
            if (n == 2)
            {
                return true;
            }

            for (i = 2; i < n; i++)
            {
                if (n % i == 0)
                {
                    return false;
                }
            }

            if (i == n)
            {
                return true;
            }

            return false;
        }

        static void Main(string[] args)
        {
            /**
             * 实验：输出[2,1000]之内的素数
             */

            for (int i = 2; i <= 1000; i++)
            {
                if (Prime(i))
                {
                    Console.Write(i + "、");
                }
            }
        }
    }
}
