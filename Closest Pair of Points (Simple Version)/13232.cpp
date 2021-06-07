#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    int T;

    cout << fixed << setprecision(8);

    cin >> T;

    while (T--)
    {
        int P, c_x = 0, c_y = 0;

        cin >> P;
        int A[P];
        int B[P];

        for (int i = 0; i < 2 * P; i++)
        {
            int X, Y;
            cin >> X >> Y;

            if (X > 0)
            {
                A[c_x] = X;
                c_x++;
            }
            else if (X < 0)
            {
                A[c_x] = (-1) * X;
                c_x++;
            }
            else if (Y > 0)
            {
                B[c_y] = Y;
                c_y++;
            }
            else
            {
                B[c_y] = (-1) * Y;
                c_y++;
            }
        }
        sort(A, A + P);
        sort(B, B + P);

        double sum = 0.0;

        for (int i = 0; i < P; i++)
        {
            sum += sqrt(pow((double)A[i], 2) + pow((double)B[i], 2));
        }
        cout << sum << endl;
    }
    return 0;
}