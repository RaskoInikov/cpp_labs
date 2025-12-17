#pragma once
#include <string>
#include <stdexcept>

class File
{
protected:
    std::string filename;

public:
    explicit File(const std::string &name)
        : filename(name) {}

    virtual ~File() = default;

    virtual void save() = 0;
    virtual void load() = 0;
};
