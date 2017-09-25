#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void asyncCallback2(const boost::system::error_code&, boost::asio::deadline_timer* timer, unsigned int* count){
    if(*count < 10)
    std::cout << "Numbers I hate: " << *count + 1 << std::endl;
}

void asyncCallback(const boost::system::error_code&){
    std::cout << "Melons and tuna dont mix" << std::endl;
}

int main(int argc, char** argv){
    boost::asio::io_service netIO;
    boost::asio::deadline_timer netDeadline(netIO, boost::posix_time::seconds(5));
    // netDeadline.wait();
    // std::cout << "America, an idea, not a place" << std::endl;
    netDeadline.async_wait(&asyncCallback);
    netIO.run();
    return 0;
}