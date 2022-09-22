#ifndef BUFFER_H
#define BUFFER_H

#include<atomic>
#include<vector>
#include<string>
#include <string.h>
#include<exception>
#include<stdexcept>




namespace Net
{
    class Connectserver;
    class Buffer{
        private:
            int readPos;
            int writePos;
            char* buffer;
            int capacity;
            int maxCapacity;
            int dataSize;
        public:
            Buffer(int capacit=8,int maxCapacit=1024):readPos(0),writePos(0),\
                                capacity(capacit),maxCapacity(maxCapacit),dataSize(capacity+1){
                buffer = new char[dataSize];
            };
            ~Buffer(){
                delete buffer;
            }
            int getUnreadSize();
            int getFreeSize();
            int read(char* data,int length);
            int writeBuffer(const char *data,int length);
            int writeConnect(Connectserver* con);
            int readConnect(Connectserver* con);
            void clean();
        private:
            void ensureInsert(int length);
            void resize(int newcap);
    };
} // namespace Net



#endif