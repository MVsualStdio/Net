

#include "Epolloop.hpp"

using namespace Net;

Epolloop::Epolloop(std::shared_ptr<Epoll> epoller){
    epoll = epoller;
}

void Epolloop::loop(){
    while(1){
        std::vector<Net::Channel*> channels;
        epoll->wait(channels);
        for(auto c : channels){
            c->ChannelCallback();
        }
    }
}

// void Epolloop::addFd(Channel& channel){
//     epoll.addFd(channel);
// }