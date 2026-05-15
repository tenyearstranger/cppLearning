#include <iostream>
#include <string>
using namespace std;

/**
 * 模块5：类与对象
 * C++的OOP特性
 */

// ============ 基本类定义 ============
class Person {
private:  // 私有成员
    string name;
    int age;
    
public:   // 公开接口
    // 构造函数
    Person(const string& n, int a) : name(n), age(a) {}
    
    // Getter方法
    string getName() const { return name; }
    int getAge() const { return age; }
    
    // Setter方法
    void setAge(int a) { 
        if (a > 0 && a < 150) age = a; 
    }
    
    // 普通成员函数
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    
    // 重载操作符
    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

// ============ 继承示例 ============
class Employee : public Person {
private:
    double salary;
    
public:
    Employee(const string& n, int a, double s) 
        : Person(n, a), salary(s) {}
    
    double getSalary() const { return salary; }
    
    // 虚函数可被子类重写
    virtual void display() const {
        Person::display();
        cout << "Salary: $" << salary << endl;
    }
};

// ============ 虚函数示例 ============
class Shape {
public:
    virtual ~Shape() {}  // 虚析构函数很重要！
    
    virtual double area() const = 0;  // 纯虚函数
    virtual void draw() const = 0;
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    
    double area() const override {  // C++11: override关键字
        return 3.14159 * radius * radius;
    }
    
    void draw() const override {
        cout << "Drawing circle with radius " << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    void draw() const override {
        cout << "Drawing rectangle " << width << "x" << height << endl;
    }
};

int main() {
    cout << "=== 类与对象 ===" << endl;
    
    // ============ 创建对象 ============
    cout << "\n--- 对象创建 ---" << endl;
    Person p1("Alice", 25);
    p1.display();
    
    Person p2("Bob", 30);
    p2.display();
    
    // ============ 继承 ============
    cout << "\n--- 继承 ---" << endl;
    Employee emp("Charlie", 35, 50000.0);
    emp.display();
    
    // ============ 多态 ============
    cout << "\n--- 多态 ---" << endl;
    Circle circle(5.0);
    Rectangle rect(4.0, 6.0);
    
    Shape* shapes[] = {&circle, &rect};
    
    for (Shape* shape : shapes) {
        shape->draw();
        cout << "Area: " << shape->area() << endl;
    }
    
    // ============ 对象比较 ============
    cout << "\n--- 运算符重载 ---" << endl;
    if (p1 < p2) {
        cout << p1.getName() << " is younger than " << p2.getName() << endl;
    }
    
    // ============ 静态成员 ============
    cout << "\n--- 静态成员 ---" << endl;
    
    class Counter {
    public:
        static int count;
        Counter() { count++; }
    };
    
    int Counter::count = 0;  // 静态成员初始化
    
    {
        Counter c1, c2, c3;
        cout << "Created " << Counter::count << " Counter objects" << endl;
    }
    
    // ============ const对象与this指针 ============
    cout << "\n--- const对象 ---" << endl;
    const Person const_person("Diana", 28);
    cout << const_person.getName() << endl;
    // const_person.setAge(29);  // ERROR: 不能调用非const方法
    
    return 0;
}

/**
 * 重要概念：
 * 1. 访问控制：private, protected, public
 * 2. 构造和析构
 * 3. 继承 vs 组合
 * 4. 虚函数与多态
 * 5. 抽象类与接口（纯虚函数）
 * 6. const正确性
 * 7. 操作符重载
 */
