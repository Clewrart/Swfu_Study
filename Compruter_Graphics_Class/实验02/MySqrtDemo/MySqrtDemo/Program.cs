using System;

namespace MySqrtDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            double a = 2.0;
            double result = MySqrt.Sqrt(a);
            Console.WriteLine("result = {0}", result);
        }
    }
}
