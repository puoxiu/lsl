#include "dataStream.h"
#include <iostream>

class A : public serialize::Serializable {
public:
    A() : a(0), b(0),str("") {}
    A(int a, int b, std::string str = "default") : a(a), b(b),str(str) {}

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