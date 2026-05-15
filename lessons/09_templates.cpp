#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

/**
 * 模块9：模板与泛型编程 ⭐
 * C++强大的compile-time编程能力
 */

// ============ 函数模板 ============
template<typename T>
T max_value(T a, T b) {
    return (a > b) ? a : b;
}

// 多参数模板
template<typename T, typename U>
void print_pair(T first, U second) {
    cout << "First: " << first << ", Second: " << second << endl;
}

// 模板特化（针对特定类型的专门实现）
template<>
void print_pair<string, int>(string first, int second) {
    cout << "String: " << first << ", Integer: " << second << endl;
}

// ============ 类模板 ============
template<typename T>
class Stack {
private:
    vector<T> data;
    
public:
    void push(const T& value) {
        data.push_back(value);
    }
    
    T pop() {
        T value = data.back();
        data.pop_back();
        return value;
    }
    
    bool empty() const {
        return data.empty();
    }
    
    int size() const {
        return data.size();
    }
};

// ============ 模板参数：类型参数 ============
template<typename T, typename U = int>  // U有默认值
class Pair {
public:
    T first;
    U second;
    
    Pair(T f, U s) : first(f), second(s) {}
};

// ============ 模板参数：非类型参数 ============
template<int SIZE>
class Buffer {
private:
    char data[SIZE];  // 大小在编译期就确定
    
public:
    int capacity() const {
        return SIZE;
    }
};

// ============ 可变参数模板（C++11） ============
// 递归基(终止条件)
void print_args() {
    cout << endl;
}

// 递归情况
template<typename T, typename... Args>
void print_args(T first, Args... rest) {
    cout << first << " ";
    print_args(rest...);
}

// ============ 完美转发与模板 ============
template<typename T>
void wrapper(T&& arg) {
    // forward保留参数的值类别（左值/右值）
    cout << "Received: " << arg << endl;
}

// ============ 概念验证（C++20） ============
// template<typename T>
// concept Comparable = requires(T a, T b) {
//     { a < b } -> convertible_to<bool>;
// };

// template<Comparable T>
// T minimum(T a, T b) {
//     return a < b ? a : b;
// }

// ============ 模板元编程示例 ============
// 编译期计算阶乘
template<int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static const int value = 1;
};

// ============ 通用迭代器示例 ============
template<typename Iterator, typename T>
Iterator find(Iterator begin, Iterator end, const T& value) {
    while (begin != end) {
        if (*begin == value) {
            return begin;
        }
        ++begin;
    }
    return end;
}

// ============ 类模板的成员函数实现 ============
template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    
    Node* head;
    
public:
    List() : head(nullptr) {}
    
    ~List() {
        clear();
    }
    
    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
    }
    
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    template<typename Func>
    void forEach(Func func) {
        Node* current = head;
        while (current) {
            func(current->data);
            current = current->next;
        }
    }
};

int main() {
    cout << "=== 模板与泛型编程 ===" << endl;
    
    // ============ 函数模板 ============
    cout << "\n--- 函数模板 ---" << endl;
    cout << "Max of 3 and 7: " << max_value(3, 7) << endl;
    cout << "Max of 3.5 and 2.1: " << max_value(3.5, 2.1) << endl;
    cout << "Max of 'A' and 'Z': " << max_value('A', 'Z') << endl;
    
    print_pair(10, 3.14);
    print_pair("Alice", 25);  // 特化版本
    
    // ============ 类模板 ============
    cout << "\n--- 类模板（Stack） ---" << endl;
    Stack<int> int_stack;
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    
    cout << "Stack size: " << int_stack.size() << endl;
    while (!int_stack.empty()) {
        cout << "Pop: " << int_stack.pop() << endl;
    }
    
    // ============ 字符串栈 ============
    cout << "\n--- 字符串栈 ---" << endl;
    Stack<string> string_stack;
    string_stack.push("First");
    string_stack.push("Second");
    
    while (!string_stack.empty()) {
        cout << "Pop: " << string_stack.pop() << endl;
    }
    
    // ============ 模板参数默认值 ============
    cout << "\n--- 模板参数默认值 ---" << endl;
    Pair<string> p1("Alice", 25);  // U使用默认的int
    cout << p1.first << ": " << p1.second << endl;
    
    Pair<string, double> p2("Height", 1.75);
    cout << p2.first << ": " << p2.second << endl;
    
    // ============ 非类型参数 ============
    cout << "\n--- 非类型参数 ---" << endl;
    Buffer<256> small_buf;
    Buffer<1024> large_buf;
    cout << "Small buffer capacity: " << small_buf.capacity() << endl;
    cout << "Large buffer capacity: " << large_buf.capacity() << endl;
    
    // ============ 可变参数模板 ============
    cout << "\n--- 可变参数模板 ---" << endl;
    print_args("Hello", 42, 3.14, true);
    
    // ============ 编译期计算 ============
    cout << "\n--- 编译期计算 ---" << endl;
    cout << "5! = " << Factorial<5>::value << endl;
    cout << "10! = " << Factorial<10>::value << endl;
    
    // ============ 通用Find ============
    cout << "\n--- 通用查找 ---" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    auto it = find(vec.begin(), vec.end(), 3);
    if (it != vec.end()) {
        cout << "Found: " << *it << endl;
    }
    
    // ============ 模板列表 ============
    cout << "\n--- 模板列表 ---" << endl;
    List<int> int_list;
    int_list.push_front(1);
    int_list.push_front(2);
    int_list.push_front(3);
    
    cout << "List elements: ";
    int_list.forEach([](int x) { cout << x << " "; });
    cout << endl;
    
    return 0;
}

/**
 * 模板关键概念：
 * 1. 模板是编译期代码生成
 * 2. 类型参数(typename)和非类型参数
 * 3. 函数模板和类模板
 * 4. 模板特化和偏特化
 * 5. SFINAE (Substitution Failure Is Not An Error)
 * 6. 可变参数模板
 * 7. 模板元编程
 * 
 * 与其他语言对比：
 * - Java: 泛型在运行时被擦除，类型信息丢失
 * - C++: 模板在编译时展开，完整的类型检查
 * - Python: 没有编译期类型检查
 */
