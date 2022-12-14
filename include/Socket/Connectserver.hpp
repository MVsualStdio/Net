#ifndef CONNECTSERVER_H
#define CONNECTSERVER_H

#include <iostream>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include "../Logger/Logger.hpp"
#include "./ServerIO.hpp"
#include "./Channel.hpp"
#include "./Epoll.hpp"
#include "./Epolloop.hpp"
#include "Channel.hpp"
#include "../Buffer/Buffer.hpp"
#include "IMuduoUser.hpp"
namespace Net{
    class Tcpserver;
    class Connectserver : public ServerIO{
        #define MAX_LINE 1024
        public:
            explicit Connectserver(int fd,std::shared_ptr<Epolloop> eloop);
            ~Connectserver();
            virtual void serverRead();
            virtual void serverWrite();
            int getFd(){ return socketfd;}
            bool isClosed(){return isclosed;}
            void Closed();
            void Coninit();
            void setUser(IMuduoUser* _user){user = _user;}
            void connectEstablished();
        private:
            bool isclosed;
            int socketfd;
            std::shared_ptr<Epolloop> loop;
            Net::Channel* channel; 
            IMuduoUser* user;
            Buffer buffer;

    };
}

#endif