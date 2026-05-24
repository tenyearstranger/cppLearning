#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double t;
    int n;
    
    cin >> t >> n;
    
    // 确保浮点数除法
    cout << fixed << setprecision(3) << t / (double)n << endl;
    cout << n * 2 << endl;
    
    return 0;
}