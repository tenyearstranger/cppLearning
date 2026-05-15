#include <iostream>
#include <memory>  // 智能指针在这里
#include <vector>
#include <fstream>
using namespace std;

/**
 * 模块14：智能指针 ⭐
 * 现代C++推荐的内存管理方式
 */

class Resource {
public:
    string name;
    
    Resource(const string& n) : name(n) {
        cout << "Resource created: " << name << endl;
    }
    
    ~Resource() {
        cout << "Resource destroyed: " << name << endl;
    }
    
    void use() {
        cout << "Using resource: " << name << endl;
    }
};

// ============ unique_ptr 示例 ============
void unique_ptr_demo() {
    cout << "\n--- unique_ptr (独占所有权) ---" << endl;
    
    // 创建unique_ptr
    unique_ptr<Resource> ptr1(new Resource("Resource1"));
    ptr1->use();
    
    // C++14+ 推荐用make_unique
    auto ptr2 = make_unique<Resource>("Resource2");
    ptr2->use();
    
    // 所有权转移（move语义）
    unique_ptr<Resource> ptr3 = move(ptr2);
    // ptr2 现在为nullptr！
    if (!ptr2) {
        cout << "ptr2 is now empty" << endl;
    }
    
    ptr3->use();
    
    // 函数作用域结束，ptr1和ptr3自动delete
    cout << "Exiting unique_ptr_demo scope..." << endl;
}

// ============ shared_ptr 示例 ============
void shared_ptr_demo() {
    cout << "\n--- shared_ptr (共享所有权) ---" << endl;
    
    {
        auto ptr1 = make_shared<Resource>("SharedResource");
        cout << "ptr1 reference count: " << ptr1.use_count() << endl;
        
        {
            auto ptr2 = ptr1;  // 共享所有权
            cout << "After creating ptr2, reference count: " << ptr1.use_count() << endl;
            
            auto ptr3 = ptr1;  // 再共享
            cout << "After creating ptr3, reference count: " << ptr1.use_count() << endl;
            
            ptr1->use();
            // ptr3和ptr2离开作用域
        }
        
        cout << "After ptr2, ptr3 out of scope, reference count: " << ptr1.use_count() << endl;
        // ptr1离开作用域，资源被释放
    }
    cout << "All shared_ptr out of scope" << endl;
}

// ============ weak_ptr 示例 ============
class TreeNode {
public:
    int value;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    weak_ptr<TreeNode> parent;  // 避免循环引用！
    
    TreeNode(int v) : value(v) {}
};

void weak_ptr_demo() {
    cout << "\n--- weak_ptr (避免循环引用) ---" << endl;
    
    auto parent = make_shared<TreeNode>(1);
    auto child = make_shared<TreeNode>(2);
    
    // 设置关系
    parent->left = child;
    child->parent = parent;  // weak_ptr，不增加引用计数
    
    cout << "parent reference count: " << parent.use_count() << endl;  // 应该是1
    cout << "child reference count: " << child.use_count() << endl;    // 应该是2
    
    // 当需要使用weak_ptr时，用lock()
    if (auto p = child->parent.lock()) {
        cout << "Parent value: " << p->value << endl;
    }
}

// ============ 在函数中使用指针 ============
void process_resource(const shared_ptr<Resource>& res) {
    res->use();
    cout << "Reference count inside function: " << res.use_count() << endl;
}

// ============ 返回智能指针 ============
unique_ptr<Resource> create_resource(const string& name) {
    return make_unique<Resource>(name);
}

shared_ptr<Resource> create_shared_resource(const string& name) {
    return make_shared<Resource>(name);
}

// ============ 指针数组 ============
void pointer_array_demo() {
    cout << "\n--- 智能指针数组 ---" << endl;
    
    vector<shared_ptr<Resource>> resources;
    
    resources.push_back(make_shared<Resource>("R1"));
    resources.push_back(make_shared<Resource>("R2"));
    resources.push_back(make_shared<Resource>("R3"));
    
    cout << "Using all resources:" << endl;
    for (auto& res : resources) {
        res->use();
    }
    
    cout << "Clearing vector..." << endl;
    resources.clear();  // 所有Resource自动被删除
}

// ============ unique_ptr vs shared_ptr ============
/**
 * unique_ptr:
 * - 只有一个所有者
 * - 不能复制，只能move
 * - 更高效（无引用计数开销）
 * - 推荐优先使用
 * - 所有权转移时用move
 * 
 * shared_ptr:
 * - 多个所有者可以共享
 * - 可以复制，自动增加引用计数
 * - 有引用计数开销
 * - 最后一个shared_ptr销毁时释放资源
 * - 注意循环引用问题
 * 
 * weak_ptr:
 * - 观察者角色，不拥有资源
 * - 不影响引用计数
 * - 必须用lock()获取shared_ptr才能使用
 */

// ============ RAII与异常安全 ============
class Database {
private:
    unique_ptr<ifstream> file;
    
public:
    Database(const string& filename) {
        file = make_unique<ifstream>(filename);
        if (!file->is_open()) {
            throw runtime_error("Cannot open file");
        }
    }
    
    ~Database() {
        if (file && file->is_open()) {
            file->close();
        }
        cout << "Database connection closed" << endl;
    }
};

// ============ 与标准库配合 ============
void stl_integration_demo() {
    cout << "\n--- 与STL容器集成 ---" << endl;
    
    map<string, shared_ptr<Resource>> resource_map;
    
    resource_map["res1"] = make_shared<Resource>("Resource 1");
    resource_map["res2"] = make_shared<Resource>("Resource 2");
    
    cout << "Using resources from map:" << endl;
    for (auto& [key, res] : resource_map) {
        cout << key << ": ";
        res->use();
    }
    
    cout << "Map going out of scope..." << endl;
}

int main() {
    cout << "=== 智能指针 ===" << endl;
    
    // ============ unique_ptr演示 ============
    unique_ptr_demo();
    
    // ============ shared_ptr演示 ============
    shared_ptr_demo();
    
    // ============ weak_ptr演示 ============
    weak_ptr_demo();
    
    // ============ 函数使用 ============
    cout << "\n--- 函数传参与返回 ---" << endl;
    auto res = create_resource("FunctionResource");
    process_resource(res);
    res->use();
    
    auto shared_res = create_shared_resource("SharedFunctionResource");
    process_resource(shared_res);
    
    // ============ 指针数组 ============
    pointer_array_demo();
    
    // ============ STL集成 ============
    stl_integration_demo();
    
    // ============ 尝试异常处理 ============
    cout << "\n--- 异常安全性 ---" << endl;
    try {
        Database db("nonexistent.db");  // 会抛异常
    } catch (const exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    
    cout << "\n=== 总结 ===" << endl;
    cout << "智能指针使用原则：" << endl;
    cout << "1. 优先使用 unique_ptr" << endl;
    cout << "2. 必要时使用 shared_ptr" << endl;
    cout << "3. 使用 make_unique/make_shared 创建" << endl;
    cout << "4. 避免循环引用，使用 weak_ptr" << endl;
    cout << "5. 忘记 new/delete，让智能指针管理内存" << endl;
    
    return 0;
}

/**
 * 从raw指针迁移到智能指针的好处：
 * 1. 自动内存管理，无内存泄漏
 * 2. 异常安全
 * 3. 代码更清晰，资源所有权明确
 * 4. 性能与手动管理相当或更好
 * 
 * 现代C++写代码几乎不需要手动new/delete！
 */
