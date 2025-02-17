using System;

namespace MergeDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            const int M = 10;
            const int N = 10;
            const int MaxValue = 100;

            int[] SeqA = new int[M];
            int[] SeqB = new int[N];

            Random random = new Random();

            for (int i = 0; i < M; i++)
            {
                SeqA[i] = random.Next(1, MaxValue);
            }
            Array.Sort(SeqA);
            Print(SeqA, "第一个序列：");

            for (int i = 0; i < N; i++)
            {
                SeqB[i] = random.Next(1, MaxValue);
            }
            Array.Sort(SeqB);
            Print(SeqB, "第二个序列：");

            int[] SeqC = Merger.Merge(SeqA, SeqB);
            {

                Print(SeqC, "归并后的序列：");
            }

            static void Print(int[] Seq, string title)
            {
                Console.Write(title);
                foreach (int e in Seq)
                {
                    Console.Write(e + " ");
                }
                Console.WriteLine();
            }
        }
    }
}
