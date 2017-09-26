#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void asyncCallback(const boost::system::error_code&, boost::asio::deadline_timer* timer, unsigned int* count){
    if(*count < 15){
        std::cout << "Numbers I hate: " << *count << std::endl;
        ++(*count);
        timer->expires_at(timer->expires_at() + boost::posix_time::milliseconds(1000));
        timer->async_wait(boost::bind(asyncCallback, boost::asio::placeholders::error, timer, count));
    }
}

/* void asyncCallback(const boost::system::error_code&){
    std::cout << "Melons and tuna dont mix" << std::endl;
} */

int main(int argc, char** argv){
    try {
        boost::asio::io_service netIO;
        boost::asio::deadline_timer netDeadline(netIO, boost::posix_time::seconds(4));
        unsigned int count = 0;
        // netDeadline.async_wait(boost::bind(asyncCallback, boost::asio::placeholders::error, &netDeadline, &count));
        boost::asio::ip::tcp::resolver tcpResolver(netIO);
        boost::asio::ip::tcp::resolver::query tcpResolverQuery(argv[1], "daytime");
        boost::asio::ip::tcp::resolver::iterator endPt_It = tcpResolver.resolve(tcpResolverQuery);
        boost::asio::ip::tcp::socket ioSocket(netIO);
        boost::asio::connect(ioSocket, endPt_It);
        while(true){
            char clientBuffer[300];
            boost::system::error_code error;

            size_t dataLen = ioSocket.read_some(boost::asio::buffer(clientBuffer), error);

            if(error == boost::asio::error::eof) break;
            else if(error) throw boost::system::system_error(error);

            std::cout.write(clientBuffer, dataLen);
        } 
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}