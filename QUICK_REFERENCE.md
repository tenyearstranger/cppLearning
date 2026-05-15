# C++ 快速参考指南

## 编译与运行

### Windows (PowerShell/CMD)
```bash
# 单个文件
g++ -std=c++17 -o program 01_basics.cpp
./program.exe

# 或使用脚本
build.bat compile 01_basics.cpp
build.bat run 01_basics
```

### Linux/Mac
```bash
# 单个文件
g++ -std=c++17 -o program 01_basics.cpp
./program

# 或使用脚本
bash build.sh compile 01_basics.cpp
bash build.sh run 01_basics
```

## 快速查找表

### 数据类型
| 类型     | 说明       | 范围           |
| -------- | ---------- | -------------- |
| `char`   | 字符       | -128 ~ 127     |
| `short`  | 短整数     | -32768 ~ 32767 |
| `int`    | 整数       | -2^31 ~ 2^31-1 |
| `long`   | 长整数     | 取决于平台     |
| `float`  | 单精度浮点 | ~7位有效数字   |
| `double` | 双精度浮点 | ~15位有效数字  |
| `bool`   | 布尔       | true/false     |
| `string` | 字符串     | 动态长度       |

### 指针与引用对比
| 特性         | 指针     | 引用     |
| ------------ | -------- | -------- |
| 可以为null   | ✓        | ✗        |
| 可以改变指向 | ✓        | ✗        |
| 需要解引用   | ✓        | ✗        |
| 指针算术     | ✓        | ✗        |
| sizeof       | 指针大小 | 对象大小 |

### 智能指针选择
| 场景       | 推荐         |
| ---------- | ------------ |
| 单个所有者 | `unique_ptr` |
| 多个所有者 | `shared_ptr` |
| 观察者角色 | `weak_ptr`   |
| RAII资源   | `unique_ptr` |

### STL容器对比
| 容器          | 随机访问 | 头部插删 | 尾部插删 | 中间插删 | 查找    |
| ------------- | -------- | -------- | -------- | -------- | ------- |
| vector        | O(1)     | O(n)     | O(1)     | O(n)     | O(n)    |
| list          | O(n)     | O(1)     | O(1)     | O(1)     | O(n)    |
| deque         | O(1)     | O(1)     | O(1)     | O(n)     | O(n)    |
| set           | -        | -        | -        | O(logn)  | O(logn) |
| unordered_set | -        | -        | -        | O(1)avg  | O(1)avg |
| map           | -        | -        | -        | O(logn)  | O(logn) |

### 常用STL算法
```cpp
find(begin, end, value)              // 查找值
find_if(begin, end, predicate)       // 条件查找
count(begin, end, value)             // 计数
sort(begin, end)                     // 排序
sort(begin, end, greater<T>())       // 反向排序
transform(begin, end, dest, func)    // 变换
copy(begin, end, dest)               // 复制
remove(begin, end, value)            // 移除（逻辑）
unique(begin, end)                   // 去重
any_of/all_of/none_of()             // 条件检查
for_each(begin, end, func)           // 遍历
```

## C++版本对比

### C++11 (关键)
- `auto` 类型推导
- 范围for循环
- Lambda表达式
- 右值引用与移动语义
- 智能指针
- 列表初始化
- `nullptr`
- `constexpr`
- 可变参数模板

### C++17 (推荐)
- `std::optional`
- `std::variant`
- 结构化绑定
- `if constexpr`
- 折叠表达式
- `std::string_view`
- 并行算法

### C++20 (未来)
- Concepts (概念)
- Coroutines (协程)
- Ranges (范围库)
- Modules (模块系统)

## 常见错误与解决

### 内存问题
```cpp
// ✗ 内存泄漏
int* p = new int(10);
delete p;  // 容易忘记

// ✓ 使用智能指针
auto p = make_unique<int>(10);  // 自动清理
```

### 拷贝/移动
```cpp
// ✗ 不必要的拷贝
vector<int> v1 = {1, 2, 3};
vector<int> v2 = v1;  // 深拷贝

// ✓ 使用移动
vector<int> v2 = move(v1);  // 移动，高效
```

### 异常安全
```cpp
// ✗ 资源泄漏
void process() {
    FILE* f = fopen("file.txt", "r");
    if (error) return;  // 文件未关闭
    fclose(f);
}

// ✓ RAII保证清理
void process() {
    FileHandler file("file.txt");  // 构造打开
    // ...
}  // 析构自动关闭
```

## 常用编译选项

```bash
g++ -std=c++17           # 指定C++标准
    -Wall -Wextra       # 显示警告
    -O2                 # 优化级别2
    -g                  # 调试信息
    -DDEBUG             # 定义宏
    -I/path/to/include  # 包含路径
    -L/path/to/lib      # 库路径
    -lname              # 链接库
    -o output file.cpp  # 输出文件名
```

## 最佳实践总结

1. **优先使用现代C++特性** - auto, nullptr, lambda等
2. **内存管理** - 用智能指针替代new/delete
3. **容器选择** - 根据操作特性选择合适容器
4. **算法应用** - 学会使用STL算法
5. **const正确性** - 合理使用const
6. **异常处理** - 用异常处理错误，RAII保证安全
7. **泛型编程** - 适当使用模板提高代码复用
8. **性能考虑** - 移动语义、引用参数等
9. **代码风格** - 一致的命名和格式
10. **单元测试** - 验证代码正确性

## 推荐学习资源

- Cppreference: https://en.cppreference.com/
- Effective C++ 系列书籍
- C++ Primer (第5版)
- Modern C++ (Herb Sutter)
- 《C++ Concurrency in Action》（并发编程）

## 进阶主题

- 并发编程 (threads, mutex, async)
- 模板元编程 (TMP)
- 设计模式
- 网络编程
- 游戏开发
- 系统编程
