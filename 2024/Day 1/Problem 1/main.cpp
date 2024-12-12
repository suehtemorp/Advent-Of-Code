#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream input("input.txt", std::ifstream::in);
    if (! input.is_open()) {
        printf("Unable to open input.txt\n");
        return -1;
    }

    std::size_t n;
    std::vector<std::size_t> first, second;

    while (input.good()) {
        try {
            input >> n;
            first.push_back(n);

            input >> n;
            second.push_back(n);
        } catch(const std::exception& e) {
            printf("Unable to read ID: %s\n", e.what());
            return -1;
        }
    }

    if (first.size() != second.size()) {
        printf(
            "Different amount of IDs in list #1 (%zu) and #2 (%zu)\n", 
            first.size(), second.size()
        );
        return -1;
    }

    n = 0;
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    for (std::size_t i = 0; i < first.size(); ++i) {
        const std::size_t& a = first[i];
        const std::size_t& b = second[i];

        n += a > b ? a - b : b - a;
    }

    printf("Sum of all pairwise distance between IDs: %zu\n", n);
    return 0;
}