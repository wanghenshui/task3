#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <cstdint>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>


struct Row {
  int a;
  int b;
};

bool operator==(const Row& l, const Row& r) {
    return l.a == r.a && l.b == r.b;
}

// 基于b的偏序
bool operator<(const Row& l, const Row& r) {
    return l.b < r.b || (l.b == r.b && l.a < r.a);
}

/*
Row sorted_rows[] =
{
{ 1000, 31 },
{ 1000, 72 },
{ 1500, 12 },
{ 1500, 34 },
{ 2000, 22 },
{ 2000, 33 },
};

*/

// #define OUTPUT_PRINT
// #undef OUTPUT_PRINT

void prepare(Row* rows, int nrow) {
    for (auto i = 0; i < nrow; i++) {
        rows[i].b = i  % 33333;
        // 映射15697
        //int mod = nrow / 15697;
        //rows[i].a =  i  / mod;
        rows[i].a = i / 100;
    }
}

int warm(Row* rows, int nrow) {
    auto count = 0;
    for (auto i = 0; i < nrow; i++) {
        auto temp = rows[i];
        count++;
    }
    return count;
}

// 遍历
// 范围比较放前面
int task1(const Row* rows, int nrow) {
    int count = 0;
    for (auto i = 0; i < nrow; i++) {
        if ((rows[i].b>= 10) && rows[i].b < 50 &&
        (rows[i].a == 1000 || rows[i].a == 2000 || rows[i].a == 3000)) {
#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif
            count++;
        }
    }
    return count;
}



// 二分 a b
int find_ab(const Row* rows,int len, int start, int target) {
    int i = 0;
    size_t step = 0;
    while (len > 0) {
        step = (len + start) / 2;
        if (rows[step].a < target ||
         (rows[step].a == target && rows[step].b < 10)){
            i = step+1; 
            len -= step + 1; 
        } else {
            len = step;
        }
    }
    return i;
}
// is sort by a,b
// 二分找到上下界，判断是否满足10<=x<50
int task2(const Row* rows, int nrow) {
    auto loop = nrow;
    auto count = 0;
    size_t i = 0;
    std::vector<int> targets = {1000, 2000, 3000};
    for (auto target : targets) {
        i = find_ab(rows, nrow, i, target);
        for (;i<nrow &&rows[i].a <= target;i++) {
            if (rows[i].a == target && rows[i].b >= 10 && rows[i].b < 50) {

#ifdef OUTPUT_PRINT
                std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif

                count++;
            }
        }
    }
   
    return count;
}


// is sort by ab, result as sort b
// bucket，相当于桶为3 桶排序
// 如果满足条件的b过多， 归并效果不如std::sort(比较次数太多)

int task3_stl_sort(const Row* rows, int nrow) {
    auto count = 0;
    size_t i = 0;

    std::vector<Row> sortOfB;
    sortOfB.reserve(1000);
    std::vector<int> targets = {1000, 2000, 3000};
    for (auto target : targets) {
        i = find_ab(rows, nrow, i, target);
        for (;i<nrow &&rows[i].a <= target;i++) {
            if (rows[i].a == target && rows[i].b>= 10 && rows[i].b < 50) {
                sortOfB.push_back(rows[i]);
                count ++;
            }
        }
    }

    std::sort(sortOfB.begin(), sortOfB.end(), 
        [](const Row& a, const Row&b) {
                return a.b < b.b;
            }
        );
#ifdef OUTPUT_PRINT
    for (auto& v : sortOfB) {
         std::cout << v.a << "," << v.b << "\n";
    }
#endif

    return count;
}

