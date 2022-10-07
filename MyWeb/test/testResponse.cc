#include "../include/Response.hpp"
// #include "Http/HttpServer.hpp"
// #include "Socket/Epolloop.hpp"
#include "../include/Route.hpp"
#include "../include/Render.hpp"
#include "../include/WebServer.hpp"
#include <iostream>
#include <map>
#include <fstream>
#include <sys/mman.h>
#include <fcntl.h>
#include <regex>
using namespace web;
using namespace std;
using namespace Net;


// void onRequest(const HttpRequest& req, HttpResponse* resp){
//     std::cout << "Headers " << req.methodString() << " " << req.path() << std::endl;
//     string path = req.path();
//     // cout<<req.postBody()<<endl;
//     if(Route::isExistRoute(path)){
//         Response s =  Route::getResponse(path);
//         s.ResRun(resp);
//     }
// }

int main(){

    WebSever web;
    web.addRoute("/",Response([](HttpResponse* resp){Render::SendHtml("login.html",resp);}));
    web.start();
}