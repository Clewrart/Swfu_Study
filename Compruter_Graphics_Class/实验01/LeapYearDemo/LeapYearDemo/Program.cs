namespace LeapYearDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("请输入一个整数代表年份：");
            string s = Console.ReadLine();
            int year = int.Parse(s);
            bool isLeapyear = false;


            /**
             * 实验：判断整形变量year代表的年份是否是闰年。
             * 如果year是闰年，将isLeapYear赋值为true；反之赋值为false。
             * 计算某一年是否是闰年：
             *   (1) 要么能够被4整除，但不能被100整除，例如2008；
             *   (2) 要么能够被400整除，例如2000。
             */
            if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
            {
                isLeapyear = true;
            }

            if (isLeapyear)
            {
               
                Console.WriteLine("{0} 是闰年!", year);
            }
            else
            {
                Console.WriteLine("{0} 不是闰年!", year);
            }
            
        }

    }
}
