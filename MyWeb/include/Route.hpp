#ifndef ROUTE_H
#define ROUTE_H

#include <unordered_map>
#include <string>
#include <algorithm>
#include <functional>
#include "Response.hpp"
#include "Http/HttpResponse.hpp"
using namespace std;

namespace web{
    class Route{
        public:
        private:
            static unordered_map<string,Response> route_;
            static void addStaticSource(string dir);
            static bool getAllFiles(const std::string& dir_in, std::vector<std::string>& files);
        public:
            Route();
            static void addRoute(string oneRoute,Response res);
            static bool isExistRoute(string oneRoute);
            static Response getResponse(string path);
    };
}


#endif