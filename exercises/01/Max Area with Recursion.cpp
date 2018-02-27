#include<iostream>

const int N = 100;

int calculateArea(char field[][N], int n, int i, int j, char density)
{
    if (i < 0 || i >= n || j < 0 || j > n) return 0; // Out of bounds
    if (field[i][j] != density) return 0; // Wrong density

    field[i][j] = 'R'; // Mark as visited
    return 1 +
            calculateArea(field, n, i + 1, j, density) +
            calculateArea(field, n, i - 1, j, density) +
            calculateArea(field, n, i, j + 1, density) +
            calculateArea(field, n, i, j - 1, density);
}

int maxArea(char field[][N], int n, char density)
{
    int max = 0;
    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < n ; ++j)
        {
            int area = calculateArea(field, n, i, j, density);
            if (area > max)
            {
                max = area;
            }
        }
    }

    return max;
}

int main()
{
    int n; // size of the field;
    std::cin>>n;
    char field[N][N];

    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < n ; ++j)
        {
            std::cin>>field[i][j];
        }
    }

    char density;
    std::cin>>density;

    std::cout<<maxArea(field, n, density);

    return 0;
}
