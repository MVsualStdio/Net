
#include "../Task/Task.hpp"
#include "../Queue/Queue.hpp"
#include "../Queue/ChronoQueue.hpp"
#include "../Task/WorkItem.hpp"
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
            while(1){
                int x = std::rand()%100;
                qu.push(move(x));
                cout<<"take  "<<x<<endl;
                sleep(1);
            }
        }
        void pop(){
            while(1){
                cout<<"pop  "<<qu.pop()<<endl;
                sleep(2);
             }
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
    ChronoQueue qut;
    
    //Queue<Task> qut;
    // function<void()> f1 = bind(&testQueue::take,&qu);
    // function<void()> f2 = bind(&testQueue::pop,&qu);
    
    // Task t1(&testQueue::take,&qu);
    // Task t2(f2);
    shared_ptr<Net::WorkItem> task = static_cast<shared_ptr<WorkItem>>(new Task(&testQueue::push,&qu));
    shared_ptr<Net::WorkItem> task2 = static_cast<shared_ptr<WorkItem>>(new Task(&testQueue::pop,&qu));
    
    chrono::seconds s(2);
    chrono::time_point<chrono::high_resolution_clock> stap = chrono::high_resolution_clock::now() + s;
    TimeStamp ts2(stap,move(task2));
    TimeStamp ts(stap,move(task));
    
    // cout<<1;
    
    qut.chronoPush(ts);
    qut.chronoPush(ts2);

    std::this_thread::sleep_for(std::chrono::seconds(50));
    //t3.run();
    //t3.run();
    // qut.push(move(t1));
    // qut.push(move(t2));
    //qut.push(t2);
    // std::thread th1(qut.pop().getTask());
    // std::thread th2(qut.pop().getTask());
    // th1.join();
    // th2.join();
}