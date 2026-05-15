#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/**
 * 模块8：继承与多态
 * 面向对象编程的核心
 */

// ============ 基类 ============
class Animal {
protected:  // 子类可访问
    string name;
    
public:
    Animal(const string& n) : name(n) {
        cout << "Animal constructor: " << name << endl;
    }
    
    virtual ~Animal() {
        cout << "Animal destructor: " << name << endl;
    }
    
    virtual void speak() const {
        cout << name << " makes a sound" << endl;
    }
    
    virtual void eat() const = 0;  // 纯虚函数，必须由子类实现
};

// ============ 继承 ============
class Dog : public Animal {
private:
    string breed;
    
public:
    Dog(const string& n, const string& b) 
        : Animal(n), breed(b) {
        cout << "Dog constructor" << endl;
    }
    
    ~Dog() {
        cout << "Dog destructor" << endl;
    }
    
    // 覆盖基类的虚函数
    void speak() const override {
        cout << name << " (Dog) barks: Woof! Woof!" << endl;
    }
    
    void eat() const override {
        cout << name << " eats dog food" << endl;
    }
    
    void fetch() const {
        cout << name << " fetches the ball" << endl;
    }
    
    string getBreed() const {
        return breed;
    }
};

class Cat : public Animal {
private:
    int lives;
    
public:
    Cat(const string& n, int l = 9) 
        : Animal(n), lives(l) {
        cout << "Cat constructor" << endl;
    }
    
    ~Cat() {
        cout << "Cat destructor" << endl;
    }
    
    void speak() const override {
        cout << name << " (Cat) meows: Meow!" << endl;
    }
    
    void eat() const override {
        cout << name << " eats cat food" << endl;
    }
    
    void scratch() const {
        cout << name << " scratches the furniture" << endl;
    }
};

// ============ 多重继承 ============
class Pet {
public:
    virtual void play() const = 0;
};

class GoldenRetriever : public Dog, public Pet {
public:
    GoldenRetriever(const string& n) : Dog(n, "Golden Retriever") {}
    
    void play() const override {
        cout << name << " plays fetch!" << endl;
    }
};

// ============ 访问权限 ============
class Base {
public:
    int pub = 1;
    
protected:
    int prot = 2;
    
private:
    int priv = 3;
};

class PublicDerived : public Base {
    // 继承访问权限：public, protected, private
public:
    void show() {
        cout << "pub: " << pub << endl;      // OK: public
        cout << "prot: " << prot << endl;    // OK: protected
        // cout << "priv: " << priv << endl;  // ERROR: private
    }
};

// ============ 虚函数表 ============
/**
 * 编译器为每个有虚函数的类生成虚函数表(vtable)
 * 每个对象维护一个指向其类的虚函数表的指针
 */

// ============ 运行时类型识别(RTTI) ============
void print_animal_info(const Animal* animal) {
    cout << "Animal info: ";
    animal->speak();
    
    // dynamic_cast尝试向下转换
    if (const Dog* dog = dynamic_cast<const Dog*>(animal)) {
        cout << "This is a dog of breed: " << dog->getBreed() << endl;
        dog->fetch();
    } else if (const Cat* cat = dynamic_cast<const Cat*>(animal)) {
        cout << "This is a cat" << endl;
        cat->scratch();
    }
}

// ============ 虚函数的作用 ============
/**
 * 不用虚函数（静态绑定）：
 * Animal* ptr = new Dog("Rex");
 * ptr->speak();  // 调用Animal::speak()
 * 
 * 使用虚函数（动态绑定）：
 * Animal* ptr = new Dog("Rex");
 * ptr->speak();  // 调用Dog::speak()
 */

