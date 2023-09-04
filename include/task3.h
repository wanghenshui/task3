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

int task0(const Row* rows, int nrow) {
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

// 旧版本简化，只二分a
int find_a(const Row* rows,int len, int start,  int target) {
    int i = 0;
    size_t step = 0;
    while (len > 0) {
        step = (len + start) / 2;
        if (rows[step].a < target){
            i = step+1; 
            len -= step + 1; 
        } else {
            len = step;
        }
    }
    return i;
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

    i = find_a(rows, nrow, i, 1000);
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b>= 10 && rows[i].b < 50) {

#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif

            count++;
        }
    }
    i = find_a(rows, nrow, i, 2000);
    for (;i<nrow &&rows[i].a <= 2000 ;i++) {
        if (rows[i].a == 2000 && rows[i].b>= 10 && rows[i].b < 50) {
            
#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif
            count++;
        }
    }
    i = find_a(rows, nrow, i, 3000);
    for (;i<nrow && rows[i].a <= 3000;i++) {
        if (rows[i].a == 3000 && rows[i].b>= 10 && rows[i].b < 50) {
 
#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif

            count++;
        }
    }
    return count;
}

int task2b(const Row* rows, int nrow) {
    auto loop = nrow;
    auto count = 0;
    size_t i = 0;

    i = find_ab(rows, nrow, i, 1000);
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b >= 10 && rows[i].b < 50) {

#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif

            count++;
        }
    }
    i = find_ab(rows, nrow, i, 2000);
    for (;i<nrow &&rows[i].a <= 2000;i++) {
        if (rows[i].a == 2000 && rows[i].b >= 10 && rows[i].b < 50) {
            
#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif
            count++;
        }
    }
    i = find_ab(rows, nrow, i, 3000);
    for (;i<nrow && rows[i].a <= 3000;i++) {
        if (rows[i].a == 3000 && rows[i].b >= 10  && rows[i].b < 50 ) {
 
#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif

            count++;
        }
    }
    return count;
}


// is sort by ab, result as sort b
// bucket，相当于桶为3 桶排序
// 如果满足条件的b过多，导致桶太深，效果不如std::sort(比较次数太多)
int task3(const Row* rows, int nrow) {
    auto count = 0;
    size_t i = 0;
    size_t start_1 = 0;
    size_t count_1 = 0;
    size_t start_2 = 0;
    size_t count_2 = 0;
    size_t count_3 = 0;
    size_t start_3 = 0;

    i = find_a(rows, nrow, i, 1000);
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b>= 10 && rows[i].b < 50) {
            if (start_1 == 0) {
                start_1 = i;
            }
            
            count_1 ++;
        }
    }

    i = find_a(rows, nrow, i, 2000);
    for (;i<nrow &&rows[i].a <= 2000;i++) {
        if (rows[i].a == 2000&& rows[i].b>= 10 && rows[i].b < 50) {
            if (start_2 == 0) {
                start_2 = i;
            }

            count_2 ++;
        }
    }


    i = find_a(rows, nrow, i, 3000);
    for (;i<nrow && rows[i].a <= 3000;i++) {
        if (rows[i].a == 3000&& rows[i].b>= 10 && rows[i].b < 50) {
            if (start_3 == 0) {
                start_3 = i;
            }
            count_3 ++;
        }
    }

    count = count_1 + count_2 + count_3;
    while (count_1 || count_2 || count_3) {
        Row min_row {INT32_MAX,INT32_MAX};
        bool e1 = false;
        bool e2 = false;
        bool e3 = false;

        if (count_1 != 0) {
            min_row = min_row < rows[start_1] ? min_row : rows[start_1];
            e1 = min_row == rows[start_1];
        }
        if (count_2 != 0) {
            min_row = min_row < rows[start_2] ? min_row : rows[start_2];
            e2 = min_row == rows[start_2];
            if (e2) {
                e1 = false;
            }
        }
        if (count_3 != 0) {
            min_row = min_row < rows[start_3] ? min_row : rows[start_3];
            e3 = min_row == rows[start_3];
            if (e3) {
                e1 = false;
                e2 = false;
            }
        }
        if (e1) {
            start_1 ++ ;
            count_1 --;
        }
        if (e2) {
            start_2 ++ ;
            count_2 --;
        }
        if (e3) {
            start_3 ++ ;
            count_3 --;
        }
#ifdef OUTPUT_PRINT
        std::cout << min_row.a << "," << min_row.b << "\n";
#endif
    }
    return count;
}

