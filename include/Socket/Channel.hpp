#ifndef CHANNEL_H
#define CHANNEL_H

#include<memory>
#include<utility>
#include <sys/epoll.h>
#include "ServerIO.hpp"  

namespace Net{
    class Channel{ 
        public:
            Channel(int socket);
            ~Channel() = default;
            void setEvent(uint32_t event);
            void setReEvent(uint32_t reevent);
            void ChannelCallback();
            void setCallBack(std::shared_ptr<ServerIO> serverio);
            int getFd() const;
            uint32_t getEvent()const;
            uint32_t getReEvent()const;
        private:
            uint32_t reevent;
            uint32_t event;
            std::shared_ptr<ServerIO> serverio;
            int socket_fd;
    };
} // namespace Net

#endif