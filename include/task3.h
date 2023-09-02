#pragma once

#include <iostream>
struct Row {
  int a;
  int b;
};

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

void prepare(Row* rows, int nrow) {
    std::ios::sync_with_stdio(false);
    for (auto i = 0; i < nrow; i++) {
        rows[i].b = i / (nrow / 10000);
        rows[i].a = 500 + i / (nrow / 1000);
    }
}

void task0(const Row* rows, int nrow) {
    for (auto i = 0; i < nrow; i++) {
        auto temp = rows[i];
    }
}

// no sort
void task1(const Row* rows, int nrow) {
    for (auto i = 0; i < nrow; i++) {
        if ((rows[i].b>= 10) && rows[i].b < 50 &&
        (rows[i].a == 1000 || rows[i].a == 2000 || rows[i].a == 3000)) {
            std::cerr << rows[i].a << "," << rows[i].b << "\n";
        }
    }
}

// is sort by a,b
void task2(const Row* rows, int nrow) {
    for (auto i = 0; i < nrow; i++) {
        if ((rows[i].b>= 10) && rows[i].b < 50 &&
        (rows[i].a == 1000 || rows[i].a == 2000 || rows[i].a == 3000)) {
            std::cerr << rows[i].a << "," << rows[i].b << "\n";
        }
    }
}

// is sort by ab, result as sort b
void task3(const Row* rows, int nrow) {
    for (auto i = 0; i < nrow; i++) {
        if ((rows[i].b>= 10) && rows[i].b < 50 &&
        (rows[i].a == 1000 || rows[i].a == 2000 || rows[i].a == 3000)) {
            std::cerr << rows[i].a << "," << rows[i].b << "\n";
        }
    }
}