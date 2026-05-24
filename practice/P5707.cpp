#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Time {
private:
    int time;  // 总分钟数 (0-1439)
    
    // 规范化时间到 0-1439
    void normalize() {
        time = ((time % 1440) + 1440) % 1440;
    }
    
public:
    Time(int h = 0, int m = 0) : time(h * 60 + m) {
        normalize();
    }
    
    // 减去一定分钟数
    void subtract(int minutes) {
        time -= minutes;
        normalize();
    }
    
    void print() const {
        int hour = time / 60;
        int minute = time % 60;
        cout << setw(2) << setfill('0') << hour << ":"
             << setw(2) << setfill('0') << minute;
    }
};

int main() {
    int s, v;
    cin >> s >> v;
    
    int need = ceil((double)s / v) + 10;
    
    Time start(8, 0);
    start.subtract(need);
    start.print();
    
    return 0;
}