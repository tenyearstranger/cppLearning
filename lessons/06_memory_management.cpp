#include <iostream>
#include <fstream>
using namespace std;

/**
 * 模块6：内存管理与RAII ⭐
 * C++最重要的特性之一，区别于C/Java/Python
 */

// ============ 问题：内存泄漏 ============
class FileHandler {
private:
    char* buffer;
    int size;
    
public:
    FileHandler(int s) : size(s) {
        buffer = new char[size];  // 动态分配
        cout << "Allocated " << size << " bytes" << endl;
    }
    
    ~FileHandler() {
        delete[] buffer;  // 必须手动释放！
        cout << "Deallocated " << size << " bytes" << endl;
    }
};

// ============ RAII原则 ============
/**
 * RAII = Resource Acquisition Is Initialization
 * 
 * 核心思想：
 * - 资源（内存、文件、锁等）在构造函数中获取
 * - 资源在析构函数中释放
 * - 利用栈对象生命周期自动管理资源
 * 
 * 好处：
 * - 自动清理，不用担心遗忘
 * - 异常安全（即使抛异常也会执行析构）
 * - 不容易内存泄漏
 */

// 不好的做法（Java/Python风格）
void bad_way() {
    cout << "\n--- 不推荐的内存管理方式 ---" << endl;
    FileHandler* handler = new FileHandler(1024);
    
    // ... 一些处理 ...
    
    delete handler;  // 容易忘记！
    // 如果发生异常，delete不会执行！
}

// 好的做法（C++风格 - 栈分配）
void good_way() {
    cout << "\n--- 推荐的RAII方式 ---" << endl;
    FileHandler handler(1024);
    
    // ... 使用handler ...
    
    // 函数结束时自动调用析构函数
}

// ============ 动态数组与new[] ============
void pointer_vs_stack() {
    cout << "\n--- 栈分配 vs 堆分配 ---" << endl;
    
    // 栈分配（大小必须是编译期常量）
    int stack_arr[10];  // 快速分配
    cout << "Stack array created" << endl;
    
    // 堆分配（大小可以是运行时常量）
    int* heap_arr = new int[100];
    cout << "Heap array created" << endl;
    delete[] heap_arr;  // 数组用delete[]
    
    // 使用场景：
    // - 栈：大小已知、生命周期短、性能要求高
    // - 堆：大小未知、需要长生命周期、跨函数传递
}

// ============ 指针所有权 ============
/**
 * C++中关键概念：谁负责delete？
 * 
 * 所有权转移示例：
 */
class Node {
public:
    int data;
    Node* next;
    
    Node(int d) : data(d), next(nullptr) {}
    
    ~Node() { 
        cout << "Node deleted: " << data << endl;
    }
};

// 返回新建的对象 - 调用者负责delete
Node* createNode(int data) {
    return new Node(data);
}

// 接收指针但不获取所有权（不负责delete）
void useNode(const Node* node) {
    cout << "Using node with data: " << node->data << endl;
}

// ============ 内存错误示例 ============
void memory_errors() {
    cout << "\n--- 常见的内存错误 ---" << endl;
    
    // 1. 野指针 (Use-After-Free)
    int* ptr = new int(42);
    delete ptr;
    // cout << *ptr << endl;  // 危险！这是use-after-free
    ptr = nullptr;  // 好习惯
    
    // 2. 重复delete
    int* p = new int(10);
    delete p;
    // delete p;  // 危险！二次delete
    
    // 3. 栈缓冲区溢出
    int arr[5] = {0};
    // arr[10] = 100;  // 越界写入
    
    // 4. 内存泄漏
    int* leak = new int(100);
    // 忘记delete或者异常抛出前没delete
}

// ============ 实战：链表示例 ============
class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    ~LinkedList() {
        clear();
    }
    
    void append(int data) {
        Node* new_node = new Node(data);
        
        if (!head) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
    
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void display() {
        cout << "List: ";
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    cout << "=== 内存管理与RAII ===" << endl;
    
    // 演示RAII
    good_way();
    
    // 演示链表
    cout << "\n--- 链表示例 ---" << endl;
    {
        LinkedList list;
        list.append(1);
        list.append(2);
        list.append(3);
        list.display();
        // 作用域结束，自动清理所有内存
    }
    cout << "List destroyed automatically" << endl;
    
    return 0;
}

/**
 * RAII总结：
 * 1. 在构造函数中获取资源
 * 2. 在析构函数中释放资源
 * 3. 利用栈对象自动调用析构
 * 4. 避免manual new/delete（优先用智能指针）
 * 5. 析构函数应该不抛异常
 */
