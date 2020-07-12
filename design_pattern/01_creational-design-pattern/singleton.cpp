#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

// command to execute 
//g++ -std=c++17 -pthread singleton.cpp

class Singleton
{
    Singleton(const string& value):value_(value){
    }
    static Singleton * instance_; 
    std::string value_;    
    static std::mutex mutex_;
  public:
    Singleton(const Singleton& rhs) = delete;
    Singleton& operator = (const Singleton& rhs) = delete;
    
    static Singleton * getInstance(const string& value){
        std::lock_guard<std::mutex> lock(mutex_);
        if(!instance_) {
            instance_ = new Singleton(value);
        }
        return instance_;
    }
    ~Singleton(){
        if(!instance_) 
            delete instance_;
    }
    string getValue() const{
        return value_;
    }
    
};
Singleton* Singleton::instance_ = nullptr;
std::mutex Singleton::mutex_;

void thread_1(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << endl << Singleton::getInstance("First")->getValue().c_str();
}
void thread_2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout <<endl << Singleton::getInstance("Second")->getValue().c_str();
}
int main()
{
    std::thread t1(thread_1);
    std::thread t2(thread_2);
    t1.join();
    t2.join();

    return 0;
}