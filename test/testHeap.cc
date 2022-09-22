#include"Task/Task.hpp"
#include "../Heap/Heap.hpp"
#include"../ThreadPool/ThreadPool.hpp"
#include <iostream>
#include<thread>
#include <random>
#include "../Task/WorkItem.hpp"
#include<utility>
#include<unistd.h>
using namespace std;
using namespace Net;

class testHeap{
    private:
        Heap<int> heap;
    public:
        void run1(){
            for(int i=0;i<10;++i){
                int x = random()%100;
                heap.push(x);
                cout<<"push:"<<x<<"   ";
            }
            cout<<endl;
            sleep(1);
        }
        void run2(){ 
            sleep(2);      
            for(int i=0;i<10;--i){ 
                int x = heap.pop();
                cout<<"pop:"<<x<<"  "<<flush;
            }

            cout<<endl;
        }
};


int main(){
    
    testHeap qu;
    shared_ptr<Net::WorkItem> task = static_cast<shared_ptr<WorkItem>>(new Task(&testHeap::run1,&qu));
    shared_ptr<Net::WorkItem> task2 = static_cast<shared_ptr<WorkItem>>(new Task(&testHeap::run2,&qu));
    ThreadPool::instance()->addTask(move(task2));
    ThreadPool::instance()->addTask(move(task));
    while (1);
}