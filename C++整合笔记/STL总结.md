# STL总结

## 字符串

背景：C风格的字符串，一空字符结尾的字符数组，操作复杂，且不安全，于是有了string。底层封装c字符数组：

**c字符数组和string对比**

+ string是一个类，char*是一个指针
+ string提供了很多对字符串操作的方法
+ string不用担心内存释放和越界问题

**常用api**

+ **大小** int str.size()  int str.length()  返回字符串的长度  

+ **清空** str.clear()  清空字符串  

+ **添加** str+='a'  追加字符串  

+ **查找** 

  + int str.find(string ele), 查找元素
  + int str.find(string ele,int pos)  从指定位置开始查找元素，存在返回位置，不存在返回str.npos（-1）;  

+ **删除** string erase(int pos,int len)  从pos 开始删除len个元素

+ **插入**  str.insert(int pos,string ele)  在下标2上插入字符串

+ **比较** str.compare(string ele) 按 照字典序比较  *>时返回 1，<时返回 -1，==时返回 0*

+ **子串** string substr(int pos,int n)  从pos开始的n个字符的字符串

+ **转换**
+ string转c_string   `const char* cstr=str.c_str()`
  + int 转string(全局函数) `string int_str=to_string(val)`
  + string 转int(全局函数) `int i=stoi(str)`



## 向量

### 底层实现

背景：array是静态空间，配置后无法改变，需要一个能动态改变内存空间的数据结构。

定义：动态数组，采用连续线性空间存储。单向开口连续内存空间。序列式容器。

+ 初始化：动态数组为了降低空间配置成本，实际配置一个容量大于实际大小的空间。

+ 容量扩充，当vector的容量不够用时，动态增加容量大小。

  > + 重新配置空间：重新找到一块足够大内存。
  > + 移动数据：拷贝新空间
  > + 释放源空间：释放源空间。
  >
  > 注意：容量扩充后，原有迭代器全部失效。

![vector容器](D:\all_document\document\document\note\c++\CPP_train_code\C++整合笔记\graph\vector容器.png)

### **常用函数**

+ 构造 
  + 构造函数构造：vector(n,elem)
  + 构造函数构造：vector(n),初始化n个0元素
  + 拷贝构造函数构造：vector(const vector<type> &vec)
+ 大小操作
  + vec.size()  返回向量大小  
  + vec.empty()  判断是否为空  
+ 存取操作：
  + operate[] 中括号返回数据
  + front() 返回第一个数据元素
  + back() 返回最后一个数据元素
+ 插入删除：只可以用迭代器，不可以用下标
  + 中间插入：
    + 多个相同元素insert(const_iterator pos, int count,ele);*//迭代器指向位置pos插入count个元素ele.*
    + 单个元素：vec.insert(iter,ele)，在指定位置插入元素
  + **尾插**  vec.push_back(ele)  向量尾部插入   
  + **尾删** vec.pop_back()  向量尾部删除（无返回值） 
  + 中间删除：
    + vec.erase(iter start,iter end) 删除[start,end) 之间元素
    + vec.erase(iter pos) 删除指定位置元素

+ **迭代器** vec.begin() vec.end()  返回向量开头和结尾迭代器  
+ **查找元素(algorithm函数)**  find(vec.begin(),vec.end(),1)  在数组中查找1，存在返回迭代器，不存在返回vec.end();
+ **排序**：sort(vec,begin(),vec.end()) 对vec元素进行排序



## deque

### 底层原理

**背景**：vector是单向开口连续线性空间，首部插入删除效率差，需要一个双向开口的连续线性空间

**vector和的区别**

+ 组织形式：vector是单向开口，deque是双向开口
+ 头部操作：deque允许使用**常数项时间**对头端进行元素的插入和删除操作O(1)
+ 容量：deque没有容量的概念，因为它是动态的以分段连续空间组合而成，随时可以增加一段新的空间并链接起来
+ 迭代器：deque容器也提供了Random Access Iterator,但是**它的迭代器并不是普通的指针**，其复杂度和vector不是一个量级（遍历复杂）****
+ **删除：删除释放内存**

总结：尽量使用vector。

![deque](D:\all_document\document\document\note\c++\CPP_train_code\C++整合笔记\graph\deque.png)

**定义**：双端队列，在逻辑上式连续的双向开口的线性空间。

**实现**：

的确是分段连续内存空间，其中包含控制一个中控器（map）和一个缓冲区。

+ 中控器是一段连续的空间，(注意，不是STL的map容器)作为主控，这里所谓的map是一小块连续的内存空间，每一个节点是一个指针，指向另一段连续内存空间
+ 缓冲区，缓冲区，存储空间主体。

