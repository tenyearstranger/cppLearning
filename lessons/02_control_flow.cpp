#include <iostream>
#include <string>
using namespace std;

/**
 * 模块2：控制流
 * if/else, switch, for, while等基本控制结构
 */

int main() {
    cout << "=== 控制流 ===" << endl;
    
    // ============ if-else语句 ============
    cout << "\n--- if-else ---" << endl;
    int score = 85;
    
    if (score >= 90) {
        cout << "Grade: A" << endl;
    } else if (score >= 80) {
        cout << "Grade: B" << endl;
    } else if (score >= 70) {
        cout << "Grade: C" << endl;
    } else {
        cout << "Grade: F" << endl;
    }
    
    // ============ switch语句 ============
    cout << "\n--- switch ---" << endl;
    int day = 3;
    
    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        default:
            cout << "Other day" << endl;
    }
    
    // ============ 三元操作符 ============
    cout << "\n--- 三元操作符 ---" << endl;
    int age = 20;
    string status = (age >= 18) ? "Adult" : "Minor";
    cout << "Age: " << age << ", Status: " << status << endl;
    
    // ============ for循环 ============
    cout << "\n--- for循环 ---" << endl;
    cout << "Counting 1 to 5: ";
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    // ============ while循环 ============
    cout << "\n--- while循环 ---" << endl;
    int count = 0;
    while (count < 3) {
        cout << "Count: " << count << endl;
        count++;
    }
    
    // ============ do-while循环 ============
    cout << "\n--- do-while循环 ---" << endl;
    int n = 0;
    do {
        cout << "n = " << n << endl;
        n++;
    } while (n < 3);
    
    // ============ break与continue ============
    cout << "\n--- break与continue ---" << endl;
    cout << "Numbers except 3: ";
    for (int i = 1; i <= 5; i++) {
        if (i == 3) continue;  // 跳过本次迭代
        cout << i << " ";
    }
    cout << endl;
    
    cout << "Stop at 3: ";
    for (int i = 1; i <= 5; i++) {
        if (i == 3) break;  // 退出循环
        cout << i << " ";
    }
    cout << endl;
    
    // ============ goto（不推荐！） ============
    cout << "\n--- goto（演示用，不推荐在实际代码中使用） ---" << endl;
    int x = 0;
    cout << "Start" << endl;
    
    if (x == 0) {
        cout << "x is 0" << endl;
        goto end;  // 跳转到end标签
    }
    
    cout << "This won't be printed" << endl;
    
end:
    cout << "End of goto demo" << endl;
    
    // ============ 嵌套控制结构 ============
    cout << "\n--- 嵌套控制结构 ---" << endl;
    cout << "Multiplication table (3x3):" << endl;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << i * j << " ";
        }
        cout << endl;
    }
    
    // ============ 标签goto的正确用法（错误处理） ============
    cout << "\n--- 使用goto进行错误处理（C风格，C++中优先用异常） ---" << endl;
    FILE* file = nullptr;
    
    file = fopen("test.txt", "r");
    if (!file) {
        cout << "File open failed" << endl;
        // goto cleanup;
    }
    
    // ... 处理文件 ...
    
    // cleanup:
    // if (file) fclose(file);
    
    return 0;
}

/**
 * 控制流总结：
 * 1. if-else: 条件分支
 * 2. switch: 多分支选择
 * 3. for: 计数循环
 * 4. while: 条件循环
 * 5. do-while: 至少执行一次的循环
 * 6. break: 退出循环
 * 7. continue: 跳过本次迭代
 * 
 * 最佳实践：
 * - 优先使用if/else而不是goto
 * - switch比if-else链更清晰
 * - 避免使用goto（goto是反面教材）
 * - 使用异常处理错误而不是goto
 */
