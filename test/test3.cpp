#include "dataStream.h"


int main()
{
    serialize::DataStream ds;

    std::vector<int> a = {1, 2, 3, 4, 5}, aa;
    std::list<int> b = {1, 2, 3, 4, 5}, bb;
    std::set<int> c = {1, 2, 3, 4, 5}, cc;
    std::map<int, int> d = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}, dd;
    std::vector<std::vector<int>> e = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, ee;
    std::vector<std::string> f = {"hello", "world", "nihao"}, ff;

    ds << a << b << c << d << e << f;

    ds >> aa >> bb >> cc >> dd >> ee >> ff;

    std::cout << "a: ";
    for (auto &i : aa)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "b: ";
    for (auto &i : bb)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "c: ";
    for (auto &i : cc)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "d: ";
    for (auto &i : dd)
    {
        std::cout << i.first << " " << i.second << " ";
    }
    std::cout << std::endl;

    std::cout << "e: ";
    for (auto &i : ee)
    {
        for (auto &j : i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "f: ";
    for (auto &i : ff)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}