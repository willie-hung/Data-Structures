#include <iostream>
#include <vector>
using namespace std;

int N, K;
vector<int> V, W;

int max(int index, int sum_v, int sum_w)
{
    if (index >= N)
        return sum_v;

    else if (sum_w + W[index] > K)
        return max(index + 1, sum_v, sum_w);

    else
    {
        int sum1 = max(index + 1, sum_v + V[index], sum_w + W[index]);
        int sum2 = max(index + 1, sum_v, sum_w);
        return (sum1 > sum2) ? sum1 : sum2;
    }
}

int main(void)
{
    cin >> N >> K;

    for (int i = 0; i < N; i++)
    {
        int v, w;

        cin >> v >> w;
        V.insert(V.end(), v);
        W.insert(W.end(), w);
    }

    int ans = max(0, 0, 0);
    cout << ans << endl;
}