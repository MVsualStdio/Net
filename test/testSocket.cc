#include "Socket/Epolloop.hpp"
#include "Socket/Tcpserver.hpp"
#include "Socket/IMuduoUser.hpp"
#include "Socket/Connectserver.hpp"

class Http:public Net::IMuduoUser{
    void onConnection(Net::Connectserver* pCon){
        
    };
    void onMessage(Net::Connectserver* pCon, Net::Buffer* pBuf){
            std::string s = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html;charset=utf-8\r\n"
                    "Content-Length: 158\r\n" 
                    "Connection: closed\r\n"
                    "\r\n"
                    "<html>"
                    "<head>"
                    "</head>"
                    "<body> "
                    "<h1>Hello</h1>"
                    "</body>"
                    "</html>";
        pBuf->clean();
        pBuf->append("HTTP/1.1 200 OK\r\n");
        pBuf->append("Content-Type");
        pBuf->append(":");
        pBuf->append("text/html;charset=utf-8\r\n");
        pBuf->append("Content-Length: 158\r\n" 
                    "Connection: closed\r\n"
                    "\r\n"
                    "<html>"
                    "<head>"
                    "</head>"
                    "<body> "
                    "<h1>Hello</h1>"
                    "</body>"
                    "</html>");
        pBuf->writeConnect(pCon);  
        pCon->Closed();
    }
    void onWriteComplate(Net::Connectserver* pCon){

    };
};


int main() {
    Http http;
    std::shared_ptr<Net::Epolloop> loop(new Net::Epolloop());
    std::shared_ptr<Net::Tcpserver> server(new Net::Tcpserver(loop));
    server->setUser(&http);
    server->Tcpinit();
    loop->loop();
    return 0;
}