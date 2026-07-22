# C++ 基础语法笔记

这份笔记面向 C++ 初学者，记录目前学到的基础语法。代码尽量只使用语言本身和常见的 `iostream`。

## 1. `const`：只读值

```cpp
const int MaxSize = 100;
// MaxSize = 200; // 错误，const 变量不能被修改
```

`const` 表示对象创建后不能再被修改。它可以是运行时才获得的值：

```cpp
int ReadSize();
const int size = ReadSize();
```

## 2. `constexpr`：编译期常量

```cpp
constexpr int MaxSize = 100;
int data[MaxSize];
```

`constexpr` 也不能被修改，但值必须在编译期间就能确定，所以适合用作数组大小。

| 特性 | `const` | `constexpr` |
| --- | --- | --- |
| 创建后不能修改 | 是 | 是 |
| 必须是编译期值 | 不一定 | 是 |
| 可作固定数组长度 | 不一定 | 可以 |

## 3. `using`：类型别名

```cpp
using ElementType = int;
ElementType value = 10; // 等价于 int value = 10
```

`ElementType` 只是 `int` 的另一个名，不是一个新的独立类型。如果以后想使用 `double`，只需改为：

```cpp
using ElementType = double;
```

`using ElementType = int;` 和 `typedef int ElementType;` 作用基本相同，现代 C++ 通常推荐 `using`。

## 4. 指针和 `nullptr`

普通变量保存数据，指针保存地址：

```cpp
int number = 10;
int* pointer = &number;

*pointer = 20; // 通过指针修改 number
```

- `&number` 是取地址。
- `*pointer` 是取指针指向的数据。
- `nullptr` 表示指针没有指向任何对象。

```cpp
int* pointer = nullptr;

if (pointer != nullptr) {
    std::cout << *pointer;
}
```

不能对 `nullptr` 解引用，否则可能导致程序崩溃。

## 5. 引用

引用是另一个变量的别名：

```cpp
int number = 10;
int& reference = number;

reference = 20; // number 也变成 20
```

引用必须在定义时绑定到一个对象，不能像指针一样指向 `nullptr`。

函数可以通过引用参数返回额外结果：

```cpp
bool Pop(int& value) {
    value = 66;
    return true;
}
```

## 6. 函数重载

函数重载是指：函数名相同，但参数数量或类型不同。

```cpp
void Print(int value);
void Print(double value);
void Print(int a, int b);

Print(10);       // 调用 Print(int)
Print(3.14);     // 调用 Print(double)
Print(10, 20);   // 调用 Print(int, int)
```

只有返回值不同不能构成重载：

```cpp
int GetValue();
// double GetValue(); // 错误，只有返回值不同
```

链表中的两个 `GetNode` 就是重载：

```cpp
Node* GetNode(int index);
const Node* GetNode(int index) const;
```

## 7. 成员函数后的 `const`

```cpp
int Length() const {
    return length_;
}
```

函数参数后的 `const` 表示这个函数不会修改当前对象。只读函数应当加上它：

```cpp
const ArrayList list;
list.Length(); // 可以调用
```

`const Node*` 中的 `const` 是另一件事：它表示不能通过这个指针修改节点。

```cpp
const Node* current = nullptr;
// current->data = 10; // 错误，只读节点
```

## 8. `new` 和 `delete`

`new` 在运行时申请内存，`delete` 释放这块内存：

```cpp
int* pointer = new int(10);

delete pointer;
pointer = nullptr;
```

创建链表节点：

```cpp
struct Node {
    int data;
    Node* next;
};

Node* node = new Node{10, nullptr};
delete node;
```

使用 `new` 后忘记 `delete` 会导致内存泄漏；`delete` 之后继续访问指针会导致未定义行为。

## 9. 学习时的总结

| 语法 | 关键含义 |
| --- | --- |
| `const` | 只读，不允许修改 |
| `constexpr` | 编译期就能确定的只读值 |
| `using` | 给类型起别名 |
| `*` | 指针声明或解引用 |
| `&` | 取地址或声明引用 |
| `nullptr` | 空指针 |
| `new` | 动态申请内存 |
| `delete` | 释放动态申请的内存 |
| 函数重载 | 同名函数根据参数区分 |
