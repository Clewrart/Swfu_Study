 /* main2-1.c     bo2-1.c         */

 #include "c1.h"
 
 typedef char ElemType;

 #include "c2-1.h"

 #include "bo2-1.c"


 int main()

{
   SqList L;
 
   ElemType e,a[5]={'a','b','c','d','e'};
 
   int i,j;

   
   printf("  ʼ  Lǰ  L.elem=%p L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);

   /*(1)   ʼ  ˳   L  */

   i=InitList(&L);

   printf("  ʼ  L  L.elem=%p L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);



   /*(2)   β   β 巨   롯a  ,  b  ,  c  ,  d  ,  e  Ԫ أ */

   for(j=1;j<=5;j++)

     i=ListInsert(&L,j,a[j-1]);


   // ڴ˱ д ϻ   Ŀ4Ҫ  ʵ ֵ        ܣ 
   /*(3)   ˳   L  */

   /*(4)   ˳   L   ȣ */

   /*(5)   ˳   L ĵ 3  Ԫ أ */

   /*(6) ڵ 4  Ԫ  λ   ϲ  롯f  Ԫ أ */

   /*(7)   ˳   L  */

   /*(8)ɾ  L ĵ 3  Ԫ أ */

   /*(9)   ˳   L  */

   /*(10) ͷ ˳   L  */

   
return(1);
 
}
