#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>



int CheckSum(int*a, int size) {
    int sum = 0;
    for(int i=0; i<size; i++)
        sum += a[i];
    return sum;
} 

int RunNumber(int* a, int size) {
    int count = 1;
    for (int i=1; i<size; i++) {
        count = (a[i] < a[i-1]) ? count+1: count;
    }
    return count;
} 

void FillRand(int *x, int n)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        x[i] = rand() % 1000 + 1;
    }
}

void PrintMas(int *x, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", x[i]);
    }
}

void insertionSort(int *array, int size, int &flag1, int &flag2)
{
    flag1 = 0, flag2 = 0;
    for (int step = 1; step < size; step++)
    {
        int key = array[step];
        int j = step - 1;
        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            --j;
            flag1++;
            flag2 = flag2 + 1;
        }
        array[j + 1] = key;
    }
}

void shellSort(int* array, int size, int &flag1, int &flag2)
{
    flag1 = 0, flag2 = 0;
    for (int interval = size / 2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < size; i += 1)
        {
            int temp = array[i];
            int j;
            flag2++;
            for (j = i; j >= interval && array[j - interval] > temp; j -= interval)
            {
                array[j] = array[j - interval];
                flag1++;
                flag2++;
            }
            array[j] = temp;
            flag2++;
        }
    }
}



int Shellsortknt(int *arr, int size, int &flag1, int &flag2, int &k)
{
    int h = 2, i, j, temp, k, t;
    for (k = h; k > 0; k--)
    {
        for (i = k; i < size; i++)
        {
            t = arr[i];
            j = i - k;
            flag1++;
            while (j >= 0 && t < arr[j])
            {
                flag1++;
                temp = arr[j + k];
                arr[j + k] = arr[j];
                arr[j] = temp;
                j = j - k;
                flag2 = flag2 + 3;
            }
            t = arr[j + k];
        }
    }
    // printf(" %d",C);
    // printf(" M= %d",M);
    //  printf(" %d",T);
    // printf("\n");
}




int main()
{
    int *arr, N, C, M;
    N = 100;

    int k;

    arr = new int[N];

    FillRand(arr, N);
    PrintMas(arr, N);
    printf("\nКонтрольная сумма : %d", CheckSum(arr, N));
	printf("\nКол-во серий : %d", RunNumber(arr, N));
    
    printf("\n\n");

    insertionSort(arr, N, C, M);
    PrintMas(arr, N);
    printf("\nКонтрольная сумма : %d", CheckSum(arr, N));
	printf("\nКол-во серий : %d", RunNumber(arr, N));
    printf("\n\n");


    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("|   n   |\tКол-во К-сортировок\t|\tInsert Мф + Сф  \t|\tShell Мф + Сф\t    |");
    printf("\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
    
    
    
    printf("|  %d\t|\t\t%d\t\t|", N, k);
    FillRand(arr, N);
    insertionSort(arr, N, C, M);
    printf("\t\t%d\t\t|", C + M);
    
    FillRand(arr, N);
    shellSort(arr, N, C, M);
    printf("\t     %d\t    |", C + M);
    printf("\n");

    N = 200;
    arr = new int[N];

    printf("-----------------------------------------------------------------------------------------------------\n");
    
    printf("|  %d\t|\t\t%d\t\t|", N);
    FillRand(arr, N);
    insertionSort(arr, N, C, M);
    printf("\t\t%d\t\t|", C + M);
    
    FillRand(arr, N);
    shellSort(arr, N, C, M);
    printf("\t     %d\t    |", C + M);
    printf("\n");

    N = 300;
    arr = new int[N];

    printf("-----------------------------------------------------------------------------------------------------\n");
    
    printf("|  %d\t|\t\t%d\t\t|", N);
    FillRand(arr, N);
    insertionSort(arr, N, C, M);
    printf("\t\t%d\t\t|", C + M);
    
    FillRand(arr, N);
    shellSort(arr, N, C, M);
    printf("\t     %d\t    |", C + M);
    printf("\n");
    

    N = 400;
    arr = new int[N];

    printf("-----------------------------------------------------------------------------------------------------\n");
    
    printf("|  %d\t|\t\t%d\t\t|", N);
    FillRand(arr, N);
    insertionSort(arr, N, C, M);
    printf("\t\t%d\t\t|", C + M);
    
    FillRand(arr, N);
    shellSort(arr, N, C, M);
    printf("\t     %d\t    |", C + M);
    printf("\n");

    N = 500;
    arr = new int[N];

    printf("-----------------------------------------------------------------------------------------------------\n");
    
    printf("|  %d\t|\t\t%d\t\t|", N);
    FillRand(arr, N);
    insertionSort(arr, N, C, M);
    printf("\t\t%d\t\t|", C + M);
    
    FillRand(arr, N);
    shellSort(arr, N, C, M);
    printf("\t     %d\t    |", C + M);
    printf("\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
}