![deque底层](D:\all_document\document\document\note\c++\CPP_train_code\C++整合笔记\graph\deque底层.png)

![deque迭代器](D:\all_document\document\document\note\c++\CPP_train_code\C++整合笔记\graph\deque迭代器.png)

**迭代器失效**

+ deque虽然也提供随机访问的迭代器，但是其迭代器并不是普通的指针
  + cur;//迭代器所指缓冲区当前的元素
  + T* first;//迭代器所指缓冲区第一个元素
  + T* last;//迭代器所指缓冲区最后一个元素
  + map_pointer node;//指向map中的node

+ 插入元素
  + 头尾，可能使指向其他元素的迭代器失效（buffer中一段连续空间满，需重新分配内存和map时）
  + 其他位置，迭代器失效
+ 删除元素
  + 头尾，指向其他元素的迭代器、指针、引用仍然有效
  + 迭代器、指针、引用失效

### 常用api

+ 构造：

  + deque(n,elem) 普通构造
  + deque(const deque &deq) 拷贝构造

+ 赋值：

  + assign(n,elem)将n个elem的值赋值给本身
  + at(idx) *//返回索引idx所指的数据，如果idx越界，抛出out_of_range。*
  + operator[idx]  *返回索引idx所指的数据，如果idx越界，不抛出异常，直接出错。*
  + front()
  + back()

+ 大小：

  + int deque.size()  返回大小
  + bool deque.empty() 返回是否为空

+ 插入和删除

  + 插入

    > 头尾插入：
    >
    > + push_back(elem)
    > + push_front(elem)
    >
    > 中间插入：
    >
    > + insert(iter pos,elem)  pos插入一个元素
    > + insert(iter pos,n,elem) pos 插入n个元素
    > + insert(iter pos,itet begin,iter end) 在iter中插入[begin,end)之间的元素

  + 删除

    >头尾删除
    >
    >+ pop_back()
    >+ pop_front()
    >
    >中间删除
    >
    >+ erase(iter begin,iter end)删除[beg,end)之间的元素
    >+ erase(iter pos) 删除pos位置的数据，返回下一个数据的位置

## 栈

### 底层实现

**定义：**stack是一种**先进后出**(First In Last Out,FILO)的数据结构，它只有一个出口，

+ stack容器允许**新增元素，移除元素，取得栈顶元素**，但是除了最顶端外，没有任何其他方法可以存取stack的其他元素。换言之，stack**不允许有遍历行为**。
+ stack**不提供迭代器**。因为stack不允许遍历

