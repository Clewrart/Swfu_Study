using System;
using System.Collections.Generic;
using System.Text;

namespace MySqrtDemo
{
    public class MySqrt
    {
        /**
         * 计算参数a的平方根
         */
        public static double Sqrt(double a)
        {
            double x0;
            double x1;

            x0 = 1.0;
            x1 = 0.5 * (x0 + a / x0);

            while (Math.Abs(x1 - x0) >= 1e-6)
            {
                /************************************************
                 * 在这里完成实验内容
                 ***********************************************/
                x0 = x1;
                x1 = 0.5 * (x0 + a / x0);

            }

            return x1;
        }
    }
}
