#include "task3.h"

#define LEN 100000
Row global[LEN];

int main(int argc, char **argv) {
    prepare(global, LEN);
    task0(global, LEN);
    std::cout << "\n\n\n---task1---\n\n\n";
    task1(global, LEN);
    std::cout << "\n\n\n---task2---\n\n\n";

    task2(global, LEN);
    std::cout << "\n\n\n---task3---\n\n\n";
    task3(global, LEN);
    std::cout << "\n\n\n---task3-stl---\n\n\n";
    task3_stl_sort(global, LEN);
}
