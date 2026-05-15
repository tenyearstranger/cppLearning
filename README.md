# C++ 语法基础学习指南

## 学习路线

所有学习代码都在 `lessons/` 文件夹中

### 第一阶段：基础语法 (已有基础可快速过)

- [1_基础语法与变量类型](./lessons/01_basics.cpp)
- [2_控制流](./lessons/02_control_flow.cpp)
- [3_函数与作用域](./lessons/03_functions.cpp)

### 第二阶段：C++核心特性（重点）

- [4_指针与引用](./lessons/04_pointers_references.cpp) ⭐
- [5_类与对象](./lessons/05_classes.cpp)
- [6_内存管理与RAII](./lessons/06_memory_management.cpp) ⭐
- [7_构造与析构](./lessons/07_constructors_destructors.cpp)
- [8_继承与多态](./lessons/08_inheritance_polymorphism.cpp)

### 第三阶段：高级特性

- [9_模板与泛型编程](./lessons/09_templates.cpp) ⭐
- [10_标准库容器](./lessons/10_stl_containers.cpp)
- [11_算法与迭代器](./lessons/11_stl_algorithms.cpp)
- [12_异常处理](./lessons/12_exceptions.cpp)

### 第四阶段：现代C++（C++11/14/17/20）

- [14_智能指针](./lessons/14_smart_pointers.cpp) ⭐
- [15_移动语义](./lessons/15_move_semantics.cpp) ⭐
- [16_Lambda表达式](./lessons/16_lambdas.cpp)
- [17_现代C++特性](./lessons/17_modern_cpp.cpp)

### 第五阶段：实战

- [18_完整项目示例](./lessons/18_project_example.cpp)

## 快速参考

| 特性       | 说明             | 关键点           |
| ---------- | ---------------- | ---------------- |
| 指针 `*`   | C风格指针        | 需要手动管理内存 |
| 引用 `&`   | 别名，不能为空   | 不涉及指针算术   |
| new/delete | 动态内存分配     | 容易内存泄漏     |
| 智能指针   | 自动内存管理     | 现代C++推荐      |
| 模板       | 泛型编程         | 编译期生成代码   |
| RAII       | 资源获取即初始化 | C++独特原则      |

## 学习建议

1. **跳过重复内容**：你已有C基础，可快速过`基础语法`部分
2. **深入学习重点**：标⭐的章节是C++与其他语言的主要差异
3. **动手实践**：每个文件都包含可运行的示例，编译并运行
4. **对比学习**：思考同样的功能在C/Java/Python中如何实现

## 编译与运行

### 使用编译脚本（推荐）

```bash
# Windows
.\build.bat compile lessons/04_pointers_references.cpp
.\build.bat run 04_pointers_references

# Linux/Mac
bash build.sh compile lessons/04_pointers_references.cpp
bash build.sh run 04_pointers_references
```

### 手动编译

```bash
# 进入lessons文件夹
cd lessons

# 编译单个文件
g++ -std=c++17 -o output_name filename.cpp

# 运行
./output_name

## 相关资源

- C++ Reference: https://en.cppreference.com/
- Effective C++系列书籍
- C++ Primer（第5版）
