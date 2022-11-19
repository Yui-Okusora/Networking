#include <iostream>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

int main(int argc, const char** argv) {

    asio::error_code ec;

    asio::io_context context;

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("https://www.facebook.com/",ec),443);

    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint,ec);

    if(!ec){
        std::cout<<"Connected!"<<std::endl;
    }else{
        std::cout<<"Failed to connect to address:\n"<<ec.message()<<std::endl;
    }

    system("pause");
    return 0;
}