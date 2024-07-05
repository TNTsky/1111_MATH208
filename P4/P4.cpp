// Implement data structures to support efficient operations.
// date: 2022/11/17

#include <iostream>
using namespace std;

struct node
{
    int key, value;
    node *next;
};

void create(node *matrix[], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        node *current = new node();
        matrix[i] = current;
        cout << "[" << i + 1 << "]:";
        int j = 0;
        cin >> j;
        while (j != 0)
        {
            current->key = j;
            cin >> current->value;
            current->next = new node;
            current = current->next;
            cin >> j;
        }
        current->next = NULL;
    }
}

void print(node *matrix[], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        node *current = new node();
        current = matrix[i];
        for (int j = 1; j <= n; j++)
        {
            if (current->key == j)
            {
                cout << current->value << "\t";
                if (current->next)
                    current = current->next;
            }
            else
                cout << "0\t";
        }
        cout << endl;
    }
}

void add(node *matrix1[], node *matrix2[], int m1, int n1, int m2, int n2)
{

    if (m1 != m2 || n1 != n2)
    {
        cout << "矩陣大小不相等，無法相加\n";
        return;
    }

    cout << "\n> Add =\n";
    for (int i = 0; i < m1; i++)
    {
        node *c1 = new node(), *c2 = new node();
        c1 = matrix1[i], c2 = matrix2[i];
        for (int j = 1; j <= n1; j++)
        {
            if (c1->key == j && c2->key == j)
            {
                cout << c1->value + c2->value << "\t";
                if (c1->next)
                    c1 = c1->next;
                if (c2->next)
                    c2 = c2->next;
            }
            else if (c1->key == j)
            {
                cout << c1->value << "\t";
                if (c1->next)
                    c1 = c1->next;
            }
            else if (c2->key == j)
            {
                cout << c2->value << "\t";
                if (c2->next)
                    c2 = c2->next;
            }
            else
                cout << "0\t";
        }
        cout << endl;
    }
}

void multiply(node *matrix1[], node *matrix2[], int m1, int n1, int m2, int n2)
{
    if (n1 != m2)
    {
        cout << "矩陣大小不匹配，無法相乘\n";
        return;
    }
    cout << "\n> Multiply =\n";
    node *c1 = new node(), *c2 = new node();
    for (int i = 0; i < m1; i++)
    {
        for (int j = 1; j <= n2; j++)
        {
            int sum = 0;
            c1 = matrix1[i];
            for (int k = 1; k <= n1; k++)
            {
                if (c1->key == k)
                {
                    c2 = matrix2[k - 1];
                    while (c2)
                    {
                        if (c2->key == j)
                        {
                            sum += c1->value * c2->value;
                            break;
                        }
                        c2 = c2->next;
                    }
                    if (c1->next != NULL)
                        c1 = c1->next;
                }
            }
            cout << sum << "\t";
        }
        cout << endl;
    }
}

main()
{
    int m1, n1, m2, n2;

    cout << "> Matrix 1" << endl
         << "Size:";
    cin >> m1 >> n1;
    node *matrix1[m1];
    create(matrix1, m1, n1);

    cout << "> Matrix 2" << endl
         << "Size:";
    cin >> m2 >> n2;
    node *matrix2[m2];
    create(matrix2, m2, n2);

    cout << "\n> Matrix 1 =\n";
    print(matrix1, m1, n1);
    cout << "\n> Matrix 2 =\n";
    print(matrix2, m2, n2);
    add(matrix1, matrix2, m1, n1, m2, n2);
    multiply(matrix1, matrix2, m1, n1, m2, n2);
}
