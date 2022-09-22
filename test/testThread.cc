#include "ThreadPool/ThreadPool.hpp"
#include "Task/Task.hpp"
#include "Queue/Queue.hpp"
#include "Queue/ChronoQueue.hpp"
#include "Task/WorkItem.hpp"
#include<thread>
#include<random>
#include<utility>
#include<unistd.h>


using namespace std;
using namespace Net;

class testQueue : public Net::WorkItem{
    private:
        Net::Queue<int> qu;
    public:
        void push(){
            //while(1){
            for(int i=0;i<10;++i){
                int x = std::rand()%100;
                qu.push(move(x));
                cout<<"push  "<<x<<endl<<flush;
                //sleep(1);
            }
        }
        void pop(){
            //while(1){
                cout<<"pop  "<<qu.pop()<<endl<<flush;
                sleep(2);
            //}
        }
        void run(){
            while(1){
                int x = std::rand()%100;
                qu.push(move(x));
                cout<<"take  "<<x<<endl;
                sleep(1);
            }
        }
};




int main(){
    testQueue qu;
    
    // shared_ptr<Net::WorkItem> task = static_cast<shared_ptr<WorkItem>>(new Task(&testQueue::push,&qu));
    // shared_ptr<Net::WorkItem> task2 = static_cast<shared_ptr<WorkItem>>(new Task(&testQueue::pop,&qu));
    // if(task==nullptr){
    //     cout<<"error"<<endl;
    // }
    // if(task2==nullptr){
    //     cout<<"error"<<endl;
    // }

    for(int i=0;i<20;++i){
        shared_ptr<Net::WorkItem> task = static_cast<shared_ptr<WorkItem>>(new Task(&testQueue::push,&qu));
        shared_ptr<Net::WorkItem> task2 = static_cast<shared_ptr<WorkItem>>(new Task(&testQueue::pop,&qu));
        ThreadPool::instance()->addTask(move(task2));
        ThreadPool::instance()->addTask(move(task));
    }
    
    
    while(1);
    // {
    //     qu.pop();
    // }
}