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
            
            char message[100]; // this is inefficient code!
            input.getline(message, 100);

            logentry curr;
            curr.timestamp = std::stoi(timestamp);
            curr.content = std::string(message);

            logs.push_back(curr);
        }

        input.close();
    }

    std::sort(logs.begin(), logs.end());

    std::ofstream output("../log/aggregated.log");
    for (const logentry& entry : logs) {
        output << entry << std::endl;
    }
    output.close();
}

// int main() {
//     tsaggregate({"../log/1.log", "../log/2.log"});
// }