**容器适配器**：修改某种接口，形成另一种风貌”的行为，成为adapter(配接器）

底层：stack这种单向开口的数据结构很容易由**双向开口的deque和list**形成

### 常用api

+ **入栈操作**：st.push(10)  入栈  
+ **出栈操作**：st.pop()  出栈，无返回值 
+ 取出栈顶元素：  int s_top=st.top()  取出栈顶元素  
+ **判空**：st.empty()  判断栈是否为空  
+ **求栈的大小**：st.size()  求栈的大小

## 队列

### 底层实现

定义：Queue是一种**先进先出**(First In First Out,FIFO)的数据结构，它有两个出口，queue容器允许从一端新增元素，从另一端移除元素。

+ 只有尾插和头删的功能，智能获取头部和尾部元素，因此不提供遍历，也就不提供迭代器。

容器适配器：修改某种接口，形成另一种风貌”的行为，成为adapter(配接器）

底层结构：queue这种“先进先出”的数据结构很容易由双向开口的deque和list形成

### 常用api

+ 队尾入队列：void que.push(ele)
+ 队头出队列：void que.pop()
+ **返回队头**：que.front()
+ **返回队尾**：que.back()

## heap堆

定义：堆不是STL的容器组件，是priority queue（优先队列）的底层实现机制

本质：完全二叉树，使用array实现，分为大根堆和小根堆。

常用函数：

+ push_heap:堆插入。将新元素插入到数组尾端，之后是一个称为percolate up（上溯）的过程。
  + 插入节点，一直和父节点比较，比父节点大则交换，否则结束
+ pop_heap ：堆删除，将根节点替换到尾端，然后为新的根节点进行一个（下溯）过程
  + 个被挤掉的元素首先会与根结点的两个子节点比较，并与较大的子节点更换位置，如此一直往下，直到这个被挤掉的元素大于左右两个子节点，或者下放到叶节点为止
+ sort排序：heap中的最大值置于底层容器vector的末尾，heap范围减1，那么不断的执行pop_heap直到树为空，即可得到一个递增序列。

## STL中的priority_queue的实现

定义：优先队列，给队列元素赋予优先级，队列中元素根据优先级排序。

底层实现（容器适配器）：默认情况下，**priority_queue使用一个max-heap**完成，底层容器使用的是一般为**vector**为底层容器，

![优先队列](D:\all_document\document\document\note\c++\CPP_train_code\C++整合笔记\graph\优先队列.png)



## list容器

### slist底层实现

slist：单向链表，存储

插入删除：由于单向特性，只支持头结点的插入和删除，其他位置的插入删除效率低

迭代器：单向迭代器，只支持前移操作

### list底层实现

定义：带头结点的双向循环链表：物理存储单元上非连续、非顺序的存储结构，数据元素的逻辑顺序是通过指针实现。

list特点：

+ 内存：采用动态内存分配，不会发生内存的浪费和溢出
+ 插入删除：插入删除灵活，不需要大量移动元素，时间复杂度低
+ 空间复杂度大。随机存取不方便

迭代器特点：

+ 迭代器类别：**双向迭代器（Bidirectional Iterators.）**，不是类似vector普通指针（遍历连续地址空间），需要有能力对结点进行遍历。需要有前移、后移（++，--）能力。
+ 该迭代器没有随机读取的功能（不能直接迭代器加减元素），不能+1，+2......
+ 迭代器失效：插入删除不会造成原有的list迭代器失效，仅仅会使得**删除元素的的迭代器失效**，其他迭代器不受到影响。

**list和vector是常用的容器**

### 常用API

+ 构造函数

  + list(n,elem);使用n个ele初始化
  + list(n);初始n个节点，节点默认为0；
  + list<T> lst; 默认构造

+ list元素的插入删除操作

  + 插入

    > 首尾插入
    >
    > push_back() 容器尾部插入
    >
    > push_front() 容器首部插入
    >
    > 中间插入
    >
    > insert(iter pos,n,elem)中间插入多个元素
    >
    > insert(iter pos,elem) 中间插入一个元素

  + 删除

    > 首尾删除
    >
    > pop_front() 删除开头元素
    >
    > pop_back() 删除结尾元素
    >
    > 中间删除
    >
    > erase(iter begin,iter end) 删除区间[begin,end)元素
    >
    > erase(iter pos) 删除pos元素。

+ 修改元素

  + 使用迭代器修改。

+ 查找

  + 

+ 大小

  + size() 返回大小
  + empty() 判断是否为空

+ 数据存取

  + front() 返回第一个元素
  + back() 返回最后一个元素

+ 反转和排序

  + reverse() 反转链表
  + lst.sort() 链表排序

## set/multiset

### 底层实现

**set定义（关联式容器）**：集合，存储一组键值（键就是值），键值不能重复

**multiset定义（关联式容器）**:集合，存储一组键值，键值可以重复

**特点：**

+ **自动排序**：set和multiset的值会根据其键值自动排序（默认从小到达）
+ **迭代器**
  + set的迭代器是**常量迭代器**，不能根据迭代器修改set元素值
  + 迭代器失效问题：list迭代器和set迭代器一样，插入删除均不会让原有的迭代器失效，仅仅删除的那个迭代器会失效。
+ **底层实现**：**红黑树**
+ **仿函数自定义排序**。
  + 仿函数：使一个**类的使用看上去像一个函数**。其实现就是类中实现一个[operator](https://baike.baidu.com/item/operator/2387244)()，这个类就有了类似函数的行为，就是一个仿函数类了。
  + 作用：丰富函数的功能。

### 常用api

+ 构造函数
  + set<T> st; 默认构造函数
  + set<T> st{e1,e2,e3} 赋值初始化
  + set& operatot=(const set<T> &st) 重载等号运算符
+ 大小操作
  + size() 返回元素个数
  + empty() 判断是否为空
+ 插入操作
  + insert(elem) 插入元素  返回pair<set<int>::iterator,bool>，其中bool判断是否插入成功
+ 删除操作
  + iter erase(iter pos)  删除pos迭代器指向的元素 ，返回删除的下一个迭代器位置
  + erase(iter begin,iter end) 删除[begin,end)之间的元素，返回下一个元素的迭代器
  + int erase(keyelem) 删除容器中值为elem的元素 ，返回删除的个数
+ 查找操作
  + set.find(key) *//查找键key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();*
  + count(key) *//查找键key的元素个数*

## pair(对组)

定义：pair将一个键和一个值，合并这对值可以表示不同的数据类型。

+ 初始化
  + pair<string,int> pair1("name",20) 构造函数初始化
  + pair<string,int> pair2=make_pair("name",30)  makepair初始化

## map

### map/multimap

#### 底层实现

map：映射，存放pair，所有元素会根据key排序，不允许有重复键值。

multimap：多值映射，允许有重复的键值。

迭代器：

+ **迭代器失效：**插入删除操作均不会让迭代器失效，只有删除的那个元素才会使得迭代器失效
+ **修改元素：**不允许通过迭代器修改键值，但是可以修改实值，因为map的键值关系到map元素的排列规则，任意改变map键值将会严重破坏map组织。如果想要修改元素的实值，那么是可以的。
+ 随机存取：map的迭代器不支持随机加减，仅仅支持前移和后移。

![map实现](D:\all_document\document\document\note\c++\CPP_train_code\C++整合笔记\graph\map实现.png)

#### 常用api

+ 构造：
  + map<T1,T2> mp; 默认构造函数
  + map(const map& mp) ：拷贝构造函数
  + map<T1,T2> mp={"a","b","c"}赋值初始化

+ 大小操作
  + size() 返回数量
  + empty() 判断是否为空
+ 插入（4种插入）
  + pair插入pair insert(pair)。其中pair可以默认构造，也可以make_pair构造
  + map插入map insert(map)
  + 数组插入 mp[T1]=T2;
+ 删除
  + erase(iter pos) 删除pos迭代器的元素 返回下一个迭代器
  + erase(iter begin,iter end) 删除[begin,end)之间元素
  + erase(keyelem) 删除键，返回删除的个数
+ 查找
  + find(key)  *查找键key是否存在,若存在，返回该键的元素的迭代器；/若不存在，返回map.end();*
  + count(key) *返回容器中key为keyElem的对组个数。对map来说，要么是0，要么是1。对multimap来说，值可能大于1。*

+ 存取
  + operator[] 运算符，可以直接进行添加和修改。

### 哈希表 unordered_map

#### 底层实现

定义：哈希表是一个数据结构，用于快速查询元素位置，其中使用哈希函数对键值进行处理，找到值的存储位置。

实现方法：开链法

+ buckets vector（桶向量） ,哈希表内置28个质数，根据存入元素的个数，选择大于元素个数作为vector的容量
  + 使用vector是由于其自动扩容的能力。不需要人工干预
+ link_list.哈希表自定义链表，存储实际的数据，link_list的长度也等于容量
+ 一旦超过容量，哈希表需要重新挑选质数，分配vector的空间

#### 解决哈希冲突的方法

+ 开链法：每个表格维护一个list，如果hash函数计算出的格子相同，则按顺序存在这个list中
+ 线性探测法：使用hash函数计算出的位置如果已经有元素占用了，则向后依次寻找，找到表尾则回到表头，直到找到一个空位
+ 再散列：发生冲突时使用另一种hash函数再计算一个地址，直到不冲突
+ 二次探测：使用hash函数计算出的位置如果已经有元素占用了，按照$1^2$、$2^2$、$3^2$...的步长依次寻找，如果步长是随机数序列，则称之为伪随机探测

### map和hash_map区别，应用场景

map：底层红黑树，自动排序，查询和维护时间复杂度为O(logn)

unorder_map:底层哈希表，不排序，查询时间复杂度O(1)，维护时间复杂度和list长度有关

应用场景：map适用于有序数据的应用场景，unordered_map适用于高效查询的应用场景

## 红黑树

面试时候现场写红黑树代码的概率几乎为0，但是红黑树一些基本概念还是需要掌握的。

1、它是二叉排序树（继承二叉排序树特显）：

- 若左子树不空，则左子树上所有结点的值均小于或等于它的根结点的值。 

- 若右子树不空，则右子树上所有结点的值均大于或等于它的根结点的值。 


- 左、右子树也分别为二叉排序树。 

2、它满足如下几点要求： 

- 树中所有节点非红即黑。 

- 根节点必为黑节点。 


-  红节点的子节点必为黑（黑节点子节点可为黑）。 


- 从根到NULL的任何路径上黑结点数相同。 

3、查找时间一定可以控制在O(logn)。 

## STL容器的使用时机

| .            | vector   | deque    | list         | set    | multiset | map             | multimap      |
| ------------ | -------- | -------- | ------------ | ------ | -------- | --------------- | ------------- |
| 典型内存结构 | 单端数组 | 双端数组 | 双向循环链表 | 二叉树 | 二叉树   | 二叉树          | 二叉树        |
| 可随机存取   | 是       | 是       | 否           | 否     | 否       | 对key而言：不是 | 否            |
| 元素搜寻速度 | 慢       | 慢       | 非常慢       | 快     | 快       | 对key而言：快   | 对key而言：快 |
| 元素安插移除 | 尾端     | 头尾两端 | 任何位置     | -      | -        | -               | -             |

+ vector场景：快速查询，几乎不删改
  + 软件历史操作记录的存储，我们经常要查看历史记录，比如上一次的记录，上上次的记录，但却不会去删除记录，因为记录是事实的描述。
+ deque场景：需要首部删除，插入
  + 比如排队购票系统，对排队者的存储可以采用deque，支持头端的快速移除，尾端的快速添加。如果采用vector，则头端移除时，会移动大量的数据，速度慢
+ list使用场景：频繁不确定位置的插入和删除
  + 公交车乘客的存储
+ set场景：需要排序，实时插入和删除
  + 个人游戏积分排名
+ map场景：快速查询
  + 比如按ID号存储十万个用户，想要快速要通过ID查找对应的用户

vector和deque的比较

+ vector.at()比deque.at()效率高，比如vector.at(0)是固定的，deque的开始位置 却是不固定的。
+ deque支持头部的快速插入与快速移除，这是deque的优点。

## 常用算法

### 仿函数

+ 背景：使用函数指针调用，扩展性太差，将函数封装成一个类，带有成员变量和成员函数，能够提高扩展性。

+ 重载函数（）操作符的类，其对象常称为**函数对象**（function object），也叫仿函数，使得类对象可以像函数调用（）;

注意：

+ 仿函数是一个对象，不是函数
+ 仿函数重载了（）操作符使得其可以像函数一样调用

### 谓词

定义：重载（）操作符且返回值是bool的仿函数。

+ 一元谓词，operator接收一个参数
+ 二元谓词，operator接收两个参数

### 内建函数对象

+ 定义：STL中内建了一些函数对象，分为算数运算符函数对象，逻辑运算符函数对象，关系运算符函数对象。

+ \#include<functional>。

### 常用算法

+ 遍历算法

  + 遍历元素 for_each(iterator beg, iterator end, _callback);

+ 查找算法

  + 普通查找  find(iterator beg, iterator end, value)
  + 条件查找  find_if(iterator beg, iterator end, _callback);
  + 二分查找  bool binary_search(iterator beg, iterator end, value);
  + 统计元素个数 count(iterator beg, iterator end, value);

+ 排序算法

  + 元素排序 sort(iterator beg, iterator end, _callback)
  + 随机打乱位置 random_shuffle(iterator beg, iterator end)
  + 倒序 reverse(iterator beg, iterator end)

+ 集合算法

  + 交集 set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)

  + 并集 set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)
  + 补集 set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)

