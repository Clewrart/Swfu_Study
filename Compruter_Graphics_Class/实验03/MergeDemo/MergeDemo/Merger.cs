using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MergeDemo
{
    class Merger
    {
        /**
         * 将有序序列SeqA和SeqB归并为一个新的有序序列。
         */
        public static int[] Merge(int[] SeqA, int[] SeqB)
        {
            int[] SeqC = new int[SeqA.Length + SeqB.Length];

            int i = 0, j = 0;

            while (i < SeqA.Length && j < SeqB.Length)
            {
                if (SeqA[i] <= SeqB[j])
                {
                    SeqC[i + j] = SeqA[i];
                    i++;
                }
                else
                {
                    SeqC[i + j] = SeqB[j];
                    j++;
                }
            }
            while (i < SeqA.Length)
            {
                SeqC[i + j] = SeqA[i];
                i++;
            }

            while (j < SeqB.Length)
            {
                SeqC[i + j] = SeqB[j];
                j++;
            }

            return SeqC;
        }
    }
}
