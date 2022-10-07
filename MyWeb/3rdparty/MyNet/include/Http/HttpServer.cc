#include "HttpServer.hpp"



using namespace Net;

HttpServer::HttpServer(std::shared_ptr<Epolloop> loop):loop_(loop){
    tcp_ = std::make_shared<Tcpserver>(loop);
}

HttpServer::~HttpServer(){

}

void HttpServer::start(){
    tcp_->setUser(this);
    tcp_->Tcpinit();
}

void HttpServer::onConnection(Connectserver* pCon){

}

void HttpServer::onWriteComplate(Connectserver* pCon){

}

void HttpServer::onMessage(Connectserver* pCon, Buffer* pBuf){
    HttpContext context;
    // std::cout<<pBuf->peek()<<std::endl;
    if (!context.parseRequest(pBuf)){
        Buffer sendBuffer;
        int len = sendBuffer.writeConnect(pCon,"HTTP/1.1 400 Bad Request\r\n\r\n");
        pCon->serverClose();
    }

    if (context.gotAll()){
        onRequest(pCon, context.request());
        context.reset();
    }
    // std::cout<<std::this_thread::get_id()<<"    Http res"<<std::endl;
}

void HttpServer::onRequest(Connectserver* pCon, const HttpRequest& req){
    const std::string& connection = req.getHeader("Connection");
    bool close = connection == "close" ||
        (req.getVersion() == HttpRequest::kHttp10 && connection != "Keep-Alive");
    HttpResponse response(close);
    httpCallback_(req, &response);
    Buffer buf;
    response.toBuffer(&buf);
    buf.writeConnect(pCon);
    if (response.closeConnection()){
        pCon->serverClose();
    }
}

void HttpServer::loop(){
    loop_->loop();
}

