#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Response.hpp"
#include "Http/HttpServer.hpp"
#include "Socket/Epolloop.hpp"
#include "Route.hpp"
#include <iostream>
#include <map>
#include <fstream>
#include <sys/mman.h>
#include <fcntl.h>
#include <regex>
using namespace std;
using namespace Net;


namespace web{
    class WebSever{
        public:
        private:
            std::shared_ptr<Net::HttpResponse> onRequest(const HttpRequest& req){
                //std::cout << "Headers " << req.methodString() << " " << req.path() << std::endl;
                string path = req.path();
                if(Route::isExistRoute(path)){
                    Response s =  Route::getResponse(path);
                    const std::string& connection = req.getHeader("Connection");
                    bool close = connection == "close" ||
                        (req.getVersion() == HttpRequest::kHttp10 && connection != "Keep-Alive");
                    std::shared_ptr<Net::HttpResponse> Newresp =  s.ResRun(req);
                    Newresp->setCloseConnect(close);
                    return Newresp;
                }
                return nullptr;
            }
        public:
            WebSever() = default;
            void start(){
                std::shared_ptr<Net::Epolloop> loop(new Net::Epolloop());
                Net::HttpServer server(loop);
                server.setHttpCallback(std::bind(&WebSever::onRequest,this,std::placeholders::_1));
                server.start();
                server.loop();
            }
            void addRoute(string path, Response res){
                Route::addRoute(path,res);
            }
    };
}

#endif