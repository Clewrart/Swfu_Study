 /* c2-1.h    Ա Ķ ̬    ˳  洢 ṹ */
 #define LIST_INIT_SIZE 10 /*    Ա 洢 ռ ĳ ʼ       */
 #define LISTINCREMENT 2 /*    Ա 洢 ռ ķ        */
 typedef struct
 {
   ElemType *elem; /*  洢 ռ  ַ */
   int length; /*   ǰ     */
   int listsize; /*   ǰ    Ĵ洢    (  sizeof(ElemType)Ϊ  λ) */
 }SqList;
