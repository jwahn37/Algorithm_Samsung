#include <iostream>
#include <algorithm>
using namespace std;
 
typedef double db;
 
int t, n;
db x[10], m[10];
 
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << fixed;
    cout.precision(10);
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> x[i];
        for (int i = 0; i < n; ++i) 
            cin >> m[i];
        cout << "#" << tc << " ";
        for (int i = 0; i < n - 1; ++i) {
            db l = x[i], r = x[i + 1], ans = 0;
            for (int k = 0; k < 50; ++k) {
                db mid = (l + r) / 2;
                db s = 0;
                for (int j = 0; j <= i; ++j) 
                    s += m[j] / ((mid - x[j])*(mid - x[j]));
                for (int j = i + 1; j < n; ++j) 
                    s -= m[j] / ((mid - x[j])*(mid - x[j]));
                if (s > 0) {
                    l = mid;
                }
                else {
                    ans = mid;
                    r = mid;
                }
            }
            cout << ans << " ";
        }
        cout << '\n';
        //cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}
