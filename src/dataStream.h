#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include "Serializable.h"

namespace serialize {

enum class DataType : uint8_t
{
    BOOL = 0,
    CHAR,
    INT32,
    INT64,
    FLOAT,
    DOUBLE,
    STRING,
    VECTOR,
    LIST,
    MAP,
    SET,
    UNORDERED_MAP,
    CUSTOM
};

class DataStream {
public:
    DataStream();
    DataStream(const std::string & data);
    ~DataStream();

    void reserve(int len);

    void write(const char * data, int len);
    void write(bool value);
    void write(char value);
    void write(int32_t value);
    void write(int64_t value);
    void write(float value);
    void write(double value);
    void write(const char * value);
    void write(const std::string & value);

    // 复合类型
    template<typename T>
    void write(const std::vector<T> & value);

    template<typename T>
    void write(const std::list<T> & value);

    template<typename T>
    void write(const std::set<T> & value);

    template<typename K, typename V>
    void write(const std::map<K, V> & value);

    template<typename K, typename V>
    void write(const std::unordered_map<K, V> & value);

    // 自定义类型
    void write(const Serializable & value);
    bool read(Serializable & value);

    /*写入重载*/
    DataStream& operator<< (bool value);
    DataStream& operator<< (char value);
    DataStream& operator<< (int32_t value);
    DataStream& operator<< (int64_t value);
    DataStream& operator<< (float value);
    DataStream& operator<< (double value);
    DataStream& operator<< (const char * value);
    DataStream& operator<< (const std::string & value);
    DataStream& operator<< (const Serializable & value);

    template<typename T>
    DataStream& operator<< (const std::vector<T> & value) {
        write(value);
        return *this;
    }

    template<typename T>
    DataStream& operator<< (const std::list<T> & value) {
        write(value);
        return *this;
    }

    template<typename T>
    DataStream& operator<< (const std::set<T> & value) {
        write(value);
        return *this;
    }

    template<typename K, typename V>
    DataStream& operator<< (const std::map<K, V> & value) {
        write(value);
        return *this;
    }

    template<typename K, typename V>
    DataStream& operator<< (const std::unordered_map<K, V> & value) {
        write(value);
        return *this;
    }

    /*读出重载*/
    bool read(char * data, int len);
    bool read(bool & value);
    bool read(char & value);
    bool read(int32_t & value);
    bool read(int64_t & value);
    bool read(float & value);
    bool read(double & value);
    bool read(std::string & value);

    template<typename T>
    bool read(std::vector<T> & value);

    template<typename T>
    bool read(std::list<T> & value);

    template<typename T>
    bool read(std::set<T> & value);

    template<typename K, typename V>
    bool read(std::map<K, V> & value);

    template<typename K, typename V>
    bool read(std::unordered_map<K, V> & value);

    DataStream & operator >> (bool & value);
    DataStream & operator >> (char & value);
    DataStream & operator >> (int32_t & value);
    DataStream & operator >> (int64_t & value);
    DataStream & operator >> (float & value);
    DataStream & operator >> (double & value);
    DataStream & operator >> (std::string & value);
    DataStream & operator >> (Serializable & value);

    template<typename T>
    DataStream & operator >> (std::vector<T> & value) {
        read(value);
        return *this;
    }

    template<typename T>
    DataStream & operator >> (std::list<T> & value) {
        read(value);
        return *this;
    }

    template<typename T>
    DataStream & operator >> (std::set<T> & value) {
        read(value);
        return *this;
    }

    template<typename K, typename V>
    DataStream & operator >> (std::map<K, V> & value) {
        read(value);
        return *this;
    }

    template<typename K, typename V>
    DataStream & operator >> (std::unordered_map<K, V> & value) {
        read(value);
        return *this;
    }
    
private:
    std::vector<char> buf_;
    int pos_;
};


template<typename T>
void DataStream::write(const std::vector<T> & value) {
    char type = static_cast<char>(DataType::VECTOR);
    write((char *)&type, sizeof(char));
    write(static_cast<int>(value.size()));
    for (const auto& v : value)
    {
        write(v);
    }
}

template<typename T>
void DataStream::write(const std::list<T> & value) {
    char type = static_cast<char>(DataType::LIST);
    write((char *)&type, sizeof(char));
    write(static_cast<int>(value.size()));
    for (const auto& v : value) {
        write(v);
    }
}

template<typename T>
void DataStream::write(const std::set<T> & value) {
    char type = static_cast<char>(DataType::SET);
    write((char *)&type, sizeof(char));
    write(static_cast<int>(value.size()));
    for (const auto& v : value) {
        write(v);
    }
}

template<typename K, typename V>
void DataStream::write(const std::map<K, V> & value) {
    char type = static_cast<char>(DataType::MAP);
    write((char *)&type, sizeof(char));
    write(static_cast<int>(value.size()));
    for (const auto& v : value) {
        write(v.first);
        write(v.second);
    }
}

template<typename K, typename V>
void DataStream::write(const std::unordered_map<K, V> & value) {
    char type = static_cast<char>(DataType::UNORDERED_MAP);
    write((char *)&type, sizeof(char));
    write(static_cast<int>(value.size()));
    for (const auto& v : value) {
        write(v.first);
        write(v.second);
    }
}

template<typename T>
bool DataStream::read(std::vector<T> & value) {
    if(buf_[pos_] != static_cast<char>(DataType::VECTOR)) {
        return false;
    }
    ++pos_;
    int len;
    if(!read(len)) {
        return false;
    }
    value.resize(len);
    for (int i = 0; i < len; ++i) {
        if(!read(value[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool DataStream::read(std::list<T> & value) {
    if(buf_[pos_] != static_cast<char>(DataType::LIST)) {
        return false;
    }
    ++pos_;
    int len;
    if(!read(len)) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        T v;
        if(!read(v)) {
            return false;
        }
        value.push_back(v);
    }
    return true;
}

template<typename T>
bool DataStream::read(std::set<T> & value) {
    if(buf_[pos_] != static_cast<char>(DataType::SET)) {
        return false;
    }
    ++pos_;
    int len;
    if(!read(len)) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        T v;
        if(!read(v)) {
            return false;
        }
        value.insert(v);
    }
    return true;
}

template<typename K, typename V>
bool DataStream::read(std::map<K, V> & value) {
    if(buf_[pos_] != static_cast<char>(DataType::MAP)) {
        return false;
    }
    ++pos_;
    int len;
    if(!read(len)) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        K k;
        V v;
        if(!read(k) || !read(v)) {
            return false;
        }
        value[k] = v;
    }
    return true;
}

template<typename K, typename V>
bool DataStream::read(std::unordered_map<K, V> & value) {
    if(buf_[pos_] != static_cast<char>(DataType::UNORDERED_MAP)) {
        return false;
    }
    ++pos_;
    int len;
    if(!read(len)) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        K k;
        V v;
        if(!read(k) || !read(v)) {
            return false;
        }
        value[k] = v;
    }
    return true;
}

}