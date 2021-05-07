# C++常见面试问题汇总

## **1 gcc和g++区别**

GCC和gcc是不同的东西

>  GCC:GNU Compiler Collection(GUN 编译器集合)，它可以编译C、C++、JAV、Fortran、Pascal、Object-C、Ada等语言。

+ gcc是GCC中的GUN C Compiler（C 编译器）

+ g++是GCC中的GUN C++ Compiler（C++编译器）

**gcc和g++本质**：cc和g++并不是编译器，也不是编译器的集合，它们只是一种驱动器，根据参数中要编译的文件的类型，调用对应的GUN编译器而已，：gcc调用了C compiler，而g++调用了C++ compiler。

**gcc编译c的步骤**

+ 调用一个预处理器
+ 调用实际的编译器
+ 调用一个汇编程序
+ 调用一个链接器

**gcc和g++的主要区别**

+ 对于 *.c和*.cpp文件，gcc分别当做c和cpp文件编译（c和cpp的语法强度是不一样的）

+ 对于 *.c和*.cpp文件，g++则统一当做cpp文件编译

+ 使用g++编译文件时，**g++会自动链接标准库STL，而gcc不会自动链接STL**
+ 在用gcc编译c++文件时，为了能够使用STL，需要加参数 –lstdc++ ，但这并不代表 gcc –lstdc++ 和 g++等价，

## 2 赋值运算符重载

题目：为自定义的string类型添加赋值运算符

考虑因素：

+ 返回值的类型声明为当前类对象（`* this`）的引用，只有引用对象才能连续赋值
+ 传入的参数是否为常量引用
  + 如果参数不是引用，实参对形参的赋值会调用一次拷贝复制函数
  + 引用不会改变实参
+ 是否把string中原有的内存释放
+ 判断传入的对象是否是当前的string对象。
  + 不进行判断，会使得释放内存，此时将无法找回内存。

```c++
MyString& MyString:: operator=(const MyString& str)
{
    if(&str==this)
        return *this;
    delete [] mp_data;
    mp_data=nullptr;
    mp_data=new char[strlen(str.mp_data)+1];
    strcpy(m_pdata,str.mp_data);
    return *this;
}
```

高级：考虑一些异常

+ 内存不足异常
  + 当申请新空间时，因为内存不足原因，可能导致程序抛出异常，因此我们解决的思路是，先申请新的内存，然后使用delete释放内存。