// 补充基于b的二分
int task3b(const Row* rows, int nrow) {
    auto count = 0;
    size_t i = 0;
    size_t start_1 = 0;
    size_t count_1 = 0;
    size_t start_2 = 0;
    size_t count_2 = 0;
    size_t count_3 = 0;
    size_t start_3 = 0;

    i = find_ab(rows, nrow, i, 1000);
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b>= 10 && rows[i].b < 50) {
            if (start_1 == 0) {
                start_1 = i;
            }
            
            count_1 ++;
        }
    }

    i = find_ab(rows, nrow, i, 2000);
    for (;i<nrow &&rows[i].a <= 2000;i++) {
        if (rows[i].a == 2000&& rows[i].b>= 10 && rows[i].b < 50) {
            if (start_2 == 0) {
                start_2 = i;
            }

            count_2 ++;
        }
    }


    i = find_ab(rows, nrow, i, 3000);
    for (;i<nrow && rows[i].a <= 3000;i++) {
        if (rows[i].a == 3000&& rows[i].b>= 10 && rows[i].b < 50) {
            if (start_3 == 0) {
                start_3 = i;
            }
            count_3 ++;
        }
    }

    count = count_1 + count_2 + count_3;
    while (count_1 || count_2 || count_3) {
        Row min_row {INT32_MAX,INT32_MAX};
        bool e1 = false;
        bool e2 = false;
        bool e3 = false;

        if (count_1 != 0) {
            min_row = min_row < rows[start_1] ? min_row : rows[start_1];
            e1 = min_row == rows[start_1];
        }
        if (count_2 != 0) {
            min_row = min_row < rows[start_2] ? min_row : rows[start_2];
            e2 = min_row == rows[start_2];
            if (e2) {
                e1 = false;
            }
        }
        if (count_3 != 0) {
            min_row = min_row < rows[start_3] ? min_row : rows[start_3];
            e3 = min_row == rows[start_3];
            if (e3) {
                e1 = false;
                e2 = false;
            }
        }
        if (e1) {
            start_1 ++ ;
            count_1 --;
        }
        if (e2) {
            start_2 ++ ;
            count_2 --;
        }
        if (e3) {
            start_3 ++ ;
            count_3 --;
        }
#ifdef OUTPUT_PRINT
        std::cout << min_row.a << "," << min_row.b << "\n";
#endif
    }
    return count;
}


// is sort by ab, result as sort b
int task3_stl_sort(const Row* rows, int nrow) {
    auto count = 0;
    size_t i = 0;
    size_t count_1 = 0;
    size_t count_2 = 0;
    size_t count_3 = 0;
    std::vector<Row> sortOfB;
    sortOfB.reserve(1000);
    i = find_a(rows, nrow, i, 1000);
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b>= 10 && rows[i].b < 50) {

            sortOfB.push_back(rows[i]);
            count_1 ++;
        }
    }

    i = find_a(rows, nrow, i, 2000);
    for (;i<nrow &&rows[i].a <= 2000;i++) {
        if (rows[i].a == 2000&& rows[i].b>= 10 && rows[i].b < 50) {
            sortOfB.push_back(rows[i]);
            count_2 ++;
        }
    }


    i = find_a(rows, nrow, i, 3000);
    for (;i<nrow && rows[i].a <= 3000;i++) {
        if (rows[i].a == 3000&& rows[i].b>= 10 && rows[i].b < 50) {
            sortOfB.push_back(rows[i]);
            count_3 ++;
        }
    }
    std::sort(sortOfB.begin(), sortOfB.end(), 
        [](const Row& a, const Row&b) {
                return a.b < b.b;
            }
        );
    count = count_1 + count_2 + count_3;
#ifdef OUTPUT_PRINT
    for (auto& v : sortOfB) {
         std::cout << v.a << "," << v.b << "\n";
    }
#endif

    return count;
}

