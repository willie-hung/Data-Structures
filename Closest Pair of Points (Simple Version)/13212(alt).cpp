#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
using namespace std;
int main()
{
    int T, N, i, j, tmp1, tmp2;
    double ans = 0.0;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        ans = 0.0;
        cin >> N;
        int *x = new int[N];
        int *y = new int[N];
        for (int tt = 0, i = 0, j = 0; tt < 2 * N; tt++)
        {
            cin >> tmp1 >> tmp2;
            if (tmp1 == 0)
                y[j++] = abs(tmp2);
            else
                x[i++] = abs(tmp1);
        }

        sort(x, x + N - 1);
        sort(y, y + N - 1);

        for (int tt = 0; tt < N; tt++)
            ans += sqrt(pow(x[tt], 2) + pow(y[tt], 2));

        cout << fixed << showpoint << setprecision(8);
        cout << ans << endl;
        delete x;
        delete y;
    }
}
