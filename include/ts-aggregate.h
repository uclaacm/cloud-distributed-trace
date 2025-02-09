#pragma once

#include <string>
#include <vector>

struct logentry {
    int timestamp;
    std::string content;

    friend bool operator<(const logentry& lhs, const logentry& rhs);
    friend std::ostream& operator<<(std::ostream& stream, const logentry& output);
};

void tsaggregate(const std::vector<std::string>& filepaths);