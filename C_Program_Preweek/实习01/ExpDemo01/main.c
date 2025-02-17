#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Data
{
    int** mat;  // 动态二维数组
    int r;      // 动态二维数组的行数
    int c;      // 动态二维数组的列数
} Data;

void read_data(const char* filename, Data* data);
void print_data(Data* data);
void transpose(Data* data, Data* tdata);
void output_data(const char* output_filename, Data* data);

int main()
{
    const char* input_filename = "input.txt";
    const char* output_filename = "output.txt";
    Data data = { NULL, 0, 0 };
    read_data(input_filename, &data);
    print_data(&data);
    Data tdata = { NULL, 0, 0 };

    // 转置
    transpose(&data, &tdata);
    print_data(&tdata);
    output_data(output_filename, &tdata);
    return 0;
}

void read_data(const char* filename, Data* data)
{
    FILE* fp = fopen(filename, "r");
    int r, c;
    fscanf(fp, "%d", &r);
    fscanf(fp, "%d", &c);

    data->r = r;
    data->c = c;

    data->mat = (int**)malloc(r * sizeof(int*));

    for (int i = 0; i < r; i++)
    {
        data->mat[i] = malloc(c * sizeof(int));
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            fscanf(fp, "%d", &data->mat[i][j]);
        }
    }

    fclose(fp);
}

void print_data(Data* data)
{
    if (data == NULL || data->mat == NULL)
    {
        return;
    }

    printf("%d行%d列的矩阵：\n", data->r, data->c);
    for (int i = 0; i < data->r; i++)
    {
        for (int j = 0; j < data->c; j++)
        {
            printf("%d ", data->mat[i][j]);
        }
        printf("\n");
    }
}

void transpose(Data* data, Data* tdata)
{
    tdata->r = data->c;
    tdata->c = data->r;

    tdata->mat = (int**)malloc(tdata->r * sizeof(int*));
    for (int i = 0; i < tdata->r; i++)
    {
        tdata->mat[i] = malloc(tdata->c * sizeof(int));
    }

    for (int i = 0; i < data->r; i++)
    {
        for (int j = 0; j < data->c; j++)
        {
            tdata->mat[j][i] = data->mat[i][j];
        }
    }


}

void output_data(const char* output_filename, Data* tdata)
{
    FILE* fp_o = fopen("output.txt", "w");
    fprintf(fp_o, "%d\n", tdata->r);
    fprintf(fp_o, "%d\n", tdata->c);

    for (int i = 0; i < tdata->r; i++)
    {
        for (int j = 0; j < tdata->c; j++)
        {
            fprintf(fp_o, "%d ", tdata->mat[i][j]);
        }
        fprintf(fp_o, "\n");
    }

    fclose(fp_o);
}



