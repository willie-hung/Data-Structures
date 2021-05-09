//Question 13190
#include <iostream>
#include <vector>
using namespace std;

enum LOCATION { CENTER, LEFT, DOWN, RIGHT, UP };

struct Node
{
    int value, x, y;
    Node *L, *D, *R, *U;
    
    Node(int _x, int _y, int val);
};

Node::Node(int _x, int _y, int val)
{
    L = D = R = U = NULL;
    x = _x;
    y = _y;
    value = val;
}

Node* path(vector<vector<int>> &M, int x, int y, int row, int col, int origin)
{
    if(x < 0 || x >= col || y < 0 || y >= row)
		return NULL;

    if (M[x][y] == 0)
		return NULL;

    Node* ptr = new Node(x, y, M[x][y]);

    if (M[x][y] != -1)
    {
        if(x - 1 >= 0 && origin != LEFT && M[x - 1][y] != 0)
			ptr->L = path(M, x - 1, y, row, col, RIGHT);

		if(y - 1 >= 0 && origin != DOWN && M[x][y - 1] != 0)
			ptr->D = path(M, x, y - 1, row, col, UP);

		if(x + 1 < col && origin != RIGHT && M[x + 1][y] != 0)
			ptr->R = path(M, x + 1, y, row, col, LEFT);

		if(y + 1 < row && origin != UP && M[x][y + 1] != 0)
			ptr->U = path(M, x, y + 1, row, col, DOWN);
    }

    return ptr;
}

int shortest_answer(int L, int D, int R, int U, int val)
{
	vector<int> tmp = {L,D,R,U};
	int ans = INT32_MAX;

	if (L <= 0 && D <= 0 && R <= 0 && U <= 0) 
        return -1;
	else 
    {
		for (auto i : tmp) 
        {
			if (i > 0 && i < ans) 
                ans = i;
		}
	}
	return (ans > 0) ? val + ans : ans;
}

int shortest_path(Node* ptr)
{
    if (ptr == NULL) 
        return 0;

    if (ptr->value == -1)
        return -1;
    
    if (ptr->L == NULL && ptr->D == NULL && ptr->R == NULL && ptr->U == NULL) 
        return ptr->value;
    
    int L, D, R, U;   
    for (int i = LEFT; i <= UP; i++)
    {
        switch(i)
        {
            case LEFT:
                L = shortest_path(ptr->L);
				break;
            case DOWN:
                D = shortest_path(ptr->D);
				break;
            case RIGHT:
                R = shortest_path(ptr->R);
				break;
            case UP:
                U = shortest_path(ptr->U);
				break;
            default:
				cout << "ERROR" << endl;
				break;
        }
    }
    return shortest_answer(L, D, R, U, ptr->value);
}

int main(void) 
{
	int row, col, value, start_x, start_y;
	
    cin >> row >> col >> start_x >> start_y;

	vector<int> empty_row;
	vector<vector<int>> matrix;
	Node* root;

	for (int i = 0; i < col; i++)
		matrix.push_back(empty_row);

	for (int j = 0; j < row; j++)
		for (int i = 0; i < col; i++) 
		{
			cin >> value;
			matrix[i].push_back(value);
		}

	root = path(matrix, start_x, start_y, row, col, CENTER);
	cout << shortest_path(root) << endl;
    
    return 0;
}