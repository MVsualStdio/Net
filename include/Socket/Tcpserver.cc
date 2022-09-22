
#include "Tcpserver.hpp"

using namespace Net;

Tcpserver::Tcpserver(std::shared_ptr<Epoll> epoller):
    socketfd(createSocket()),epoll(epoller){
        channel = new Channel(socketfd);
    }


void Tcpserver::Tcpinit(){
        channel->setCallBack(shared_from_this());
        epoll_event ev;
        channel->setReEvent(EPOLLIN);
        epoll->addFd(channel);
}



Tcpserver::~Tcpserver(){
    delete(channel);
}



void Tcpserver::start(){
    // while(1){
    //     std::vector<std::shared_ptr<Net::Channel>> channel;


    // }
}

void Tcpserver::serverWrite(){
    std::cout<<"tcpwrite"<<std::endl;
}

void Tcpserver::serverRead(){
    sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    int client_len = sizeof(client_addr);
    int conn_fd = accept(socketfd, (sockaddr*)&client_addr, (socklen_t*)&client_len);
    if(conn_fd > 0) {
        LogDebug(Net::Logger::MESSAGE) << "New Connection from: ["
                    << inet_ntoa(client_addr.sin_addr) << ':'
                    << ntohs(client_addr.sin_port) <<']'
                    << " accepted, Socket ID: "
                    << conn_fd;
                    
    } else {
        LogDebug(Net::Logger::MESSAGE) <<  "accept error, errno" << errno;
    }
    fcntl(conn_fd, F_SETFL, O_NONBLOCK);
    conList[conn_fd] = std::shared_ptr<Connectserver>(new Connectserver(conn_fd,epoll));
    conList[conn_fd]->Coninit();
}


int Tcpserver::createSocket(){
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd == -1){
        LogDebug(Net::Logger::WARN) << "socket create error";
    }
    fcntl(socketfd,F_SETFL,O_NONBLOCK);
    int opt = 1;
    setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(LISTEN_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(socketfd,(sockaddr*)&server_addr,sizeof(server_addr));
    if(ret == -1){
        LogDebug(Net::Logger::WARN) << "socket bind error";
    }
    ret = listen(socketfd,MAX_LISTEN_FD);
    if( ret == -1){
        LogDebug(Net::Logger::WARN) << "socket listen error";
    }
    return socketfd;
}