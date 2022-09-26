

#include "Epolloop.hpp"

using namespace Net;

Epolloop::Epolloop(){
    epoll = std::make_shared<Epoll>();
}

void Epolloop::loop(){
    while(1){
        std::vector<Net::Channel*> channels;
        epoll->wait(channels);
        for(auto c : channels){
            shared_ptr<Net::WorkItem> work = static_cast<shared_ptr<WorkItem>>(new Task(&Channel::ChannelCallback,c));
            ThreadPool::instance()->addTask(std::move(work));
        }
    }
}

void Epolloop::update(Channel* channel){
    epoll->update(channel);
}

// void Epolloop::addFd(Channel& channel){
//     epoll.addFd(channel);
// }