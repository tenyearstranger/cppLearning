#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <variant>
#include <string_view>
using namespace std;

/**
 * 模块17：现代C++特性
 * C++11/14/17/20 的各种特性
 */

// ============ auto与类型推导 ============
/**
 * C++11引入auto，让编译器推导类型
 * 好处：
 * - 代码更简洁
 * - 重构时自动适应
 * - 避免写长的类型名称
 */

void auto_demo() {
    cout << "\n--- auto类型推导 ---" << endl;
    
    auto age = 25;                    // int
    auto height = 1.75;               // double
    auto name = "Alice";              // const char*
    auto numbers = vector<int>{1,2,3};  // vector<int>
    
    // decltype获取表达式的类型
    decltype(age) same_as_age = 30;   // int
    
    auto& ref = age;                  // int&
    auto* ptr = &age;                 // int*
    
    cout << "Auto types deduced correctly" << endl;
}

// ============ 范围for循环 ============
void range_for_demo() {
    cout << "\n--- 范围for循环 ---" << endl;
    
    vector<int> nums = {1, 2, 3, 4, 5};
    
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    
    // 修改容器元素
    for (auto& num : nums) {
        num *= 2;
    }
    
    cout << "Doubled: ";
    for (auto num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

// ============ 列表初始化 ============
void list_initialization() {
    cout << "\n--- 列表初始化 ---" << endl;
    
    vector<int> v1{1, 2, 3, 4};      // 初始化列表
    vector<int> v2 = {5, 6, 7, 8};   // 等价的形式
    
    map<string, int> age_map{
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };
    
    // 防止类型转换错误
    int x{10};  // OK
    // int y{3.14};  // ERROR: 不允许缩窄转换
    
    cout << "List initialization works" << endl;
}

// ============ nullptr ============
void nullptr_demo() {
    cout << "\n--- nullptr ---" << endl;
    
    int* ptr1 = nullptr;     // C++11推荐
    // int* ptr2 = NULL;     // 旧风格，容易混淆
    // int* ptr3 = 0;        // 也可以但不清晰
    
    if (ptr1 == nullptr) {
        cout << "ptr1 is null" << endl;
    }
}

// ============ constexpr ============
constexpr int square(int x) {
    return x * x;
}

void constexpr_demo() {
    cout << "\n--- constexpr ---" << endl;
    
    // 编译期计算
    constexpr int result = square(5);  // 编译时计算，效率高
    cout << "5^2 = " << result << endl;
    
    // constexpr变量必须用常量表达式初始化
    constexpr int size = 10;
    int arr[size];  // 可以用constexpr作为数组大小
}

// ============ std::optional ============
std::optional<int> find_value(const vector<int>& v, int target) {
    for (int val : v) {
        if (val == target) {
            return val;
        }
    }
    return std::nullopt;  // 返回"无值"
}

void optional_demo() {
    cout << "\n--- std::optional(C++17) ---" << endl;
    
    vector<int> nums = {1, 2, 3, 4, 5};
    
    auto result1 = find_value(nums, 3);
    if (result1.has_value()) {
        cout << "Found: " << result1.value() << endl;
    }
    
    auto result2 = find_value(nums, 10);
    if (!result2.has_value()) {
        cout << "Not found" << endl;
    }
    
    // 使用value_or
    cout << "Result or default: " << result2.value_or(-1) << endl;
}

// ============ std::variant ============
/**
 * variant是type-safe的联合体
 * 比void*更安全，比union更易用
 */
std::variant<int, double, std::string> get_data(int type) {
    switch (type) {
        case 1: return 42;
        case 2: return 3.14;
        default: return "Hello";
    }
}

void variant_demo() {
    cout << "\n--- std::variant(C++17) ---" << endl;
    
    auto data1 = get_data(1);
    auto data2 = get_data(2);
    auto data3 = get_data(3);
    
    // 使用std::get访问
    cout << "Int: " << std::get<int>(data1) << endl;
    cout << "Double: " << std::get<double>(data2) << endl;
    cout << "String: " << std::get<std::string>(data3) << endl;
    
    // 或使用std::visit
    auto visitor = [](auto& val) {
        cout << "Value: " << val << endl;
    };
    
    std::visit(visitor, data1);
    std::visit(visitor, data2);
    std::visit(visitor, data3);
}

// ============ 结构化绑定 ============
struct Point {
    int x, y;
};

tuple<int, string, double> get_tuple() {
    return {42, "answer", 3.14};
}

void structured_binding_demo() {
    cout << "\n--- 结构化绑定(C++17) ---" << endl;
    
    // 绑定结构体成员
    Point p = {10, 20};
    auto [x, y] = p;
    cout << "Point: (" << x << ", " << y << ")" << endl;
    
    // 绑定元组
    auto [num, text, pi] = get_tuple();
    cout << "Tuple: " << num << ", " << text << ", " << pi << endl;
    
    // 绑定map
    map<string, int> ages = {{"Alice", 25}, {"Bob", 30}};
    for (auto [name, age] : ages) {
        cout << name << ": " << age << endl;
    }
}

// ============ 初始化器列表 ============
class Container {
private:
    vector<int> data;
    
public:
    Container(initializer_list<int> list) : data(list) {}
    
    void print() const {
        for (int x : data) {
            cout << x << " ";
        }
        cout << endl;
    }
};

void initializer_list_demo() {
    cout << "\n--- initializer_list ---" << endl;
    
    Container c{10, 20, 30, 40};
    cout << "Container: ";
    c.print();
}

// ============ 右值引用与转移语义 ============
void move_semantics_recap() {
    cout << "\n--- 右值引用与std::move ---" << endl;
    
    vector<string> v1 = {"a", "b", "c"};
    vector<string> v2 = move(v1);  // 移动而不是拷贝
    
    cout << "v1.size() = " << v1.size() << " (emptied)" << endl;
    cout << "v2.size() = " << v2.size() << endl;
}

// ============ 折叠表达式 ============
// C++17
template<typename... Args>
int sum(Args... args) {
    return (args + ...);  // 折叠表达式
}

void fold_expressions() {
    cout << "\n--- 折叠表达式(C++17) ---" << endl;
    
    cout << "sum(1, 2, 3, 4, 5) = " << sum(1, 2, 3, 4, 5) << endl;
    cout << "sum(10, 20) = " << sum(10, 20) << endl;
}

// ============ std::string_view ============
void string_view_demo() {
    cout << "\n--- std::string_view(C++17) ---" << endl;
    
    std::string full_string = "Hello World";
    
    // string_view是一个轻量级的字符串视图
    std::string_view view = full_string;
    cout << "View: " << view << endl;
    cout << "View size: " << view.size() << endl;
    
    // 不需要复制就能操作子串
    std::string_view substring = view.substr(0, 5);
    cout << "Substring: " << substring << endl;
}

// ============ if constexpr ============
template<typename T>
void print_type(T value) {
    if constexpr (std::is_integral<T>::value) {
        cout << "Integer: " << value << endl;
    } else if constexpr (std::is_floating_point<T>::value) {
        cout << "Float: " << value << endl;
    }
}

void if_constexpr_demo() {
    cout << "\n--- if constexpr(C++17) ---" << endl;
    
    print_type(42);
    print_type(3.14);
}

int main() {
    cout << "=== 现代C++特性 ===" << endl;
    
    auto_demo();
    range_for_demo();
    list_initialization();
    nullptr_demo();
    constexpr_demo();
    optional_demo();
    variant_demo();
    structured_binding_demo();
    initializer_list_demo();
    move_semantics_recap();
    fold_expressions();
    string_view_demo();
    if_constexpr_demo();
    
    cout << "\n=== 现代C++特性总结 ===" << endl;
    cout << "C++11新特性：" << endl;
    cout << "  - auto, nullptr, constexpr" << endl;
    cout << "  - 右值引用, 移动语义" << endl;
    cout << "  - Lambda表达式" << endl;
    cout << "  - 变参模板, decltype" << endl;
    cout << "  - 列表初始化" << endl;
    
    cout << "\nC++14新特性：" << endl;
    cout << "  - 泛型lambda" << endl;
    cout << "  - Lambda捕获初始化" << endl;
    cout << "  - auto返回类型推导" << endl;
    
    cout << "\nC++17新特性：" << endl;
    cout << "  - std::optional" << endl;
    cout << "  - std::variant" << endl;
    cout << "  - 结构化绑定" << endl;
    cout << "  - if constexpr" << endl;
    cout << "  - 折叠表达式" << endl;
    cout << "  - std::string_view" << endl;
    
    cout << "\nC++20新特性（预览）：" << endl;
    cout << "  - Concepts" << endl;
    cout << "  - Coroutines" << endl;
    cout << "  - Ranges" << endl;
    cout << "  - 模块系统" << endl;
    
    return 0;
}

/**
 * 现代C++的演进：
 * - C++98: 第一个标准版本
 * - C++11: 大幅改进（最重要！）
 * - C++14: 细微改进
 * - C++17: 实用特性增加
 * - C++20: 重大改进（概念系统）
 * - C++23: 正在工作中...
 */
