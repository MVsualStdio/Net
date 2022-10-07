#include "../include/Render.hpp"
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

using namespace Net;
using namespace web;

extern char favicon[555];
bool benchmark = true;


const unordered_map<string, string> web::Render::SUFFIX_TYPE = {
    { ".html",  "text/html" },
    { ".xml",   "text/xml" },
    { ".xhtml", "application/xhtml+xml" },
    { ".txt",   "text/plain" },
    { ".rtf",   "application/rtf" },
    { ".pdf",   "application/pdf" },
    { ".word",  "application/nsword" },
    { ".png",   "image/png" },
    { ".gif",   "image/gif" },
    { ".jpg",   "image/jpeg" },
    { ".jpeg",  "image/jpeg" },
    { ".au",    "audio/basic" },
    { ".mpeg",  "video/mpeg" },
    { ".mpg",   "video/mpeg" },
    { ".avi",   "video/x-msvideo" },
    { ".gz",    "application/x-gzip" },
    { ".tar",   "application/x-tar" },
    { ".css",   "text/css"},
    { ".js",    "text/javascript"},
};


const map<Net::HttpResponse::HttpStatusCode, string> web::Render::ERROR_ACCESS_PATH = {
    {Net::HttpResponse::K404NotFound,"./static/html/404.html"}
};

string web::Render::path_;
string web::Render::pathType_;
int web::Render::filefd_;
char* web::Render::buffer_ = nullptr;
size_t web::Render::pathLen_ = 0;




void Render::SendHtml(string path,Net::HttpResponse* resp){
    path_ = path;
    auto pos = path_.find('.');
    if(pos != path_.length()){
        std::string suffix(path_.begin()+pos,path_.end());
        auto iter = SUFFIX_TYPE.find(suffix);
        if(iter != SUFFIX_TYPE.end()){
            pathType_ = iter->second;
        }
    }
    if(buffer_){
        UnmapFile();
    }
    string openPath ;
    getPath(openPath);
    filefd_ = mmapFile(openPath);
    setResp(resp);
    close(filefd_);
    UnmapFile();
}

void Render::UnmapFile() {
    if(buffer_) {
        munmap(buffer_, pathLen_);
        buffer_ = nullptr;
    }
}

int Render::mmapFile(string file){
        int fd = open(file.c_str(), O_RDONLY);
        if(fd>0){
            pathLen_ = lseek(fd, 0, SEEK_END);
            //  建立映射
            buffer_ = (char *) mmap(NULL, pathLen_, PROT_READ, MAP_PRIVATE, fd, 0);
        }
        else{
            fd = open("./static/html/404.html", O_RDONLY);
            pathLen_ = lseek(fd, 0, SEEK_END);
            //  建立映射
            buffer_ = (char *) mmap(NULL, pathLen_, PROT_READ, MAP_PRIVATE, fd, 0);
        }
        return fd;
}


void Render::getPath(string& path){
    
    if(pathType_ == "text/html"){
        path = "./static/html/"+path_;
    }
    
    else if(pathType_ == "text/css"){
        path = "./static/css/"+path_;
    }

    else if(pathType_ == "text/javascript"){
        path = "./static/js/"+path_;
    }
}

void Render::setResp(Net::HttpResponse* resp){
    if(filefd_>0){
        resp->setStatusCode(HttpResponse::K200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType(pathType_);
        resp->setBody(buffer_);
    }
    else{
        resp->setStatusCode(HttpResponse::K404NotFound);
        resp->setStatusMessage("Bad Request");
        resp->setContentType("text/html");
        resp->setBody(buffer_);
    }
}