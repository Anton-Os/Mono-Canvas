#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>

int main(int argc, char** argv){
    boost::asio::io_service netIO;
    boost::asio::deadline_timer netDeadline(netIO, boost::posix_time::seconds(5));
    netDeadline.wait();
    std::cout << "Hello Boost" << std::endl;
    return 0;
}