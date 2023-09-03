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
        rows[i].b = i  % 60;
        // 映射10000
        int mod = nrow / 10000;
        rows[i].a =  i  / mod;
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

// is sort by a,b
// 二分找到上下界，判断是否满足10<=x<50
int task2(const Row* rows, int nrow) {
    auto loop = nrow;
    auto count = 0;
    size_t i = 0;
    size_t step = 0;
    while (loop > 0) {
        step = loop / 2;
        if (rows[step].a < 1000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b>= 10 && rows[i].b < 50) {

#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif

            count++;
        }
    }
    loop = nrow;
    while (loop > 0) {
        step = (i + loop) / 2;
        if (rows[step].a < 2000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
    for (;i<nrow &&rows[i].a <= 2000;i++) {
        if (rows[i].a == 2000 && rows[i].b>= 10 && rows[i].b < 50) {
            
#ifdef OUTPUT_PRINT
            std::cout << rows[i].a << "," << rows[i].b << "\n";
#endif
            count++;
        }
    }
    loop = nrow;
    while (loop > 0) {
        step = (i + loop) / 2;
        if (rows[step].a < 3000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
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



// is sort by ab, result as sort b
// bucket
int task3(const Row* rows, int nrow) {
    auto loop = nrow;
    auto count = 0;
    size_t i = 0;
    size_t step = 0;
    size_t start_1 = 0;
    size_t count_1 = 0;
    size_t start_2 = 0;
    size_t count_2 = 0;
    size_t count_3 = 0;
    size_t start_3 = 0;
    while (loop > 0) {
        step = loop / 2;
        if (rows[step].a < 1000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b>= 10 && rows[i].b < 50) {
            if (start_1 == 0) {
                start_1 = i;
            }
            
            count_1 ++;
        }
    }

    loop = nrow;
    while (loop > 0) {
        step = (loop + i) / 2;
        if (rows[step].a < 2000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
    for (;i<nrow &&rows[i].a <= 2000;i++) {
        if (rows[i].a == 2000&& rows[i].b>= 10 && rows[i].b < 50) {
            if (start_2 == 0) {
                start_2 = i;
            }

            count_2 ++;
        }
    }


    loop = nrow;
    while (loop > 0) {
        step = (loop + i) / 2;
        if (rows[step].a < 3000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
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
        #undef MIN
        #define MIN(x, y) (x.b < y.b || (x.b== y.b &&x.a < y.a) ? x:y)
        #undef EQ
        #define EQ(x ,y) (x.a == y.a && x.b == y.b)
        if (count_1 != 0) {
            min_row = MIN(min_row, rows[start_1]);
            e1 = EQ(min_row,rows[start_1]);
        }
        if (count_2 != 0) {
            min_row = MIN(min_row, rows[start_2]);
            e2 = EQ(min_row,rows[start_2]);
            if (e2) {
                e1 = false;
            }
        }
        if (count_3 != 0) {
            min_row = MIN(min_row, rows[start_3]);
            e3 = EQ(min_row,rows[start_3]);
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
    auto loop = nrow;
    auto count = 0;
    size_t i = 0;
    size_t step = 0;
    size_t count_1 = 0;
    size_t count_2 = 0;
    size_t count_3 = 0;
    std::vector<Row> sortOfB;
    sortOfB.reserve(1000);
    while (loop > 0) {
        step = loop / 2;
        if (rows[step].a < 1000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
    for (;i<nrow &&rows[i].a <= 1000;i++) {
        if (rows[i].a == 1000 && rows[i].b>= 10 && rows[i].b < 50) {

            sortOfB.push_back(rows[i]);
            count_1 ++;
        }
    }

    loop = nrow;
    while (loop > 0) {
        step = (loop + i) / 2;
        if (rows[step].a < 2000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
    for (;i<nrow &&rows[i].a <= 2000;i++) {
        if (rows[i].a == 2000&& rows[i].b>= 10 && rows[i].b < 50) {
            sortOfB.push_back(rows[i]);
            count_2 ++;
        }
    }


    loop = nrow;
    while (loop > 0) {
        step = (loop + i) / 2;
        if (rows[step].a < 3000){
            i = step+1; 
            loop -= step + 1; 
        } else {
            loop = step;
        }
    }
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