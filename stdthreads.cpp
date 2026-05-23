//threads: allows multiple functions to run concurrently
#include <iostream>
#include <thread>
#include <chrono>

void foo(){
    //simulates task that finishes in 1sec
    std::cout << "foo start" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "foo ends" << std::endl;
}

void bar(){
    std::cout<< "bar start" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "bar ends" << std::endl;
}

void independentThread(){
    std::cout << "starting concurrent thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "exiting concurrent thread" << std::endl;
}

void threadCaller(){
    std::cout << "starting thread caller" << std::endl;
    std::thread t(independentThread);
    t.detach(); //.detach to permit exection of thread independently from thread object
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Exiting thread caller" << std::endl;
}

int main(){
    std::cout << "starting first worker" << std::endl;
    std::thread worker1(foo);  //workers stars running in background as soon as init.
    
    std::cout << "starting second helper" << std::endl;
    std::thread worker2(bar);
    
    std::cout << "waiting for workers to finish" << std::endl;
    
    worker1.join(); // .join to wait so Main thread waits for this thread to finish b4 terminate
    worker2.join();
    
    threadCaller();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    std::cout << "done!" << std::endl;
    std::cout << std::thread::hardware_concurrency() << std::endl;
    return 0;
}