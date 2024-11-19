# 一个轻量的c++序列化库

这是一个轻量级的C++序列化库，旨在帮助开发者快速理解和实现序列化功能。本项目主要用于学习和研究，目前还不适合在生产环境中使用。

## 1.支持的功能

* **基本数据类型**：支持 `char`, `bool`, `int`, `float`, `double`, `string` 的序列化（可继续扩展）。
* **复合数据类型**：支持 `vector`, `list`, `set`, `map`, `unordered_map` 的序列化（可继续扩展）。
* **自定义类型**：支持自定义类型的序列化，但需要用户实现一些额外的工作。

## 2.编译运行此项目

```shell
git clone https://github.com/puoxiu/lsl.git
cd lsl
mkdir build
cd build
cmake ..
make

# 分别测试基本数据类型
./bin/test1
# 复合数据类型
./bin/test2
# 自定义数据类型
./bin/test3
```

## 3.对自定义类型序列化

需要继承抽象类：Serializable，并重写serialize & deserialize：

```c++
#include "dataStream.h"
#include <iostream>

class A : public serialize::Serializable {
public:
    A() : a(0), b(0),str("") {}
    A(int a, int b, std::string str = "default-str") : a(a), b(b),str(str) {}

    void serialize(serialize::DataStream &ds) const override {
        char type = static_cast<char>(serialize::DataType::CUSTOM);
        ds.write((char *)&type, sizeof(char));
        ds << a << b << str;
    }

    bool deserialize(serialize::DataStream &ds) override {
        char type;
        ds.read((char *)&type, sizeof(char));
        if(type != static_cast<char>(serialize::DataType::CUSTOM)) {
            return false;
        }
        ds >> a >> b >> str;
        return true;
    }
    int getA() const {
        return a;
    }
    int getB() const {
        return b;
    }
    std::string getStr() const {
        return str;
    }
private:
    int a;
    int b;
    std::string str;
};

int main()
{
    serialize::DataStream ds;
    
    A a(1, 2);
    ds << a;

    A b;
    ds >> b;
    std::cout << b.getA() << " " << b.getB() << " " << b.getStr() << std::endl;
    return 0;
}
```

## 4.TODO

* 数据持久化
* 大/小端支持
* 自定义类型序列化使用方式优化