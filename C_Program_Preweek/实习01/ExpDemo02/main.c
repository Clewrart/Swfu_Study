#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Data
{
    int* arr;  // 一维数组
    int n;     // 一维数组的元素个数
} Data;

void read_data(const char* filename, Data* data1, Data* data2);
void print_data(Data* data);
void merge(Data* data1, Data* data2, Data* data3);
void output_data(const char* output_filename, Data* data);

int main()
{
    const char* input_filename = "input.txt";
    const char* output_filename = "output.txt";
    Data data1 = { NULL, 0 };
    Data data2 = { NULL, 0 };

    read_data(input_filename, &data1, &data2);

    print_data(&data1);
    print_data(&data2);

    Data data3 = { NULL, 0 };

    // 合并
    merge(&data1, &data2, &data3);

    print_data(&data3);
    output_data(output_filename, &data3);
    return 0;
}

void read_data(const char* filename, Data* data1, Data* data2)
{
    FILE* fp = fopen(filename, "r");
    int n1, n2;
    fscanf(fp, "%d", &n1);
    data1->n = n1;
    data1->arr = (int*)malloc(data1->n * sizeof(int));

    for (int i = 0; i < data1->n; i++)
    {
        fscanf(fp, "%d", &data1->arr[i]);
    }

    fscanf(fp, "%d", &n2);
    data2->n = n2;
    data2->arr = (int*)malloc(data2->n * sizeof(int));

    for (int i = 0; i < data2->n; i++)
    {
        fscanf(fp, "%d", &data2->arr[i]);
    }

    fclose(fp);
}

void print_data(Data* data)
{
    if (data == NULL || data->arr == NULL)
    {
        return;
    }

    printf("%d个元素的一维数组：\n", data->n);
    for (int i = 0; i < data->n; i++)
    {
        printf("%d ", data->arr[i]);
    }
    printf("\n");
}

void merge(Data* data1, Data* data2, Data* data3)
{
    int total = data1->n+data2->n;
    data3->n = total;
    data3->arr = (int*)malloc(total * sizeof(int));
    int i=0;
    int j=0;
    int p=0;


    while (i < data1->n && j < data2->n)
        {
        if (data1->arr[i] <= data2->arr[j])
        {
            data3->arr[p++] = data1->arr[i++];
        }
        else {
            data3->arr[p++] = data2->arr[j++];
        }
    }

    while (i < data1->n) {
        data3->arr[p++] = data1->arr[i++];
    }

    while (j < data2->n) {
        data3->arr[p++] = data2->arr[j++];
    }

}

void output_data(const char* output_filename, Data* data)
{
    void output_data(const char* output_filename, Data* data)
    FILE* fpo= fopen(output_filename, "w");
    fprintf(fpo, "%d\n", data->n);

    for (int i = 0; i < data->n; i++)
    {
        fprintf(fpo, "%d ", data->arr[i]);
    }

    fclose(fpo);
}

