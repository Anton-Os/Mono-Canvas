#include <iostream>
#include <ctime>
#include <chrono>

int main(int argc, char** argv){
    for(int i = 0; i < 1000000000; i++);
    std::clock_t clock0 = clock();
    std::cout << "Current processor time: " << clock0 << std::endl; 
}