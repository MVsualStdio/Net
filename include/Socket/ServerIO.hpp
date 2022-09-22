#ifndef SERVERIO_H
#define SERVERIO_H
#include<memory>
namespace Net{
    struct virtual_enable_shared_from_this_base:
        std::enable_shared_from_this<virtual_enable_shared_from_this_base> {
        virtual ~virtual_enable_shared_from_this_base() {}
    };
    template<typename T>
        struct virtual_enable_shared_from_this:
        virtual virtual_enable_shared_from_this_base {
        std::shared_ptr<T> shared_from_this() {
            return std::dynamic_pointer_cast<T>(
                virtual_enable_shared_from_this_base::shared_from_this());
        }
    };
    class ServerIO:public std::enable_shared_from_this<ServerIO>{
        public:
            virtual void serverRead()=0;
            virtual void serverWrite()=0;
            //virtual void serverClose()=0;
    };

}

#endif