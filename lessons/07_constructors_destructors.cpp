#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * 模块7：构造与析构
 * 对象生命周期管理的关键
 */

// ============ 默认构造 ============
class Simple {
public:
    Simple() {
        cout << "Simple constructor called" << endl;
    }
    
    ~Simple() {
        cout << "Simple destructor called" << endl;
    }
};

// ============ 参数化构造 ============
class Person {
private:
    string name;
    int age;
    
public:
    // 参数化构造
    Person(const string& n, int a) : name(n), age(a) {
        cout << "Person constructor: " << name << ", " << age << endl;
    }
    
    // 默认构造（如果用户定义了任何构造，编译器不会自动生成）
    Person() : name("Unknown"), age(0) {
        cout << "Person default constructor" << endl;
    }
    
    // 拷贝构造
    Person(const Person& other) : name(other.name), age(other.age) {
        cout << "Copy constructor: " << name << endl;
    }
    
    // 移动构造（C++11）
    Person(Person&& other) noexcept : name(move(other.name)), age(other.age) {
        cout << "Move constructor: " << name << endl;
    }
    
    // 析构
    ~Person() {
        cout << "Person destructor: " << name << endl;
    }
    
    // 拷贝赋值
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
            cout << "Copy assignment: " << name << endl;
        }
        return *this;
    }
    
    // 移动赋值
    Person& operator=(Person&& other) noexcept {
        if (this != &other) {
            name = move(other.name);
            age = other.age;
            cout << \"Move assignment: \" << name << endl;
        }
        return *this;
    }
    
    void display() const {
        cout << name << \" (\" << age << \")\" << endl;
    }
};

// ============ 初始化列表 ============
class Point {
private:
    double x, y;
    
public:
    // 初始化列表（推荐）
    Point(double x_val, double y_val) : x(x_val), y(y_val) {
        cout << \"Point created: (\" << x << \", \" << y << \")\" << endl;
    }
    
    void display() const {
        cout << \"(\" << x << \", \" << y << \")\" << endl;
    }
};

// ============ 委托构造（C++11） ============
class Rectangle {
private:
    double width, height;
    
public:
    // 委托给其他构造
    Rectangle() : Rectangle(1.0, 1.0) {}
    
    Rectangle(double w, double h) : width(w), height(h) {
        cout << \"Rectangle: \" << width << \"x\" << height << endl;
    }
    
    double area() const { return width * height; }
};

// ============ 转换构造 ============
class Temperature {
private:
    double celsius;
    
public:
    // 允许从double隐式转换
    Temperature(double c) : celsius(c) {}
    
    // explicit防止隐式转换
    // explicit Temperature(double c) : celsius(c) {}
    
    double getCelsius() const { return celsius; }
};

// ============ 析构函数的重要性 ============
class ResourceHolder {
private:
    int* data;
    int size;
    
public:
    ResourceHolder(int s) : size(s) {
        data = new int[size];
        cout << \"ResourceHolder allocated \" << size << \" integers\" << endl;
    }
    
    ~ResourceHolder() {
        delete[] data;
        cout << \"ResourceHolder deallocated \" << size << \" integers\" << endl;
    }
    
    // 禁用拷贝（只允许移动）
    ResourceHolder(const ResourceHolder&) = delete;
    ResourceHolder& operator=(const ResourceHolder&) = delete;
    
    // 允许移动
    ResourceHolder(ResourceHolder&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
};

// ============ 虚析构函数 ============
class Base {
public:
    virtual ~Base() {
        cout << \"Base destructor\" << endl;
    }
};

class Derived : public Base {
private:
    int* resource;
    
public:
    Derived() {
        resource = new int(42);
        cout << \"Derived constructor\" << endl;
    }
    
