#include "HttpContext.hpp"

using namespace Net;

bool HttpContext::processRequestLine(const char* begin, const char* end){
    bool succed = false;
    const char* start = begin;
    const char* space = std::find(start,end,' ');
   
    if(space!=end && request_.setMethod(start,space)){
        start = space+1;
        space = std::find(start,end,' ');
        if(space!=end){
            const char* question = std::find(start, space, '?');
            if(question!=space){
                request_.setPath(start,question);
                request_.setQuery(question,space);
            }
            else{
                request_.setPath(start,space);
            }
            start = space+1;
            
            succed = (end-start == 8) && std::equal(start, end-1, "HTTP/1.");
            if(succed){
                if(*(end-1) == '1'){
                    request_.setVersion(HttpRequest::Version::kHttp11);
                }
                else if((*end-1) == '0'){
                    request_.setVersion(HttpRequest::Version::kHttp10);
                }
                else{
                    succed = false;
                }
            }
        }
    }
    return succed;
}


bool HttpContext::parseRequest(Buffer* buf){
    bool ok = true;
    bool hasMore = true;
    while(hasMore){
        if(state_ == kExpectRequestLine){
            const char* crlf = buf->findCRLF();
            if(crlf){
                ok = processRequestLine(buf->peek(), crlf);
                if(ok){
                    buf->retrieveUntil(crlf+2);
                    state_ = kExpectHeaders;
                }
                else{
                    hasMore = false;
                }
            }
            else{
                hasMore = false;
            }
        }
        else if(state_ = kExpectHeaders){
            const char* crlf = buf->findCRLF();
            if(crlf){
                // std::cout<<std::string(buf->peek(),crlf);
                const char* colon = std::find(buf->peek(), crlf, ':');
                if(colon != crlf){
                    request_.addHeader(buf->peek(),colon,crlf);
                }
                else{
                    state_ = kGotAll;
                    hasMore = false;
                }
                buf->retrieveUntil(crlf + 2);
            }
            else{
                hasMore = false;
            }
        }
        else if(state_ == kExpectBody){

        }
    }
    return ok;
}