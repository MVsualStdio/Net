#ifndef RENDER_H
#define RENDER_H
#include <unordered_map>
#include "Http/HttpResponse.hpp"
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
            static void setResp(Net::HttpResponse* resp);
        public:
            static const unordered_map<string, string> SUFFIX_TYPE;
            static const map<Net::HttpResponse::HttpStatusCode, string> ERROR_ACCESS_PATH;
            Render() = default;
            static void SendHtml(string path,Net::HttpResponse* resp_);
           
    };
}



#endif
