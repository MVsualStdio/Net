#include "Socket/Epoll.hpp"
#include "Socket/Epolloop.hpp"
#include "Socket/Tcpserver.hpp"


int main() {
    std::shared_ptr<Net::Epoll> epoll(new Net::Epoll());
    
    std::shared_ptr<Net::Tcpserver> server(new Net::Tcpserver(epoll));
    server->Tcpinit();
    Net::Epolloop loop(epoll);
    loop.loop();
    return 0;
}