#### 遍历算法

```C++
/*
    遍历算法 遍历容器元素
	@param beg 开始迭代器
	@param end 结束迭代器
	@param _callback  函数回调或者函数对象
	@return 函数对象
*/
for_each(iterator beg, iterator end, _callback);
```

#### 查找算法

```C++
/*
	find算法 查找元素
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param value 查找的元素
	@return 返回查找元素的位置
*/
find(iterator beg, iterator end, value)
/*
	find_if算法 条件查找
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param  callback 回调函数或者谓词(返回bool类型的函数对象)
	@return bool 查找返回true 否则false
*/
find_if(iterator beg, iterator end, _callback);

/*
	adjacent_find算法 查找相邻重复元素
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param  _callback 回调函数或者谓词(返回bool类型的函数对象)
	@return 返回相邻元素的第一个位置的迭代器
*/
bool binary_search(iterator beg, iterator end, value);

/*
	count算法 统计元素出现次数
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
	@param  value回调函数或者谓词(返回bool类型的函数对象)
	@return int返回元素个数
*/
count(iterator beg, iterator end, value);
```

#### 排序算法

```C++
/*
	sort算法 容器元素排序
	注意:两个容器必须是有序的
	@param beg 容器1开始迭代器
	@param end 容器1结束迭代器
	@param _callback 回调函数或者谓词(返回bool类型的函数对象)
*/
sort(iterator beg, iterator end, _callback)
/*
	sort算法 对指定范围内的元素随机调整次序
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
*/
random_shuffle(iterator beg, iterator end)
/*
	reverse算法 反转指定范围的元素
	@param beg 容器开始迭代器
	@param end 容器结束迭代器
*/
reverse(iterator beg, iterator end)
```

