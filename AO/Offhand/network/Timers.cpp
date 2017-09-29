#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void asyncCallback2(const boost::system::error_code&, boost::asio::deadline_timer* timer, unsigned int* count){
    if(*count < 15){
        std::cout << "Numbers I hate: " << *count << std::endl;
        ++(*count);
        timer->expires_at(timer->expires_at() + boost::posix_time::milliseconds(1000));
        timer->async_wait(boost::bind(asyncCallback2, boost::asio::placeholders::error, timer, count));
    }
}

void asyncCallback1(const boost::system::error_code&){
    std::cout << "Melons and tuna dont mix" << std::endl;
}

int main(int argc, char** argv){
    boost::asio::io_service netIO;
    boost::asio::io_service netIO2;
    boost::asio::deadline_timer deadlineTimer(netIO);
    deadlineTimer.expires_from_now(boost::posix_time::milliseconds(5000));
    deadlineTimer.async_wait(asyncCallback1);
    boost::asio::deadline_timer deadlineTimer2(netIO);
    deadlineTimer2.expires_from_now(boost::posix_time::milliseconds(5000));
    deadlineTimer2.async_wait(asyncCallback1);
    netIO.run();
    boost::system::error_code errorAdr;
    return 0;
}