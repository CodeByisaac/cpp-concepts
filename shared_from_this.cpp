
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

class Test :
    public std::enable_shared_from_this<Test>
{
public:
    ~Test(){ std::cout << "destroyed" << std::endl;}
    
    void start(){
        //auto self = shared_from_this();
        std::thread([this](){
            std::this_thread::sleep_for(std::chrono::seconds(2));
            
            std::cout << "thread finished" << std::endl;
            }).detach();    
    }
};

int main()
{
  auto obj = std::make_shared<Test>();
  obj->start();
  obj.reset();
  
  std::cout << "main released ownership\n";
  
  std::this_thread::sleep_for(std::chrono::seconds(3));
  
  return 0;
    
}