int main() {
    cout << "=== 继承与多态 ===" << endl;
    
    // ============ 基本继承 ============
    cout << "\\n--- 基本继承 ---" << endl;
    {
        Dog dog("Rex", "Labrador");
        dog.speak();
        dog.eat();
        dog.fetch();
    }
    
    // ============ 多态性 ============
    cout << "\\n--- 多态性 ---" << endl;
    {
        vector<unique_ptr<Animal>> animals;
        
        animals.push_back(make_unique<Dog>("Rex", "Labrador"));
        animals.push_back(make_unique<Cat>("Whiskers"));
        animals.push_back(make_unique<Dog>("Buddy", "Golden"));
        
        cout << "\\nCalling speak() through base class pointer:" << endl;
        for (auto& animal : animals) {
            animal->speak();  // 调用不同的实现
        }
        
        cout << "\\nCalling eat():" << endl;
        for (auto& animal : animals) {
            animal->eat();    // 调用不同的实现
        }
    }
    
    // ============ RTTI ============
    cout << "\\n--- 运行时类型识别 ---" << endl;
    {
        Dog dog("Buddy", "Poodle");
        Cat cat("Tom");
        
        print_animal_info(&dog);
        cout << endl;
        print_animal_info(&cat);
    }
    
    // ============ 访问权限 ============
    cout << "\\n--- 访问权限 ---" << endl;
    {
        PublicDerived derived;
        derived.show();
    }
    
    // ============ 多重继承 ============
    cout << "\\n--- 多重继承 ---" << endl;
    {
        GoldenRetriever gr("Lucky");
        gr.speak();       // 来自Dog/Animal
        gr.play();        // 来自Pet
        gr.fetch();       // 来自Dog
    }
    
    // ============ 虚函数与类型转换 ============
    cout << "\\n--- 虚函数示例 ---" << endl;
    {
        // 静态类型 vs 动态类型
        Animal* ptr1 = new Dog("Max", "Beagle");      // 静态类型: Animal*, 动态类型: Dog*
        Animal* ptr2 = new Cat("Mittens");            // 静态类型: Animal*, 动态类型: Cat*
        
        // 虚函数根据动态类型调用
        ptr1->speak();  // Dog::speak()
        ptr2->speak();  // Cat::speak()
        
        delete ptr1;
        delete ptr2;
    }
    
    // ============ 抽象类 ============
    cout << "\\n--- 抽象类 ---" << endl;
    cout << "Animal是抽象类（有纯虚函数eat()）" << endl;
    cout << "不能直接创建Animal对象" << endl;
    // Animal a("Bob");  // ERROR: 不能实例化抽象类
    
    // ============ 虚析构函数的重要性 ============
    cout << "\\n--- 虚析构函数的重要性 ---" << endl;
    {
        Animal* animal = new Dog("Destructor Test", "Mixed");
        delete animal;  // 调用Dog析构，然后Animal析构
    }
    
    cout << "\\n=== 继承与多态总结 ===" << endl;
    cout << "1. 虚函数实现运行时多态" << endl;
    cout << "2. override关键字确保正确覆盖" << endl;
    cout << "3. 纯虚函数定义接口（抽象类）" << endl;
    cout << "4. 虚析构函数是必须的（当有虚函数时）" << endl;
    cout << "5. dynamic_cast进行安全的类型转换" << endl;
    cout << "6. 多重继承：使用时要小心歧义" << endl;
    cout << "7. 优先使用组合而不是继承" << endl;
    
    return 0;
}

/**
n * 虚函数 vs 重载：\n * \n * 虚函数（多态）:\n * - 基类定义接口\n * - 子类提供不同实现\n * - 运行时动态选择\n * - 基于对象的实际类型\n * \n * 重载：\n * - 同一作用域内\n * - 参数列表不同\n * - 编译时静态选择\n * - 基于编译期已知的类型\n * \n * 继承体系的设计原则：\n * 1. Liskov替换原则(LSP)：子类可以替代基类\n * 2. 接口隔离原则：不依赖不需要的接口\n * 3. 依赖倒置：依赖抽象而不是具体\n * 4. 避免菱形继承问题（虚继承解决）\n * 5. 组合优于继承\n */\n"