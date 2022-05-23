#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include "mingw.thread.h"
#include "mingw.mutex.h"
#include "mingw.condition_variable.h"
#define SHIFT_VALUE 16

using namespace std;

class Crawler {
    atomic<int> ref_count = 0;
    int start; int end;
    string dir = "C:\\Users\\romag\\CLionProjects\\OOP5\\test_data\\";
    string dir1 = "C:\\Users\\romag\\CLionProjects\\OOP5\\copied_data\\";
    unordered_set<string> crawled_files;
    unordered_set<string> queue = {"0"};
    atomic<int> working_threads = 0;
    vector<thread> threads;
    mutex crawlerMutex;

public:
    Crawler();

    string make_string(const string & ref);
    bool crawled(const string & ref);
    void start_crawler(int threads_amount);
    void crawl();

    ~Crawler() = default;
};