## 相关问题

### 1 STL的两级空间配置器

#### 为什么需要两级空间配置器

原因：在堆上动态开辟内存时，频繁的申请和释放会导致堆上有大量**外部碎片，导致空间利用率降低。**

解决：

+ 当开辟空间小于128字节，选二级空间配置器（默认）
+ 当开辟空间大于128字节，选一级空间配置器。

#### 一级空间配置器

**一级空间配置器**中重要的函数就是allocate、deallocate、reallocate 。 一级空间配置器是以malloc()，free()，realloc()等C函数执行实际的内存配置 。大致过程是：

1、直接allocate分配内存，其实就是malloc来分配内存，成功则直接返回，失败就调用处理函数

2、如果用户自定义了内存分配失败处理函数，定义调用，没定义返回异常

3、 查看是否有内存不足处理函数（），不断释放内存，分配内存。

![一级配置器](D:/all_document/document/document/note/c++/CPP_train_code/C++整合笔记/graph/一级配置器.png)

#### 二级空间配置器

堆内存组成

+ 已经分配的内存：被用户使用的内存
+ 内存池：暂时没有被分配的内存

二级空间配置器组成：

+ freelist数组：**维持一个16个元素的数组空间，每个空间存储链表头结点指针**。分别是0-15号链表，最小8字节，以8字节逐渐递增，最大128字节，
+ free list（自由链表）：每一个节点存储对应区块的地址，

