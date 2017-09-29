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
        if(argc != 2) return -1;
        boost::asio::io_service netIO;
        boost::asio::ip::tcp::resolver netResolver(netIO);
        boost::asio::ip::tcp::resolver::query resolverQuery(argv[1], "daytime");
        boost::asio::ip::tcp::resolver::iterator resolverEndItr = netResolver.resolve(resolverQuery);
        boost::asio::ip::tcp::socket tcpSocket(netIO);
        boost::asio::connect(tcpSocket, resolverEndItr);
        while(true){
            char cliBuffer[128];
            boost::system::error_code error;
            size_t cliBufferLen = tcpSocket.read_some(boost::asio::buffer(cliBuffer), error);
            if(error == boost::asio::error::eof) break;
            else if(error) throw boost::system::system_error(error);
            std::cout.write(cliBuffer, cliBufferLen);
        }
    } catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}