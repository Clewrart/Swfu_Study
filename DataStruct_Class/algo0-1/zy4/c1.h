/* c1.h (头文件) */
#include<string.h>
#include<ctype.h>
#include<limits.h> /* INT_MAX */
#include<stdio.h> /* EOF(=^Z  F6),NULL */
#include<stdlib.h> /* atoi() */
#include<math.h> /* floor(),ceil(),abs() */
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
/* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */
