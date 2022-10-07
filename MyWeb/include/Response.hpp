#ifndef RESPONSE_H
#define RESPONSE_H
#include <unordered_map>
#include "Http/HttpResponse.hpp"
using namespace std;


namespace web{
    class Response{
        public:
            using ResponseCallBack = std::function<void (Net::HttpResponse*)>;
        private:
            ResponseCallBack callback_;
        public:
            Response() = default;
            Response(ResponseCallBack callback):callback_(callback){};
            void ResRun(Net::HttpResponse* rsp){
                callback_(rsp);
            }
    };
}



#endif
