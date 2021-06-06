#include <iostream>
using namespace std;

void Merge(int A[], int p, int q, int m)
{
    int n1 = m - p + 1;
    int n2 = q - m;

    int left[n1];
    int right[n2];

    for (int i = 0; i < n1; i++)
    {
        left[i] = A[p + i];
    }
    for (int i = 0; i < n2; i++)
    {
        right[i] = A[i + m + 1];
    }

    left[n1] = INT32_MAX;
    right[n2] = INT32_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= q; k++)
    {
        if (left[i] <= right[j])
        {
            A[k] = left[i];
            i++;
        }
        else
        {
            A[k] = right[j];
            j++;
        }
    }
}

void MergeSort(int A[], int p, int q)
{
    if (p < q)
    {
        int m = (p + q) / 2;
        MergeSort(A, p, m);
        MergeSort(A, m + 1, q);
        Merge(A, p, q, m);
    }
}

//Merge sort L & R arrays
void mysort(int arr[], int l, int r)
{
    MergeSort(arr, 0, l - 1);
    MergeSort(arr, l, l + r - 1);
}

void solve()
{
    int N, L, R;
    long long int C, change, move;

    cin >> N >> L >> R >> C;

    //Insert all the gems into one array
    int *gem = new int[N];
    for (int i = 0; i < N; i++)
    {
        int v;
        cin >> v;
        gem[i] = v;
    }
    mysort(gem, L, R);

    //Calculate change and move
    if (L >= R)
    {
        change = (L - R) / 2 + (L + R) / 2;
        move = (L - R) / 2;
    }
    else
    {
        change = (R - L) / 2 + (L + R) / 2;
        move = (R - L) / 2;
    }

    //Find the elements that have already matched
    int match = 0;
    for (int i = 0, j = L; (i < L) && (j < L + R); i++, j++)
    {
        if (gem[i] == gem[j])
        {
            gem[i] = gem[j] = 0;
            match = match + 1;
        }
        else if (gem[i] > gem[j])
        {
            i = i - 1;
        }
        else
        {
            j = j - 1;
        }
    }
    //Same elements don't need to change
    change = change - match;

    //Choose the longer side's index
    int long_begin, long_end;
    if (L >= R)
    {
        long_begin = 0;
        long_end = L - 1;
    }
    else
    {
        long_begin = L;
        long_end = L + R - 1;
    }

    long long int long_match = 0;
    for (int i = long_begin; i < long_end;)
    {
        if (gem[i] == 0)
        {
            i++;
        }
        //Find out the repeat ones
        else if (gem[i] == gem[i + 1])
        {
            gem[i] = gem[i + 1] = 0;
            i = i + 2;
            long_match = long_match + 1;
        }
        else
        {
            i++;
        }
    }

    //Total Cost
    cout << (change - min(long_match, move)) * C << endl;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        solve();
    }
    return 0;
}