#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

/**
 * 模块10：标准库容器
 * STL容器概览与使用
 */

int main() {
    cout << "=== STL容器 ===" << endl;
    
    // ============ vector - 动态数组 ============
    cout << "\n--- vector(动态数组) ---" << endl;
    vector<int> v = {1, 2, 3};
    
    v.push_back(4);        // 在末尾添加
    v.insert(v.begin(), 0); // 在开头插入
    
    cout << "Vector size: " << v.size() << ", capacity: " << v.capacity() << endl;
    for (int x : v) cout << x << " ";
    cout << endl;
    
    // ============ list - 链表 ============
    cout << "\n--- list(双向链表) ---" << endl;
    list<int> l = {1, 2, 3, 4, 5};
    
    l.push_front(0);  // 在前面添加
    l.push_back(6);   // 在后面添加
    
    cout << "List: ";
    for (int x : l) cout << x << " ";
    cout << endl;
    
    // ============ deque - 双端队列 ============
    cout << "\n--- deque(双端队列) ---" << endl;
    deque<int> d = {1, 2, 3};
    
    d.push_front(0);
    d.push_back(4);
    
    cout << "Deque: ";
    for (int x : d) cout << x << " ";
    cout << endl;
    
    // ============ set - 有序集合（无重复） ============
    cout << "\n--- set(有序集合) ---" << endl;
    set<int> s = {3, 1, 4, 1, 5, 9, 2, 6};  // 自动排序，去重
    
    cout << "Set: ";
    for (int x : s) cout << x << " ";
    cout << endl;
    
    s.insert(7);
    cout << "After insert(7): ";
    for (int x : s) cout << x << " ";
    cout << endl;
    
    // ============ map - 键值对映射 ============
    cout << "\n--- map(有序键值对) ---" << endl;
    map<string, int> age_map;
    
    age_map["Alice"] = 25;
    age_map["Bob"] = 30;
    age_map["Charlie"] = 35;
    
    cout << "Alice's age: " << age_map["Alice"] << endl;
    cout << "Map contents: " << endl;
    for (auto& [name, age] : age_map) {
        cout << "  " << name << ": " << age << endl;
    }
    
    // ============ unordered_set - 无序集合 ============
    cout << "\n--- unordered_set(哈希集合) ---" << endl;
    unordered_set<string> tags = {"C++", "programming", "STL"};
    
    cout << "Tags: ";
    for (const auto& tag : tags) cout << tag << " ";
    cout << endl;
    
    // ============ unordered_map - 无序映射 ============
    cout << "\n--- unordered_map(哈希映射) ---" << endl;
    unordered_map<string, double> scores;
    
    scores["Alice"] = 95.5;
    scores["Bob"] = 87.3;
    scores["Charlie"] = 92.1;
    
    cout << "Scores:" << endl;
    for (auto& [name, score] : scores) {
        cout << "  " << name << ": " << score << endl;
    }
    
    // ============ stack - 栈 ============
    cout << "\n--- stack(LIFO栈) ---" << endl;
    stack<int> stk;
    
    stk.push(1);
    stk.push(2);
    stk.push(3);
    
    cout << "Stack (pop): ";
    while (!stk.empty()) {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;
    
    // ============ queue - 队列 ============
    cout << "\n--- queue(FIFO队列) ---" << endl;
    queue<int> q;
    
    q.push(1);
    q.push(2);
    q.push(3);
    
    cout << "Queue (dequeue): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    
    // ============ priority_queue - 优先队列 ============
    cout << "\n--- priority_queue(优先队列) ---" << endl;
    priority_queue<int> pq;  // 默认最大堆
    
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(1);
    pq.push(5);
    
    cout << "Priority queue (descending): ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    
    // ============ 容器选择指南 ============
    cout << "\n--- 容器选择指南 ---" << endl;
    cout << "vector: 随机访问、动态数组" << endl;
    cout << "list: 频繁插删（中间）" << endl;
    cout << "deque: 双端操作" << endl;
    cout << "set: 有序、无重复、查找快" << endl;
    cout << "map: 键值对映射、有序" << endl;
    cout << "unordered_set: 无序查找、平均O(1)" << endl;
    cout << "unordered_map: 无序键值对、平均O(1)" << endl;
    cout << "stack: 后进先出" << endl;
    cout << "queue: 先进先出" << endl;
    
    // ============ 容器适配器 ============
    cout << "\n--- 容器适配器 ---" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    
    // 基于vector的stack
    stack<int, vector<int>> vec_stack(vec);
    cout << "Vector-based stack top: " << vec_stack.top() << endl;
    
    // ============ 常用操作对比 ============
    cout << "\n--- 常用操作复杂度对比 ---" << endl;
    cout << "Vector: push_back O(1), 随机访问O(1), insert O(n)" << endl;
    cout << "List: push_back O(1), 随机访问O(n), insert O(1)" << endl;
    cout << "Set: insert O(logn), find O(logn), 有序" << endl;
    cout << "Unordered_set: insert O(1)avg, find O(1)avg, 无序" << endl;
    
    return 0;
}

/**
 * STL容器选择决策树：
 * 
 * 需要随机访问？
 * ├─ 是 → vector
 * └─ 否
 *     需要频繁插删？
 *     ├─ 是 → list 或 deque
 *     └─ 否
 *         需要不重复元素？
 *         ├─ 是
 *         │   需要有序？
 *         │   ├─ 是 → set
 *         │   └─ 否 → unordered_set
 *         └─ 否
 *             需要键值对？
 *             ├─ 是
 *             │   需要有序？
 *             │   ├─ 是 → map
 *             │   └─ 否 → unordered_map
 *             └─ 否
 *                 需要特殊访问模式？
 *                 ├─ 栈 → stack
 *                 ├─ 队列 → queue
 *                 └─ 优先队列 → priority_queue
 */
