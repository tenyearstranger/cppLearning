#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

/**
 * 模块16：Lambda表达式
 * 匿名函数，C++11引入
 */

// ============ 基本Lambda语法 ============
/**
 * [captures](parameters) -> return_type { body }
 * 
 * captures: 捕获列表
 * - []: 不捕获任何变量
 * - [=]: 捕获所有左值变量（按值）
 * - [&]: 捕获所有左值变量（按引用）
 * - [&, =]: 混合方式
 * - [x, &y]: 具体指定
 * 
 * return_type: 返回类型（通常可省略，编译器推导）
 */

int main() {
    cout << "=== Lambda表达式 ===" << endl;
    
    // ============ 最简单的lambda ============
    cout << "\n--- 最简单的lambda ---" << endl;
    auto greet = []() { cout << "Hello, Lambda!" << endl; };
    greet();
    
    // ============ Lambda参数与返回值 ============
    cout << "\n--- 参数与返回值 ---" << endl;
    auto add = [](int a, int b) { return a + b; };
    cout << "5 + 3 = " << add(5, 3) << endl;
    
    auto multiply = [](int a, int b) -> int {
        cout << "Multiplying " << a << " and " << b << endl;
        return a * b;
    };
    cout << "4 * 6 = " << multiply(4, 6) << endl;
    
    // ============ 捕获变量 ============
    cout << "\n--- 捕获变量 ---" << endl;
    int x = 10, y = 20;
    
    // 按值捕获
    auto capture_by_value = [x, y]() {
        cout << "x=" << x << ", y=" << y << endl;
    };
    x = 100;  // 改变原变量
    capture_by_value();  // 输出仍是10, 20
    
    // 按引用捕获
    auto capture_by_ref = [&x, &y]() {
        cout << "x=" << x << ", y=" << y << endl;
    };
    capture_by_ref();  // 输出100, 20
    
    // 修改捕获的引用变量
    auto modify_ref = [&x]() { x = 200; };
    modify_ref();
    cout << "After lambda, x=" << x << endl;
    
    // ============ 捕获所有变量 ============
    cout << "\n--- 捕获所有变量 ---" << endl;
    int a = 5, b = 15;
    
    auto all_by_value = [=]() {
        cout << "By value: a=" << a << ", b=" << b << endl;
    };
    
    auto all_by_ref = [&]() {
        cout << "By reference: a=" << a << ", b=" << b << endl;
    };
    
    all_by_value();
    all_by_ref();
    
    // ============ mutable lambda ============
    cout << "\n--- mutable lambda ---" << endl;
    int counter = 0;
    auto count_up = [counter]() mutable {
        counter++;
        cout << "Counter: " << counter << endl;
    };
    
    count_up();  // 1
    count_up();  // 2
    cout << "Original counter: " << counter << endl;  // 0（未改变）
    
    // ============ Lambda与STL算法 ============
    cout << "\n--- Lambda与STL算法 ---" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // sort
    cout << "Sorting in descending order: ";
    sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b;
    });
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // find_if
    cout << "Finding first even number: ";
    auto even = find_if(numbers.begin(), numbers.end(), 
                       [](int n) { return n % 2 == 0; });
    if (even != numbers.end()) {
        cout << *even << endl;
    }
    
    // transform
    cout << "Doubling all numbers: ";
    vector<int> doubled;
    transform(numbers.begin(), numbers.end(),
             back_inserter(doubled),
             [](int n) { return n * 2; });
    for (int n : doubled) cout << n << " ";
    cout << endl;
    
    // count_if
    int even_count = count_if(numbers.begin(), numbers.end(),
                             [](int n) { return n % 2 == 0; });
    cout << "Even numbers count: " << even_count << endl;
    
    // ============ Lambda捕获初始化 ============
    cout << "\n--- Lambda捕获初始化(C++14) ---" << endl;
    auto make_counter = [n = 0]() mutable {
        return ++n;
    };
    
    cout << "Counter: " << make_counter() << endl;  // 1
    cout << "Counter: " << make_counter() << endl;  // 2
    
    // ============ 使用reference wrapper ============
    cout << "\n--- reference_wrapper ---" << endl;
    int value = 42;
    vector<int> nums = {1, 2, 3, 4, 5};
    
    auto has_value = [value](int n) { return n == value; };
    if (find_if(nums.begin(), nums.end(), has_value) != nums.end()) {
        cout << "Found " << value << " in vector" << endl;
    }
    
    // ============ 递归Lambda ============
    cout << "\n--- 递归Lambda(需要function包装) ---" << endl;
    
    function<int(int)> factorial = [&factorial](int n) -> int {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    };
    
    cout << "5! = " << factorial(5) << endl;
    
    // ============ Lambda作为回调 ============
    cout << "\n--- Lambda作为回调 ---" << endl;
    
    auto process_data = [](vector<int>& data, 
                          function<void(int&)> callback) {
        for (auto& item : data) {
            callback(item);
        }
    };
    
    vector<int> data = {1, 2, 3, 4};
    process_data(data, [](int& n) { n *= 2; });
    
    cout << "Doubled data: ";
    for (int n : data) cout << n << " ";
    cout << endl;
    
    // ============ Generic Lambda(C++14) ============
    cout << "\n--- Generic Lambda(C++14) ---" << endl;
    
    auto generic_add = [](auto a, auto b) {
        return a + b;
    };
    
    cout << "1 + 2 = " << generic_add(1, 2) << endl;
    cout << "1.5 + 2.5 = " << generic_add(1.5, 2.5) << endl;
    cout << "\"Hello\" + \"World\" = " << generic_add(string("Hello"), string("World")) << endl;
    
    // ============ Lambda对象的大小 ============
    cout << "\n--- Lambda对象大小 ---" << endl;
    auto simple = []() {};
    auto with_capture = [x, y]() {};
    
    cout << "Size of lambda without capture: " << sizeof(simple) << " bytes" << endl;
    cout << "Size of lambda with capture: " << sizeof(with_capture) << " bytes" << endl;
    
    // ============ 使用std::function ============
    cout << "\n--- std::function ---" << endl;
    
    vector<function<int(int)>> functions;
    functions.push_back([](int n) { return n * 2; });
    functions.push_back([](int n) { return n + 10; });
    functions.push_back([](int n) { return n * n; });
    
    int test_val = 5;
    for (size_t i = 0; i < functions.size(); i++) {
        cout << "Function " << i << "(5) = " << functions[i](test_val) << endl;
    }
    
    cout << "\n=== Lambda总结 ===" << endl;
    cout << "1. Lambda是匿名函数，编译器生成一个类" << endl;
    cout << "2. 捕获列表控制外部变量的访问方式" << endl;
    cout << "3. 与STL算法完美配合" << endl;
    cout << "4. 类型由编译器推导，避免函数指针开销" << endl;
    cout << "5. Generic lambda提供模板能力" << endl;
    
    return 0;
}

/**
 * Lambda vs 传统函数对象：
 * 传统方式：
 * struct Add {
 *     int operator()(int a, int b) const { return a + b; }
 * };
 * Add add_op;
 * add_op(1, 2);
 * 
 * Lambda方式：
 * auto add = [](int a, int b) { return a + b; };
 * add(1, 2);
 * 
 * Lambda更简洁，编译器能更好地优化
 */