    ~Derived() {
        delete resource;
        cout << \"Derived destructor\" << endl;
    }
};

int main() {
    cout << \"=== 构造与析构 ===\" << endl;
    
    // ============ 默认构造 ============
    cout << \"\\n--- 默认构造 ---\" << endl;
    {
        Simple s;
    }  // 析构函数在这里调用
    
    // ============ 参数化构造 ============
    cout << \"\\n--- 参数化构造 ---\" << endl;
    Person p1(\"Alice\", 25);
    p1.display();
    
    // ============ 拷贝构造 ============
    cout << \"\\n--- 拷贝构造 ---\" << endl;
    Person p2 = p1;  // 拷贝构造
    p2.display();
    
    // ============ 移动构造 ============
    cout << \"\\n--- 移动构造 ---\" << endl;
    Person p3 = move(p1);  // 移动构造
    p3.display();
    
    // ============ 拷贝赋值 ============
    cout << \"\\n--- 拷贝赋值 ---\" << endl;
    Person p4(\"Bob\", 30);
    p4 = p2;  // 拷贝赋值
    p4.display();
    
    // ============ 移动赋值 ============
    cout << \"\\n--- 移动赋值 ---\" << endl;
    p4 = move(p3);  // 移动赋值
    
    // ============ 初始化列表 ============
    cout << \"\\n--- 初始化列表 ---\" << endl;
    Point pt(3.0, 4.0);
    pt.display();
    
    // ============ 委托构造 ============
    cout << \"\\n--- 委托构造 ---\" << endl;
    Rectangle r1;        // 委托给Rectangle(1.0, 1.0)
    Rectangle r2(2.0, 3.0);
    cout << \"Area of r2: \" << r2.area() << endl;
    
    // ============ 转换构造 ============
    cout << \"\\n--- 转换构造 ---\" << endl;
    Temperature t1 = 25.5;  // 隐式转换
    Temperature t2(30.0);   // 显式转换
    cout << \"Temperature: \" << t1.getCelsius() << \"C\" << endl;
    
    // ============ 对象容器 ============
    cout << \"\\n--- 对象容器 ---\" << endl;
    {
        vector<Person> people;
        people.emplace_back(\"Charlie\", 35);  // 原地构造，避免移动
        people.emplace_back(\"Diana\", 28);
        
        cout << \"People in vector:\" << endl;
        for (auto& p : people) {
            p.display();
        }
    }  // 所有Person对象在这里析构
    
    // ============ 资源管理 ============
    cout << \"\\n--- 资源管理(RAII) ---\" << endl;
    {
        ResourceHolder holder(100);
        // ... 使用holder ...
    }  // 自动调用析构，释放资源
    
    // ============ 虚析构函数的重要性 ============
    cout << \"\\n--- 虚析构函数 ---\" << endl;
    {
        Base* ptr = new Derived();
        delete ptr;  // 正确：先调用Derived析构，再Base析构
    }
    
    cout << \"\\n=== 构造与析构总结 ===\" << endl;
    cout << \"1. 默认构造：无参数初始化\" << endl;
    cout << \"2. 参数化构造：提供初始值\" << endl;
    cout << \"3. 拷贝构造：深拷贝\" << endl;
    cout << \"4. 移动构造：资源所有权转移\" << endl;
    cout << \"5. 初始化列表：优先于函数体赋值\" << endl;
    cout << \"6. 虚析构：多态删除的关键\" << endl;
    cout << \"7. RAII：资源获取即初始化\" << endl;
    
    return 0;
}

/**\n * Rule of Five (或Rule of Three/Zero)：\n * \n * 如果定义了以下之一，需要定义所有五个：\n * 1. 析构函数\n * 2. 拷贝构造\n * 3. 拷贝赋值\n * 4. 移动构造(C++11)\n * 5. 移动赋值(C++11)\n * \n * 或者都不定义，让编译器生成默认实现\n * \n * 关键概念：\n * - 成员初始化列表在构造函数体之前执行\n * - 析构顺序与构造顺序相反\n * - 虚析构函数确保多态删除正确\n * - 移动操作比拷贝更高效\n */\n"