// is sort by ab, result as sort b
int task3b_stl_sort(const Row* rows, int nrow) {
    auto count = 0;
    size_t i = 0;
    size_t count_1 = 0;
    size_t count_2 = 0;
    size_t count_3 = 0;
    std::vector<Row> sortOfB;
    sortOfB.reserve(1000);
    i = find_ab(rows, nrow, i, 1000);
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b>= 10 && rows[i].b < 50) {

            sortOfB.push_back(rows[i]);
            count_1 ++;
        }
    }

    i = find_ab(rows, nrow, i, 2000);
    for (;i<nrow &&rows[i].a <= 2000;i++) {
        if (rows[i].a == 2000&& rows[i].b>= 10 && rows[i].b < 50) {
            sortOfB.push_back(rows[i]);
            count_2 ++;
        }
    }


    i = find_ab(rows, nrow, i, 3000);
    for (;i<nrow && rows[i].a <= 3000;i++) {
        if (rows[i].a == 3000&& rows[i].b>= 10 && rows[i].b < 50) {
            sortOfB.push_back(rows[i]);
            count_3 ++;
        }
    }
    std::sort(sortOfB.begin(), sortOfB.end(), 
        [](const Row& a, const Row&b) {
                return a.b < b.b;
            }
        );
    count = count_1 + count_2 + count_3;
#ifdef OUTPUT_PRINT
    for (auto& v : sortOfB) {
         std::cout << v.a << "," << v.b << "\n";
    }
#endif

    return count;
}


// 抄的
class fixed_thread_pool {
 public:
  fixed_thread_pool(size_t thread_count=5)
      : data_(std::make_shared<data>()) {
    for (size_t i = 0; i < thread_count; ++i) {
      std::thread([data = data_] {
        std::unique_lock<std::mutex> lk(data->mtx_);
        for (;;) {
          if (!data->tasks_.empty()) {
            auto current = std::move(data->tasks_.front());
            current();
            data->tasks_.pop();
          } else if (data->is_shutdown_) {
            break;
          } else {
            data->cond_.wait(lk);
          }
        }
      }).detach();
    }
  }

  ~fixed_thread_pool() {
    if ((bool) data_) {
      {
        std::lock_guard<std::mutex> lk(data_->mtx_);
        data_->is_shutdown_ = true;
      }
      data_->cond_.notify_all();
    }
  }

  template <class F>
  void execute(F&& task) {
    {
      std::lock_guard<std::mutex> lk(data_->mtx_);
      data_->tasks_.emplace(std::forward<F>(task));
    }
    data_->cond_.notify_one();
  }
  bool task_finish() {
    if (data_) {
      std::lock_guard<std::mutex> lk(data_->mtx_);
      return data_->tasks_.empty();
    } else {
      return true;
    } 
  }
 private:
  struct data {
    std::mutex mtx_;
    std::condition_variable cond_;
    bool is_shutdown_ = false;
    std::queue<std::function<void()>> tasks_;
  };
  std::shared_ptr<data> data_;
};


// is sort by a,b
// 线程池/std::vector没差别
int task2_mt(const Row* rows, int nrow, fixed_thread_pool *ths) {

    std::vector<int> count = {0,0,0};
    std::vector<size_t> i = {0,0,0};

    for (auto tn = 0; tn <3; tn++) {
        ths->execute([=, &count, &i](){
            size_t step = 0;
            auto loop = nrow;
            while (loop > 0) {
                step = loop / 2;
                if (rows[step].a < (tn+1)*1000){
                    i[tn] = step+1; 
                    loop -= step + 1; 
                } else {
                    loop = step;
                }
            }
            for (;i[tn]<nrow &&rows[i[tn]].a <= (tn+1)*1000;i[tn]++) {
                if (rows[i[tn]].a ==(tn+1)* 1000 && rows[i[tn]].b>= 10 && rows[i[tn]].b < 50) {
                    count[tn]++;
                }
            }
        });
    }

#ifdef OUTPUT_PRINT
        for (auto j=0; j< 3; j++) {
            auto cnt = 0;
            for (auto k = i[j]; k != 0 && cnt < count[k]; cnt++) {
                std::cout << rows[k-cnt].a << "," << rows[k - cnt].b << "\n";
            }
        }
#endif

       while (!ths->task_finish()) {
       }
   return count[0] + count[1] + count[2];
}