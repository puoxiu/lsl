#pragma once

namespace serialize {

class DataStream;

class Serializable {
public:
    virtual void serialize(DataStream &ds) const = 0;
    virtual bool deserialize(DataStream &ds) = 0;
};

}