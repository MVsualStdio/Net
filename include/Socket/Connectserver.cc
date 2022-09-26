#include "Connectserver.hpp"


using namespace Net;


Connectserver::Connectserver(int fd,std::shared_ptr<Epolloop> eloop):
    socketfd(fd){
        loop = eloop;
        isclosed = false;
        channel = new Channel(loop,socketfd);

}

void Connectserver::connectEstablished(){
    if(user){
        user->onConnection(this);
    }
}



void Connectserver::Coninit(){
        channel->setCallBack(shared_from_this());
        channel->enableReading();
}

Connectserver::~Connectserver(){
    
    delete(channel);
}

void Connectserver::Closed(){
    close(socketfd);
    isclosed = true;
}

void Connectserver::serverWrite(){
    // const char *s = "HTTP/1.1 200 OK\r\n"
    //                 "Content-Type: text/html;charset=utf-8\r\n"
    //                 "Content-Length: 158\r\n" 
    //                 "Connection: closed\r\n"
    //                 "\r\n"
    //                 "<html>"
    //                 "<head>"
    //                 "</head>"
    //                 "<body> "
    //                 "<h1>Hello</h1>"
    //                 "</body>"
    //                 "</html>";
    // buffer.clean();
    //buffer.writeBuffer(s,strlen(s));
    buffer.writeConnect(this);  
    channel->disableWriting();
}

void Connectserver::serverRead(){
    int length = buffer.readConnect(this);
    if(length){
        if(user){
            user->onMessage(this,&buffer);
        }
    }   
    else{
        Closed();
    }
}