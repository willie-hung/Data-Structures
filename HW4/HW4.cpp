//Problem 13202
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

#define INF INT32_MAX

int dis[100][100], pos[100][100];

//Initialize the containers
void initialize(int V, vector<vector<int>> &Matrix, vector<vector<int>> &Position)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            dis[i][j] = Matrix[i][j];
            pos[i][j] = Position[i][j];
        }
    }
}

//Compare the smallest node in the path
bool choose_path(vector<int> orig_path, vector<int> new_path)
{
    for (int i = 0; i < min(orig_path.size(), new_path.size()); i++)
    {
        if (orig_path[i] < new_path[i])
            return false;

        else if (orig_path[i] > new_path[i])
            return true;
    }

    if (orig_path.size() < new_path.size())
        return false;
    else
        return true;
}

//Floyd Warshall Algorithm
void floyd_warshall(int V, vector<vector<vector<int>>> &path)
{
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dis[i][k] != INF && dis[k][j] != INF && i != j && i != k && j != k)
                {
                    if (dis[i][j] > dis[i][k] + dis[k][j])
                    {
                        dis[i][j] = dis[i][k] + dis[k][j];
                        pos[i][j] = k;

                        path[i][j] = path[i][k];

                        for (int l = 1; l < path[k][j].size(); l++)
                        {
                            path[i][j].push_back(path[k][j][l]);
                        }
                    }

                    else if (dis[i][j] == dis[i][k] + dis[k][j])
                    {
                        vector<int> new_path;
                        new_path = path[i][k];

                        for (int l = 1; l < path[k][j].size(); l++)
                        {
                            new_path.push_back(path[k][j][l]);
                        }

                        if (choose_path(path[i][j], new_path))
                        {
                            path[i][j] = new_path;
                            pos[i][j] = k;
                        }
                    }
                }
            }
        }
    }
}

void print_path(int V, vector<vector<vector<int>>> &path)
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dis[i][j] != INF && i != j)
            {
                cout << "Path(" << i << "," << j << "):";

                cout << path[i][j][0];

                for (int k = 1; k < path[i][j].size(); k++)
                {
                    cout << "->" << path[i][j][k];
                }
                cout << endl;
                cout << "Difficulty:" << dis[i][j] << endl;
            }
        }
    }
}

void centrality(int V)
{
    for (int i = 0; i < V; i++)
    {
        double sum = 0.0;

        for (int j = 0; j < V; j++)
        {
            if (i != j && dis[j][i] != INF)
            {
                sum += (1.0 / (dis[j][i]));
            }
        }
        cout << "Centrality(" << i << "):" << fixed << setprecision(3) << sum << endl;
    }
}

int main()
{
    int V, E;

    vector<int> empty_row;
    vector<vector<int>> empty_plane;

    vector<vector<int>> matrix, position;
    vector<vector<vector<int>>> path;

    cin >> V;

    //Insert data
    for (int i = 0; i < V; i++)
    {
        matrix.push_back(empty_row);
        position.push_back(empty_row);
        path.push_back(empty_plane);

        for (int j = 0; j < V; j++)
        {
            //Original
            cin >> E;

            if (i == j)
                matrix[i].push_back(0);

            else if (E == 0)
                matrix[i].push_back(INF);

            else
                matrix[i].push_back(E);

            //Position
            position[i].push_back(-1);

            //Path
            path[i].push_back(empty_row);
            path[i][j].push_back(i); //x
            path[i][j].push_back(j); //y
        }
    }

    //Initialize
    initialize(V, matrix, position);

    //Execution
    floyd_warshall(V, path);

    //Path & Difficulty
    print_path(V, path);

    //Centrality
    centrality(V);

    return 0;
}