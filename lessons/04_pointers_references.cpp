#include <iostream>
using namespace std;

/**
 * 模块4：指针与引用 ⭐
 * C++最重要的概念之一，与C类似但更复杂
 */

int main() {
    cout << "=== 指针与引用 ===" << endl;
    
    // ============ 1. 指针基础 ============
    cout << "\n--- 指针基础 ---" << endl;
    int x = 10;
    int* ptr = &x;  // 指针保存变量地址
    
    cout << "x = " << x << endl;
    cout << "Address of x: " << &x << endl;
    cout << "ptr = " << ptr << endl;
    cout << "Dereference ptr: " << *ptr << endl;
    
    *ptr = 20;  // 通过指针修改值
    cout << "After *ptr = 20, x = " << x << endl;
    
    // ============ 2. 引用（C++特有！） ============
    cout << "\n--- 引用 ---" << endl;
    int y = 30;
    int& ref = y;  // 引用必须初始化，是别名
    
    cout << "y = " << y << endl;
    cout << "ref = " << ref << endl;
    cout << "Address of y: " << &y << endl;
    cout << "Address of ref: " << &ref << " (同一个!)" << endl;
    
    ref = 40;  // 修改引用实际修改原变量
    cout << "After ref = 40, y = " << y << endl;
    
    // ============ 3. 指针vs引用 ============
    cout << "\n--- 指针 vs 引用 ---" << endl;
    /*
     * 指针：
     * - 可以为nullptr
     * - 可以重新指向其他变量
     * - 占用内存存储地址
     * - 可以进行指针算术(ptr++)
     * - 需要解引用(*)访问值
     * 
     * 引用：
     * - 不能为null
     * - 不能改变指向的对象
     * - 不占用额外内存（是别名）
     * - 不能进行算术运算
     * - 自动解引用，直接使用
     */
    
    // ============ 4. 常指针与指针常量 ============
    cout << "\n--- const指针 ---" << endl;
    int a = 100;
    int b = 200;
    
    // const指针：指向的内容不能改
    const int* const_ptr = &a;
    // *const_ptr = 150;  // ERROR
    const_ptr = &b;  // 可以，指针本身可以改
    
    // 指针常量：指针本身不能改
    int* const ptr_const = &a;
    *ptr_const = 150;  // 可以，内容可以改
    // ptr_const = &b;  // ERROR
    
    cout << "const int* 和 int* const 用法示例完成" << endl;
    
    // ============ 5. 空指针 ============
    cout << "\n--- 空指针 ---" << endl;
    int* null_ptr = nullptr;  // C++11推荐（不要用NULL）
    
    if (null_ptr == nullptr) {
        cout << "ptr is nullptr" << endl;
    }
    
    // ============ 6. 指针的指针 ============
    cout << "\n--- 指针的指针 ---" << endl;
    int c = 50;
    int* ptr1 = &c;
    int** ptr2 = &ptr1;  // 指向指针的指针
    
    cout << "c = " << c << endl;
    cout << "*ptr1 = " << *ptr1 << endl;
    cout << "**ptr2 = " << **ptr2 << endl;
    
    // ============ 7. 数组指针 ============
    cout << "\n--- 数组指针 ---" << endl;
    int arr[] = {10, 20, 30};
    int* arr_ptr = arr;  // 数组退化为指向第一个元素的指针
    
    cout << "arr[0] = " << arr[0] << ", *arr_ptr = " << *arr_ptr << endl;
    cout << "arr[1] = " << arr[1] << ", *(arr_ptr+1) = " << *(arr_ptr+1) << endl;
    cout << "arr[2] = " << arr[2] << ", *(arr_ptr+2) = " << *(arr_ptr+2) << endl;
    
    // ============ 8. 引用作为函数参数 ============
    cout << "\n--- 引用在函数中的应用 ---" << endl;
    
    auto swap_by_ref = [](int& x, int& y) {
        int temp = x;
        x = y;
        y = temp;
    };
    
    int m = 5, n = 10;
    cout << "Before swap: m=" << m << ", n=" << n << endl;
    swap_by_ref(m, n);
    cout << "After swap: m=" << m << ", n=" << n << endl;
    
    return 0;
}

/**
 * 关键概念总结：
 * 1. 指针存储地址，引用是别名
 * 2. 引用更安全（不能为空，不能改变指向）
 * 3. 引用通常用于函数参数和返回值
 * 4. const和指针/引用的组合要仔细理解
 */
