#ifndef EPOLLOOP_H
#define EPOLLOOP_H

#include "Epoll.hpp"
#include "Channel.hpp"
namespace Net{

    class Epolloop: public enable_shared_from_this<Epolloop>{
        private:
            std::shared_ptr<Epoll> epoll;
        public:
            void loop();
            Epolloop(std::shared_ptr<Epoll> epoll);
            //void addFd(Channel& Channel);
    };

}

#endif