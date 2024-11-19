#include "dataStream.h"
#include <iostream>

int main()
{
    serialize::DataStream ds;

    int a = 100, aa;
    bool b = true, bb;
    float c = 3.14, cc;
    std::string d = "hello world", dd;

    ds << a << b << c << d;

    ds >> aa >> bb >> cc >> dd;

    std::cout <<"a = " << a << ",aa = " << aa << std::endl;
    std::cout <<"b = " << b << ",bb = " << bb << std::endl;
    std::cout <<"c = " << c << ",cc = " << cc << std::endl;
    std::cout <<"d = " << d << ",dd = " << dd << std::endl;


    return 0;
}