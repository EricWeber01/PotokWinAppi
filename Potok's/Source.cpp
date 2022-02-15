#include <iostream>
#include <Windows.h>
#include <time.h>
#define SIZE 10
using namespace std;
struct matrix
{
    int value[SIZE];
    int result = 0;
    int rnd;
    bool check;
};
DWORD WINAPI generateAndCalc(void* data)
{
    matrix* m = (matrix*)data;
    srand(m->rnd);
    for (int i = 0; i < SIZE; i++)
    {
        m->value[i] = rand() % 10;
        if (m->value[i] % 2 != 0)
            m->result += m->value[i];
    }
    return 0;
}
DWORD WINAPI generateAndCalc(void* data)
{
    matrix* m = (matrix*)data;
    srand(m->rnd);
    for (int i = 0; i < SIZE; i++)
    {
        m->value[i] = rand() % 10;
        if (i % 2 != 0)
            m->result += m->value[i];
    }
    return 0;
}
DWORD WINAPI generateAndCalc(void* data)
{
    matrix* m = (matrix*)data;
    srand(m->rnd);
    for (int i = 0; i < SIZE; i++)
    {
        m->value[i] = rand() % 10;
    }
    if (m->check == 1) {
        for (int i = 0; i < SIZE - 1; i++)
        {
            for (int j = 0; j < SIZE - i - 1; j++)
            {
                if (m->value[j] > m->value[j + 1])
                    swap(m->value[j], m->value[j + 1]);
            }
        }
    }
    else if (m->check == 0) {
        for (int i = 0; i < SIZE - 1; i++)
        {
            for (int j = 0; j < SIZE - i - 1; j++)
            {
                if (m->value[j] < m->value[j + 1])
                    swap(m->value[j], m->value[j + 1]);
            }
        }
    }
    return 0;
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    HANDLE thread[SIZE];
    DWORD thrId[SIZE];
    matrix mat[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        mat[i].rnd = rand();
        thread[i] = CreateThread(NULL, 0, &generateAndCalc, &mat[i], 0, &thrId[i]);
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf(" %d", mat[i].value[j]);
        }
        printf(" |  = %d\n", mat[i].result);
    }
    for (int i = 0; i < SIZE; i++)
    {
        CloseHandle(thread[i]);
    }
    matrix mat2[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        mat2[i].rnd = rand();
        thread[i] = CreateThread(NULL, 0, &generateAndCalc, &mat2[i], 0, &thrId[i]);
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("  %d", mat2[j].value[i]);
        }
        cout << endl;
    }
    for (int i = 0; i < SIZE; i++)
    {
        cout << " ||";
    }
    cout << endl;
    for (int i = 0; i < SIZE; i++)
    {
        printf(" %d", mat2[i].result);
    }
    for (int i = 0; i < SIZE; i++)
    {
        CloseHandle(thread[i]);
    }
    matrix mat3[SIZE];
    bool check;
    for (int i = 0; i < SIZE; i++)
    {
        mat3[i].rnd = rand();
        printf("1 ==> Возростание\n0 ==> Убывание\n");
        cin >> check;
        mat3[i].check = check;
        thread[i] = CreateThread(NULL, 0, &generateAndCalc, &mat3[i], 0, &thrId[i]);
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("  %d", mat3[i].value[j]);
        }
        cout << endl;
    }
    for (int i = 0; i < SIZE; i++)
    {
        CloseHandle(thread[i]);
    }
    return 0;
}