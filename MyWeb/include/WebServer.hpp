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
            void onRequest(const HttpRequest& req, HttpResponse* resp){
                string path = req.path();
                if(Route::isExistRoute(path)){
                    Response s =  Route::getResponse(path);
                    s.ResRun(resp);
                }
            }
        public:
            WebSever() = default;
            void start(){
                std::shared_ptr<Net::Epolloop> loop(new Net::Epolloop());
                Net::HttpServer server(loop);
                server.setHttpCallback(std::bind(&WebSever::onRequest,this,std::placeholders::_1,std::placeholders::_2));
                server.start();
                server.loop();
            }
            void addRoute(string path, Response res){
                Route::addRoute(path,res);
            }
    };
}

#endif