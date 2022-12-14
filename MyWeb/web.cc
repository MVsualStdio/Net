#include "Response.hpp"
// #include "Http/HttpServer.hpp"
// #include "Socket/Epolloop.hpp"
#include "Route.hpp"
#include "Render.hpp"
#include "WebServer.hpp"
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

std::shared_ptr<HttpResponse> login(HttpRequest& req){
    if(req.method() == HttpRequest::Method::kPost & req.postBody() == "u=4&p=4"){
        std::cout<<"req:"<<req.postBody()<<std::endl;
        // std::shared_ptr<HttpResponse> rsp(new HttpResponse(true));
        return Render::sendRedirect("/welcome.html");
    }
    return Render::SendHtml("/login.html");
}




int main(){
    WebSever web;
    web.addRoute("/",Response(login));
    web.addRoute("/ppp0",Response([](HttpRequest& resp){return Render::SendContent("/login.html");}));
    web.addRoute("/welcome",Response([](HttpRequest& resp){return Render::SendHtml("/welcome.html");}));
    web.start();
}