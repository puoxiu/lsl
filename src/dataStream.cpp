#include "dataStream.h"

using namespace serialize;

DataStream::DataStream(): pos_(0) {

}
DataStream::DataStream(const std::string & data) {
    buf_.clear();
    reserve(data.size());
    write(data.c_str(), data.size());
}
DataStream::~DataStream() {}

/*
    扩充容量但不扩充size
*/
void DataStream::reserve(int len)
{
    int size = buf_.size();
    int cap = buf_.capacity();
    if (size + len > cap) {
        while (size + len > cap) {
            if (cap == 0) {
                cap = 1;
            } else {
                cap *= 2;
            }
        }
        buf_.reserve(cap);
    }
}
/*

*/
void DataStream::write(const char* data, int len) {
    reserve(len);
    int size = buf_.size();
    buf_.resize(size + len);
    std::memcpy(&buf_[size], data, len);
}

void DataStream::write(bool value) {
    char type = static_cast<char> (DataType::BOOL);
    write((char *)&type, sizeof(char));
    write((char *)&value, sizeof(bool));
}
void DataStream::write(char value) {
    char type = static_cast<char> (DataType::CHAR);
    write((char *)&type, sizeof(char));
    write((char *)&value, sizeof(char));
}
void DataStream::write(int32_t value) {
    char type = static_cast<char> (DataType::INT32);
    write((char *)&type, sizeof(char));
    write((char *)&value, sizeof(int32_t));
}

void DataStream::write(int64_t value) {
    char type = static_cast<char> (DataType::INT64);
    write((char *)&type, sizeof(char));
    write((char *)&value, sizeof(int64_t));
}
void DataStream::write(float value) {
    char type = static_cast<char> (DataType::FLOAT);
    write((char *)&type, sizeof(char));
    write((char *)&value, sizeof(float));
}
void DataStream::write(double value) {
    char type = static_cast<char> (DataType::DOUBLE);
    write((char *)&type, sizeof(char));
    write((char *)&value, sizeof(double));
}
void DataStream::write(const char* value) {
    char type = static_cast<char> (DataType::STRING);
    write((char *)&type, sizeof(char));
    int len = strlen(value);
    write(len);
    write(value, len);
}
void DataStream::write(const std::string& value) {
    char type = static_cast<char> (DataType::STRING);
    write((char *)&type, sizeof(char));
    int len = value.size();
    write(len);
    write(value.data(), len);
}

void DataStream::write(const Serializable& value) {
    value.serialize(*this);
}

DataStream& DataStream::operator<< (bool value) {
    write(value);
    return *this;
}

DataStream& DataStream::operator<< (char value) {
    write(value);
    return *this;
}
DataStream& DataStream::operator<< (int32_t value) {
    write(value);
    return *this;
}
DataStream& DataStream::operator<< (int64_t value) {
    write(value);
    return *this;
}
DataStream& DataStream::operator<< (float value) {
    write(value);
    return *this;
}
DataStream& DataStream::operator<< (double value) {
    write(value);
    return *this;
}
DataStream& DataStream::operator<< (const char * value) {
    write(value);
    return *this;
}
DataStream& DataStream::operator<< (const std::string & value) {
    write(value);
    return *this;
}
DataStream& DataStream::operator<< (const Serializable & value) {
    write(value);
    return *this;
}

bool DataStream::read(char * data, int len) {
    std::memcpy(data, (char*)&buf_[pos_], len);
    pos_ += len;
    return true;
}
bool DataStream::read(bool & value) {
    if(buf_[pos_] != static_cast<char>(DataType::BOOL)) {
        return false;
    }
    ++pos_;
    // read((char*)&value, sizeof(bool));
    value = buf_[pos_];
    ++pos_;
    return true;
}
bool DataStream::read(char & value) {
    if(buf_[pos_] != static_cast<char>(DataType::CHAR)) {
        return false;
    }
    ++pos_;
    // read((char*)&value, sizeof(bool));
    value = buf_[pos_];
    ++pos_;
    return true;
}
bool DataStream::read(int32_t & value)
{
    if (buf_[pos_] != static_cast<char>( DataType::INT32))
    {
        return false;
    }
    ++pos_;
    if(!read((char*)&value, sizeof(int32_t)))
        return false;

    return true;
}
bool DataStream::read(int64_t & value) {
    if(buf_[pos_] != static_cast<char>(DataType::INT64)) {
        return false;
    }
    ++pos_;
    // read((char*)&value, sizeof(bool));
    // 读取4字节
    if(!read((char*)&value, sizeof(int64_t)))
        return false;
    return true;
}
bool DataStream::read(float & value) {
    if(buf_[pos_] != static_cast<char>(DataType::FLOAT)) {
        return false;
    }
    ++pos_;
    // read((char*)&value, sizeof(bool));
    // 读取4字节
    if(!read((char*)&value, sizeof(float)))
        return false;
    return true;
}
bool DataStream::read(double & value) {
    if(buf_[pos_] != static_cast<char>(DataType::DOUBLE)) {
        return false;
    }
    ++pos_;
    // read((char*)&value, sizeof(bool));
    // 读取4字节
    if(!read((char*)&value, sizeof(double)))
        return false;
    return true;
}
bool DataStream::read(std::string & value) {
    char t = buf_[pos_];
    if(t != static_cast<char>(DataType::STRING)) {
        return false;
    }

    pos_++;
    int len;
    read(len);
    if(len < 0) {
        return false;
    }
    value.assign((char*)&(buf_[pos_]), len);
    pos_ += len;

    return true;
}

bool DataStream::read(Serializable & value) {
    value.deserialize(*this);
    return true;
}

DataStream& DataStream::operator >> (bool & value) {
    read(value);
    return *this;
}
DataStream& DataStream::operator >> (char & value) {
    read(value);
    return *this;
}
DataStream& DataStream::operator >> (int32_t & value) {
    read(value);
    return *this;
}
DataStream& DataStream::operator >> (int64_t & value) {
    read(value);
    return *this;
}
DataStream& DataStream::operator >> (float & value) {
    read(value);
    return *this;
}
DataStream& DataStream::operator >> (double & value) {
    read(value);
    return *this;
}
DataStream& DataStream::operator >> (std::string & value) {
    read(value);
    return *this;
}

DataStream& DataStream::operator >> (Serializable & value) {
    read(value);
    return *this;
}