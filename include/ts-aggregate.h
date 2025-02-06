#pragma once

#include <string>
#include <vector>

struct logentry {
    int timestamp;
    std::string content;
};

void tsaggregate(std::vector<std::string> filepaths[]);