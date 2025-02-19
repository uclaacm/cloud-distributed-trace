#include "../include/ts-aggregate.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


bool operator<(const logentry& lhs, const logentry& rhs) {
    if (lhs.timestamp < rhs.timestamp) return true;
    else return false;
}

std::ostream& operator<<(std::ostream& stream, const logentry& output) {
    stream << output.timestamp << ' ' << output.content;
    return stream;
}

void tsaggregate(const std::vector<std::string>& filepaths) {
    std::vector<logentry> logs;

    for (const std::string& filename : filepaths) {
        std::ifstream input(filename);

        while (input.peek()!=-1) {
            std::string timestamp;
            input >> timestamp;
            
            std::string message;
            std::getline(input, message, '\n');

            logentry curr;
            curr.timestamp = std::stoi(timestamp);
            curr.content = std::string(message);

            logs.push_back(curr);
        }

        input.close();
    }

    std::sort(logs.begin(), logs.end());

    // automatically creates log/aggregated.log if it does not exist. however,
    // WARNING! overrides ALL existing data in log/aggregated.log. if needed,
    // a backup log functionality can be provided. we'll see.
    std::ofstream output("../log/aggregated.log", std::ios_base::out);
    for (const logentry& entry : logs) {
        output << entry << std::endl;
    }
    output.close();
}

// int main() {
//     tsaggregate({"../log/1.log", "../log/2.log"});
// }