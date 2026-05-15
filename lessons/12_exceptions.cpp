#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
using namespace std;

/**
 * 模块12：异常处理
 * C++的错误处理机制
 */

// ============ 自定义异常 ============
class InsufficientFundsException : public exception {
private:
    string message;
    
public:
    InsufficientFundsException(double required, double available) {
        message = "Insufficient funds! Required: " + to_string(required) + 
                  ", Available: " + to_string(available);
    }
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// ============ 银行账户示例 ============
class BankAccount {
private:
    double balance;
    string account_number;
    
public:
    BankAccount(const string& num, double initial) 
        : account_number(num), balance(initial) {}
    
    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Amount must be positive");
        }
        
        if (amount > balance) {
            throw InsufficientFundsException(amount, balance);
        }
        
        balance -= amount;
        cout << "Withdrew: $" << amount << endl;
    }
    
    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Amount must be positive");
        }
        
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }
    
    double getBalance() const {
        return balance;
    }
    
    void display() const {
        cout << "Account " << account_number << ": $" << balance << endl;
    }
};

// ============ 异常抛出 ============
int safe_divide(int a, int b) {
    if (b == 0) {
        throw invalid_argument("Division by zero!");
    }
    return a / b;
}

// ============ 函数异常规范（C++17前） ============
// 不推荐使用，C++20已移除
void may_throw() {
    throw runtime_error("Something went wrong");
}

void wont_throw() noexcept {
    // noexcept保证这个函数不抛异常
}

// ============ 异常层级 ============
class DatabaseException : public exception {
public:
    const char* what() const noexcept override {
        return "Database error occurred";
    }
};

class ConnectionException : public DatabaseException {
public:
    const char* what() const noexcept override {
        return "Failed to connect to database";
    }
};

// ============ RAII与异常 ============
class FileHandler {
private:
    string filename;
    
public:
    FileHandler(const string& fname) : filename(fname) {
        cout << "Opening file: " << filename << endl;
    }
    
    ~FileHandler() {
        cout << "Closing file: " << filename << endl;
    }
    
    void read() {
        cout << "Reading from: " << filename << endl;
    }
};

void file_operations_demo() {
    cout << "\n--- RAII与异常安全 ---" << endl;
    
    try {
        FileHandler file("data.txt");  // 文件打开
        file.read();
        
        throw runtime_error("Simulated error");
        // FileHandler的析构函数会被调用
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
        // 即使异常发生，file的析构函数也会被调用！
    }
}

int main() {
    cout << "=== 异常处理 ===" << endl;
    
    // ============ 基本try-catch ============
    cout << "\n--- 基本异常处理 ---" << endl;
    
    try {
        int result = safe_divide(10, 2);
        cout << "10 / 2 = " << result << endl;
        
        result = safe_divide(10, 0);  // 抛异常
    } catch (const invalid_argument& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
    // ============ 多个catch块 ============
    cout << "\n--- 多个catch块 ---" << endl;
    
    try {
        cout << "Enter two numbers to divide (0 to exit): ";
        int a = 10, b = 0;  // 模拟输入
        
        int result = safe_divide(a, b);
        cout << "Result: " << result << endl;
    } catch (const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "General exception: " << e.what() << endl;
    } catch (...) {  // 捕获所有其他异常
        cout << "Unknown exception occurred" << endl;
    }
    
    // ============ 标准异常类 ============
    cout << "\n--- 标准异常类 ---" << endl;
    try {
        throw out_of_range("Index out of bounds");
    } catch (const out_of_range& e) {
        cout << "Caught: " << e.what() << endl;
    }
    
    // ============ 自定义异常 ============
    cout << "\n--- 自定义异常 ---" << endl;
    
    BankAccount account("12345", 1000);
    account.display();
    
    try {
        account.deposit(100);
        account.withdraw(500);
        account.display();
        
        account.withdraw(1000);  // 余额不足，抛异常
    } catch (const InsufficientFundsException& e) {
        cout << "Account error: " << e.what() << endl;
    } catch (const invalid_argument& e) {
        cout << "Invalid operation: " << e.what() << endl;
    }
    
    account.display();
    
    // ============ 异常的重新抛出 ============
    cout << "\n--- 异常重新抛出 ---" << endl;
    
    auto process_data = [&]() {
        try {
            throw runtime_error("Processing error");
        } catch (const exception& e) {
            cout << "Caught in inner try: " << e.what() << endl;
            throw;  // 重新抛出同一个异常
        }
    };
    
    try {
        process_data();
    } catch (const exception& e) {
        cout << "Caught in outer try: " << e.what() << endl;
    }
    
    // ============ 异常层级 ============
    cout << "\n--- 异常层级与多态 ---" << endl;
    
    try {
        throw ConnectionException();
    } catch (const DatabaseException& e) {
        cout << "Database-related error: " << e.what() << endl;
    }
    
    // ============ noexcept函数 ============
    cout << "\n--- noexcept函数 ---" << endl;
    
    try {
        wont_throw();  // 这个函数保证不抛异常
        cout << "wont_throw() executed successfully" << endl;
    } catch (const exception& e) {
        cout << "This won't be printed" << endl;
    }
    
    // ============ 容器异常 ============
    cout << "\n--- 容器异常 ---" << endl;
    
    vector<int> vec = {1, 2, 3};
    
    try {
        // 注意：operator[]不检查边界
        cout << "vec[1] = " << vec[1] << endl;
        
        // at()会检查边界
        cout << "vec.at(10) = " << vec.at(10) << endl;
    } catch (const out_of_range& e) {
        cout << "Out of range: " << e.what() << endl;
    }
    
    // ============ RAII与异常安全 ============
    file_operations_demo();
    
    // ============ 异常安全保证 ============
    cout << "\n--- 异常安全保证级别 ---" << endl;
    cout << "1. No-throw guarantee: 不抛异常" << endl;
    cout << "2. Strong guarantee: 事务性，全部成功或全部失败" << endl;
    cout << "3. Basic guarantee: 资源不泄漏，状态有效但未知" << endl;
    cout << "4. No guarantee: 无法预知状态" << endl;
    
    // ============ 异常与性能 ============
    cout << "\n--- 异常与性能 ---" << endl;
    cout << "1. 异常在非常见路径上性能最好（平时零开销）" << endl;
    cout << "2. 异常发生时会有性能开销（栈展开等）" << endl;
    cout << "3. 不要用异常做控制流" << endl;
    cout << "4. 用异常处理真正的错误" << endl;
    
    return 0;
}

/**
 * 异常处理最佳实践：
 * 1. 按值抛出异常，按const引用捕获
 * 2. 创建异常层级（继承std::exception）
 * 3. 提供有意义的what()信息
 * 4. 使用RAII确保资源清理（析构函数中）
 * 5. 标记noexcept的函数不能抛异常
 * 6. 避免在析构函数中抛异常
 * 7. 不要用异常做正常的控制流
 * 
 * 标准异常类：
 * - logic_error: 逻辑错误
 *   - invalid_argument: 无效参数
 *   - out_of_range: 越界
 *   - length_error: 长度错误
 * - runtime_error: 运行时错误
 *   - range_error: 范围错误
 *   - overflow_error: 溢出错误
 *   - underflow_error: 下溢错误
 */