分配方式：

1. **freelist中选择合适内存快**；你传入一个字节参数，表示你需要多大的内存，会自动帮你校对到第几号链表（如需要13bytes空间，我们会给它分配16bytes大小），在找到第n个链表后查看链表是否为空，如果不为空直接从对应的free_list中拔出，将已经拨出的指针向后移动一位。
2. freelist为空，内存池不空
   + 内存池大于等于20，够取出1个给用户，剩下19个挂到链表中。
   + 内存池大于1个节点，取出一个给用户，然后从剩下内存尽可能分配给相应free_list
   + 内存池小于1个节点，直接将内存分配到相应结点，开始3
3. 内存池空，申请内存成功
   + 配置器使用malloc在堆空间中直接申请40块对应节点空间，一半挂载在链表上，一半放入内存池
4. 申请失败
   + 说明heap上没有足够空间分配给我们了，这时，二级空间配置器会从比所需节点空间大的free_list中一一搜索，从比它所需节点空间大的free_list中拔除一个节点来使用。如果这也没找到，说明比其大的free_list中都没有自由区块了，**那就要调用一级适配器了。**

释放方式：

+ 内存大于128直接，调用deallocate函数，调用一级空间配置器
+ 内存小于128，直接将内存挂载在相应的链表位置。

#### 二级配置器的优点和缺点

优点：

+ 解决外部碎片问题，提高效率，频繁申请和释放会使，空间就会增加一些附加信息，降低了空间利用率

缺点：

+ 引入内碎片：节点空间h会自动提升，比如需要1个字节，自动会分配8个字节
+ 二级空间配置器是在堆上申请大块的狭义内存池，然后用自由链表管理。
  + **无法开辟较大内存**：即我不断的开辟小块内存，最后整个堆上的空间都被挂在自由链表上，若我想开辟大块内存就会失败；
  + **内存占用问题**：自由链表上挂很多内存块没有被使用，当前进程又占着内存不释放，这时别的进程在堆上申请不到空间，也不可以使用当前进程的空闲内存，由此就会引发多种问题

### 2  vector与list的区别与应用？怎么找某vector或者list的倒数第二个元素

####  vector数据结构

**特点：**

+ 内存：占用连续地址空间，起始地址一般不变。
+ 高效随机存取：O(1)
+ 插入删除：中间插入删除复杂度高：O(n)，尾部插入删除复杂度低O(1)，
+ 动态增长（和array的主要区别）：当数组中内存空间不够时，会重新申请一块内存空间并进行内存拷贝

#### list数据结构

**特点**：

+ 内存：双向循环链表，内存空间不连续。
+ 随机存取：无法随机存取，只能顺序遍历。O(n)
+ 插入删除：插入删除复杂度低，O(1)

**区别：**

+ 内存：
+ 随机存取
+ 插入删除
+ 迭代器失效：vector中的迭代器在使用后就失效了，而list的迭代器在使用之后还可以继续使用。 

**寻找倒数元素**

+ vector使用下标访问
+ list使用反向迭代器遍历

### 3 STL 中vector删除其中的元素，迭代器如何变化？为什么是两倍扩容？释放空间？

**相关函数**

+ size() 返回已用空间大小
+ capacity() 返回总空间大小
+ reserve(n)  预先分配一块较大的指定大小的内存空间，（空间未满，不会重新分配，可以提升效率），只有当n>capacity()时，调用reserve(n)才会改变vector容量。
+ resize()成员函数只改变元素的数目，不改变容量大小

**两倍扩容**

+ 不同的编译器，vector有不同的扩容大小。在vs下是1.5倍，在GCC下是2倍；

原因：

+ 空间和时间的权衡。简单来说， 空间分配的多，平摊时间复杂度低，但浪费空间也多。

+ 时间：现采用采用成倍方式扩容，可以保证常数的时间复杂度，而增加指定大小的容量只能达到O(n)的时间复杂度

+ 空间：考虑可能产生的堆空间浪费，成倍增长倍数不能太大，使用较为广泛的扩容方式有两种，以2二倍的方式扩容，或者以1.5倍的方式扩容。以2倍的方式扩容，导致下一次申请的内存必然大于之前分配内存的总和，导致之前分配的内存不能再被使用，所以最好倍增长因子设置为(1,2)之间：

  

