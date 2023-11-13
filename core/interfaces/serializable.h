#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <vector>

class serializable {
public:
    virtual std::vector<std::string> serialize() const = 0;
    virtual void deserialize(const std::vector<std::string>& data) = 0;
    virtual ~serializable() = default;
};

#endif