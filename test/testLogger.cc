#include "Logger/Logger.hpp"


int main(){
    LogDebug(Net::Logger::MESSAGE) << "test1";
    LogDebug(Net::Logger::MESSAGE) << "test2";
    LogDebug(Net::Logger::MESSAGE) << "test3";
    LogDebug(Net::Logger::MESSAGE) << "test4";
    LogDebug(Net::Logger::MESSAGE) << "test5";
    while(1);
}