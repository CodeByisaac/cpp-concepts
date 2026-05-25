//std::mutex : synchronization primitive that protects shared data from being simultaneously accessed by mutiple threads.
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int x = 0;
std::mutex x_mutex; //every access to data must use the same mutex

void slow_increment(int id){
  for (int i = 0; i < 3; i++){
    x_mutex.lock();  //makes other threads wait till unlock
    ++x;
    std::cout << "id:" << id << ", xcount: " << x << std::endl; //mutex also syncronizes the output
    x_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(4));
  }
  
}

int main () {
  
  std::thread t1{slow_increment, 0};
  std::thread t2{slow_increment, 1};
  
  t1.join();
  t2.join();
  
  std::cout << "Done!" << std::endl;
  return 0;
};