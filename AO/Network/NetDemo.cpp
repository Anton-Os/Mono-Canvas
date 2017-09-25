#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void asyncCallback2(const boost::system::error_code&, boost::asio::deadline_timer* timer, unsigned int* count){
    if(*count < 10){
        std::cout << "Numbers I hate: " << *count << std::endl;
        ++(*count);
        timer->expires_at(timer->expires_at() + boost::posix_time::seconds(1));
        timer->async_wait(boost::bind(asyncCallback2, boost::asio::placeholders::error, timer, count));
    }
}

void asyncCallback(const boost::system::error_code&){
    std::cout << "Melons and tuna dont mix" << std::endl;
}

int main(int argc, char** argv){
    boost::asio::io_service netIO;
    boost::asio::deadline_timer netDeadline(netIO, boost::posix_time::seconds(4));
    unsigned int count = 0;
    netDeadline.async_wait(boost::bind(asyncCallback2, boost::asio::placeholders::error, &netDeadline, &count));
    netIO.run();
    return 0;
}