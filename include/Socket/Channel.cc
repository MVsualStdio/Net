
#include "Channel.hpp"


using namespace Net;

Channel::Channel(int socket){
    
    event = 0;
    socket_fd =  socket;
}

void Channel::setEvent(uint32_t epoll_event){
    event = epoll_event;
}

void Channel::setReEvent(uint32_t epoll_event){
    reevent = epoll_event;
}


void Channel::setCallBack(std::shared_ptr<ServerIO> serverio){
    this->serverio = serverio;
}

void Channel::ChannelCallback(){
    if(event & EPOLLIN){
        serverio->serverRead();
    }
    if(event & EPOLLOUT){
        serverio->serverWrite();
    }
    if(event & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)){
        //serverio->serverClose();
    }
}


int Channel::getFd() const {
    return socket_fd;
}

uint32_t Channel::getEvent() const {
    return event;
}

uint32_t Channel::getReEvent() const {
    return reevent;
}