**缩小空间**

+ 所有的内存空间只有当vector被析构的时候才会被系统回收

+ 使用swap动态缩小空间

+ ```
  vector<Point>().swap(pointVec);
  ```

  swap()是交换函数，使vector离开其自身的作用域，从而强制释放vector所占的内存空间，总而言之，释放vector内存最简单的方法是vector<Point>().swap(pointVec)

### 4 容器内部删除一个元素

+ 顺序容器（序列式容器，比如vector、deque）

  erase迭代器不仅使所指向被删除的迭代器失效，而且使被删元素之后的所有迭代器失效(list除外)，所以不能使用erase(it++)的方式，但是erase的返回值是下一个有效迭代器；

  It = c.erase(it);

+ 关联容器(关联式容器，比如map、set、multimap、multiset等)

  erase迭代器只是被删除元素的迭代器失效，但是返回值是void，所以要采用erase(it++)的方式删除迭代器；

  c.erase(it++)

### 5 STL迭代器如何实现

+ 抽象粘合剂：通过迭代器可以在不了解容器内部原理的情况下遍历容器，作为容器与STL算法的粘合剂

+ **提供容器遍历接口**：
  + 因此迭代器内部必须保存一个与容器相关联的**指针**
  + 重载各种运算操作来遍历，其中最重要的是*运算符与->运算符，以及++、--

### 6 map、set是怎么实现的，红黑树是怎么能够同时实现这两种容器？ 为什么使用红黑树？

实现方式：

+ 使用红黑树实现，
+ map中结点存储key+value，set的结点中存储key

原因：

+ set，map要求自动排序，红黑树自动排序
+ set，map要求高效的插入删除，红黑树的插入删除为O(logn)

### 7 如何在共享内存上使用STL标准库？

 **假设进程A在共享内存中放入了数个容器，进程B如何找到这些容器呢？**

+ 使用共享内存的确定地址：一个方法就是进程A把容器放在共享内存中的确定地址上（fixed offsets），则进程B可以从该已知地址上获取容器。
+ **共享内存的确定地址上存入一个map：**另外一个改进点的办法是，进程A先在共享内存某块确定地址上放置一个map容器，然后进程A再创建其他容器，然后给其取个名字和地址一并保存到这个map容器里。进程B知道如何获取该保存了地址映射的map容器，然后同样再根据名字取得其他容器的地址。

### 8 map的四种插入方式

+ 插入pair
+ 插入make_pair
+ 插入map
+ 以数组方式插入

### 9 STL中unordered_map(hash_map)和map的区别，hash_map如何解决冲突以及扩容

+ 底层实现：
  + 哈希表，底层hash_table实现，使用开链法避免冲突，存储键值对，不对键进行排序，
  + 映射：底层红黑树实现，存储键值对，对键值进行排序
+ 查找：
  + 哈希表，通过key的hash值判断元素是否相同，自定义类型，unordered_map需要定义hash_value函数并且重载operator==
  + 映射，通过二叉排序树的搜索树结构，进行查找，自定义类型，需要重载operator<运算符

扩容时机：

+ 当向容器添加元素的时候，会判断当前容器的元素个数，如果大于等于阈值---即当前数组的长度乘以加载因子的值的时候，就要自动扩容啦。

扩容方式：

+ 重新计算容量，在质数中重新挑选一个质数，扩大数组空间，然后重新hash

### 10、vector越界访问下标，map越界访问下标？vector删除元素时会不会释放空间？

**vector越界访问：**

+ 下标访问：通过下标访问vector中的元素时不会做边界检查，即便下标越界，程序也不会报错，而是返回这个地址中存储的值

+ at函数访问：而且在at函数内部会对下标进行边界检查。

**map越界访问：**

+ 下标访问：下标运算符[]的作用是：将key作为下标去执行查找，并返回相应的值；如果不存在这个key，就将一个具有该key和value的某人值插入这个map。

**删除空间释放：**

+ erase()函数，只能删除内容，不能改变容量大小; 
  + 它删除了itVect迭代器指向的元素，并且返回要被删除的itVect之后的迭代器
  + clear函数清空内容，不释放内存。
  + 需要是释放内存建议使用deque容器。

### 11 map中[]与find的区别？

+ 访问：map的下标运算符[]的作用是：将关键码作为下标去执行查找，并返回对应的值；如果不存在这个关键码，就将一个具有该关键码和值类型的默认值的项插入这个map。

+ 查询：map的find函数：用关键码执行查找，找到了返回该位置的迭代器；如果不存在这个关键码，就返回尾迭代器。

### 12 STL中list与deque之间的区别

