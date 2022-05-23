#include "Crawler.h"

Crawler::Crawler(): ref_count(0), start(clock()), end(-1) {}

string Crawler::make_string(const string & ref)
{
    lock_guard<mutex> lock(crawlerMutex);
    ifstream file; file.open(dir+ref+".html");
    string temp; string s;
    file >> temp; s += temp;
    while (!file.eof()) {file >> temp; s += " " + temp;}
    return s;
}

bool Crawler::crawled(const string & ref)
{
    lock_guard<mutex> lock(crawlerMutex);
    if (crawled_files.find(ref) != crawled_files.end())
        return true;
    return false;
}

void Crawler::start_crawler(int threads_amount)
{
    for (int i = 0; i < threads_amount; ++i)
    {
        threads.emplace_back(&Crawler::crawl, this);
    }
    for (int i = 0; i < threads_amount; ++i)
    {
        threads[i].join();
    }
    cout << "References: "<< ref_count << endl;
    end = clock();
    cout << "Time: " << (end - start) << " clocks";
}

void Crawler::crawl()
{
    while (true)
    {
        if (!queue.empty())
        {
            ++working_threads;
            string ref;
            {
                lock_guard<mutex> lock(crawlerMutex);
                if (queue.empty())
                {
                    --working_threads;
                    continue;
                }
                ref = move(queue.extract(queue.begin()).value());
            }
            if (crawled(ref))
            {
                --working_threads;
                continue;
            }
            string s = make_string(ref);
            {
                lock_guard<mutex> lock(crawlerMutex);
                ofstream output(dir1+ref+".html");
                output << s;
                output.close();
            }
            size_t found = 0;
            string reference;
            while (true) {
                found = s.find("<a href", found);
                if (found == -1)
                    break;
                while (s[found + SHIFT_VALUE] != '.')
                {
                    reference += s[(found++) + SHIFT_VALUE];
                }
                if (!crawled(reference))
                {
                    lock_guard<mutex> lock(crawlerMutex);
                    queue.insert(reference);
                }
                reference = "";
            }
            if (!crawled(ref))
            {
                lock_guard<mutex> lock(crawlerMutex);
                ref_count++;
                crawled_files.insert(ref);
            }
            --working_threads;
        }
        if (working_threads == 0 && queue.empty())
        {
            lock_guard<mutex> lock(crawlerMutex);
            cout << "thread has finished working in " << (clock() - start)<< " clocks\n";
            break;
        }
    }
}