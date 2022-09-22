#include "Buffer.hpp"
#include "../Socket/Connectserver.hpp"

using namespace Net;

void Buffer::ensureInsert(int length){
    if (getFreeSize() >= length) {
        return;
    }
    int min_cap_need = capacity + length;
    if(min_cap_need > maxCapacity){
        throw std::runtime_error("out of capacity");
    }
    int newcap = capacity + length;
    int doublecap = capacity*2;
    if(min_cap_need > doublecap){
        newcap = min_cap_need;
    }
    else{
        if(capacity < 1024){
            newcap = doublecap <= maxCapacity ? doublecap : maxCapacity;
        }
        else{
            while(newcap < min_cap_need){
                newcap += newcap/4;
                if(newcap > maxCapacity){
                    newcap = maxCapacity;
                    break;
                }
            }
        }
    }
    resize(newcap);
}

void Buffer::resize(int newcap){
    int unread_size = getUnreadSize();

    if (newcap == capacity) {
        return;
    }


    char* temp = new char[newcap];
    for (int i = 0; i < unread_size; i++) {
        int cur_index = (readPos + i) % capacity;
        memcpy(temp + i, buffer + cur_index, 1);
    }
    delete []buffer;
    buffer = temp;
    capacity = newcap;
    dataSize = capacity+1;
    readPos = 0;
    writePos = unread_size;
}

int Buffer::getUnreadSize(){
    if(readPos >= writePos){
        return writePos - readPos;
    }
    return dataSize - readPos + writePos;
}

int Buffer::getFreeSize(){
    return capacity - getUnreadSize();
}

int Buffer::read(char* data,int length){
    if(length > getUnreadSize()){
        return -1;
    }
    int curIndex = readPos;
    for (int i = 0; i < length; i++) {
        curIndex = (readPos + i) % dataSize;
        memcpy(data + i,  buffer + curIndex, 1);
    }
    readPos = (curIndex + 1) % dataSize;
    return length;
}


int Buffer::writeBuffer(const char* data,int length){
    if (length <= 0) {
        return 0;
    }
    ensureInsert(length);
    int curIndex = writePos;
    for(int i=0;i<length;++i){
        curIndex = (writePos + i) % dataSize;
        memcpy(buffer + curIndex,data + i, 1);
    }
    writePos = (curIndex+1)%dataSize;
    return length;
}

int Buffer::writeConnect(Connectserver* con){
    int fd = con->getFd();
    int total_sent_num = 0;
    while (getUnreadSize() > 0) {
        int cur_send_len = writePos - readPos;
        if (readPos > writePos) {
            cur_send_len = capacity - readPos;
        }
        size_t writeNum = ::write(fd, buffer + readPos, cur_send_len);
        if (writeNum == 0) {
            if (errno == EINTR) {
                continue;
            } else {
                // 缓冲区满了，或者写入报错，直接退出
                break;
            }
        }
        readPos = (readPos + writeNum) % dataSize;
        total_sent_num += writeNum;
  }
  return total_sent_num;
}

int Buffer::readConnect(Connectserver* con){
    int socketfd = con->getFd();
    if(socketfd < 0) {
        LogDebug(Net::Logger::WARN) << "socket id minus error, errno: "<< errno;
        return -1;
    }
    char line[MAX_LINE];
    bzero(line, MAX_LINE);
    ssize_t read_length = ::read(socketfd, line, MAX_LINE);
    if(read_length < 0) {
        if(errno == ECONNRESET) {
            LogDebug(Net::Logger::WARN) << "ECONNRESET error, closed: " << socketfd;
            return -1;
        } 
    } 
    else if(read_length == 0) {
        LogDebug(Net::Logger::MESSAGE) <<"Client Connection closed: " << socketfd;
        return 0;
    }
    return this->writeBuffer(line,read_length);
    
}


void Buffer::clean(){
    readPos = 0;
    writePos = 0;
}