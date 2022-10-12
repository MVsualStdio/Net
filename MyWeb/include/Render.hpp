#ifndef RENDER_H
#define RENDER_H
#include <unordered_map>
#include "Http/HttpResponse.hpp"
#include <memory>
using namespace std;


namespace web{
    class Render{
        private:
            static string path_;
            static string pathType_;
            static int filefd_;
            static char* buffer_;
            static size_t pathLen_;
            
        private:
            static void UnmapFile();
            static int mmapFile(string file);
            static void getPath(string& path);
            static void setResp(std::shared_ptr<Net::HttpResponse> resp);
        public:
            static const unordered_map<string, string> SUFFIX_TYPE;
            static const map<Net::HttpResponse::HttpStatusCode, string> ERROR_ACCESS_PATH;
            Render() = default;
            static std::shared_ptr<Net::HttpResponse> SendHtml(string path);
           
    };
}



#endif
