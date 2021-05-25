//Problem 13217
#include <iostream>
#include <vector>
using namespace std;

#define INF INT32_MAX

void floyd_warshall(vector<vector<int>> &M, int num)
{
    for (int k = 0; k < num; k++)
    {
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {
                if (M[i][k] < INF && M[k][j] < INF && M[i][k] > 0 && M[k][j] > 0)
                {
                    if (M[i][j] > M[i][k] + M[k][j])
                    {
                        M[i][j] = M[i][k] + M[k][j];
                    }
                }
            }
        }
    }
}

int main()
{
    int T, N, Q, E, start, end;

    cin >> T;

    for (int i = 0; i < T; i++)
    {
        cin >> N >> Q;

        vector<vector<int>> matrix;
        vector<vector<vector<int>>> path;

        vector<int> empty_row;
        vector<vector<int>> empty_plane;

        for (int j = 0; j < N; j++)
        {
            matrix.push_back(empty_row);
            path.push_back(empty_plane);
        }

        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                int E;

                cin >> E;

                if (j == k)
                    matrix[j].push_back(0);

                else if (E == 0)
                    matrix[j].push_back(INF);

                else
                    matrix[j].push_back(E);

                path[j].push_back(empty_row);

                path[j][k].push_back(j);
                path[j][k].push_back(k);
            }
        }

        floyd_warshall(matrix, N);

        cout << "Testcase" << i + 1 << endl;

        for (int j = 0; j < Q; j++)
        {
            cin >> start >> end;

            if (matrix[start][end] != 0 && matrix[start][end] != INF)
            {
                cout << "Cost(" << start << "," << end << "):" << matrix[start][end] << endl;
            }
            else
            {
                cout << "Cost(" << start << "," << end << "):No Service" << endl;
            }
        }
    }
    return 0;
}