+ 底层：
  + list，底层是双向循环链表，在物理上不连续的空间
  + deque，双端队列，底层是双向开口的分段连续内存空间（表面连续，实际不连续），物理上不连续的空间。
+ 迭代器：
  + deque，头尾删除不失效，中间删除，失效。头尾插入可能不失效，其他位置，失效。
  + list，迭代器插入删除后，原迭代器任然有效。
  + list和deque的迭代器度不是普通指针，存储不是连续空间。

### 13 STL中的allocator,deallocator

空间配置器：allocator：**分配内存、构造对象、析构对象、释放内存**

**allocator将内存分配和对象构造分离原因：**

+ 不分离：
  1. 找到一块更大的内存空间，并同时在上面对所有的内存实行对象的**默认构造函数以**实现对象的构造
  2. 将旧的空间的对象一个个通过**拷贝构造函数**赋值给新空间的被默认初始化的新对象，实现对象的移动
  3. 析构旧的空间的对象，然后回收内存空间
+ 分离
  1. 找到一块更大的内存空间
  2. 在这块内存空间上对每一块内存（对象大小的内存块）直接根据旧的空间上的对应位置的对象实行一对一的`placement new`构造
  3. 释放旧空间的内存

总结：将内存分配和对象构造结合，将会扩容时，大量无用构造函数和拷贝构造函数。

一级配置器：>128字节 直接使用malloc()、free()和relloc()

二级配置器：<128字节 allocate、deallocate、reallocate函数，

+ 空间配置函数allocate()，首先判断区块大小，大于128就直接调用第一级配置器，小于128时就检查对应的free-list。如果free-list之内有可用区块，就直接拿来用，如果没有可用区块，就将区块大小调整至8的倍数，然后调用refill()，为free-list重新分配空间；

+ 空间释放函数deallocate()，该函数首先判断区块大小，大于128bytes时，直接调用一级配置器，小于128bytes就找到对应的free-list然后释放内存。

### 14 常见容器性质总结？

1.vector    底层数据结构为数组 ，支持快速随机访问

2.list       底层数据结构为双向链表，支持快速增删

3.deque    底层数据结构为一个中央控制器和多个缓冲区，详细见STL源码剖析P146，支持首尾（中间不能）快速增删，也支持随机访问

deque是一个双端队列(double-ended queue)，也是在堆中保存内容的.它的保存形式如下:

[堆1] --> [堆2] -->[堆3] --> ...

每个堆保存好几个元素,然后堆和堆之间有指针指向,看起来像是list和vector的结合品.

4.stack    底层一般用list或deque实现，封闭头部即可，不用vector的原因应该是容量大小有限制，扩容耗时

5.queue   底层一般用list或deque实现，封闭头部即可，不用vector的原因应该是容量大小有限制，扩容耗时（stack和queue其实是适配器,而不叫容器，因为是对容器的再封装）

6.priority_queue   的底层数据结构一般为vector为底层容器，堆heap为处理规则来管理底层容器实现

7.set          底层数据结构为红黑树，有序，不重复

8.multiset      底层数据结构为红黑树，有序，可重复 

9.map         底层数据结构为红黑树，有序，不重复

10.multimap  底层数据结构为红黑树，有序，可重复

11.unordered_set   底层数据结构为hash表，无序，不重复

12.unordered_multiset 底层数据结构为hash表，无序，可重复 

13.unordered_map   底层数据结构为hash表，无序，不重复

14.unordered_multimap 底层数据结构为hash表，无序，可重复 

### 15 说一下STL每种容器对应的迭代器

| 容器                                   | 迭代器         |
| -------------------------------------- | -------------- |
| vector、deque                          | 随机访问迭代器 |
| stack、queue、priority_queue           | 无             |
| list、(multi)set/map                   | 双向迭代器     |
| unordered_(multi)set/map、forward_list | 前向迭代器     |

### 16 set和map的区别，multimap和multiset的区别

**set和map区别：数据类型接口，比较函数**

+ set只提供一种数据类型的**接口**，但是会将这一个元素分配到key和value上，而且它的**compare_function用的是 identity()函数**，这个函数是输入什么输出什么，这样就实现了set机制，set的key和value其实是一样的了。其实他保存的是两份元素，而不是只保存一份元素

+ map则提供两种数据类型的**接口**，分别放在key和value的位置上，他的**比较function采用的是红黑树的comparefunction（）**，保存的确实是两份元素。

他们两个的insert都是采用红黑树的insert_unique() 独一无二的插入 。

**map和multimap区别**（插入方式）

+ multimap和map的唯一区别就是：multimap调用的是红黑树的insert_equal(),可以重复插入

+ map调用的则是独一无二的插入insert_unique()，