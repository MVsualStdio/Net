#include "Connectserver.hpp"

using namespace Net;


Connectserver::Connectserver(int fd,std::shared_ptr<Epoll> epoller):
    socketfd(fd){
        epoll = epoller;
        isclosed = false;
        channel = new Channel(socketfd);

}

void Connectserver::Coninit(){
        channel->setCallBack(shared_from_this());
        epoll_event ev;
        channel->setEvent(EPOLLIN);
        epoll->addFd(channel);
}

Connectserver::~Connectserver(){
    
    delete(channel);
}

void Connectserver::Closed(){
    close(socketfd);
    isclosed = true;
}

void Connectserver::serverWrite(){
    const char *s = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html;charset=utf-8\r\n"
                    "Content-Length: 158\r\n" 
                    "Connection: closed\r\n"
                    "\r\n"
                    "<html>"
                    "<head>"
                    "</head>"
                    "<body> "
                    "<h1>Hello</h1>"
                    "</body>"
                    "</html>";
    buffer.clean();
    buffer.writeBuffer(s,strlen(s));
    buffer.writeConnect(this);  
    Closed();
}

void Connectserver::serverRead(){
    int length = buffer.readConnect(this);
    if(length){
        channel->setEvent(EPOLLIN | EPOLLOUT);
        epoll->modFd(channel);
    }   
    else{
        Closed();
    }
}