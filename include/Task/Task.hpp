#ifndef TASK_H
#define TASK_H

#include<utility>
#include <functional>
#include<iostream>
#include<thread>
#include "WorkItem.hpp"
namespace Net{

    using namespace std;
    
    typedef std::function<void()> taskFun;
    class Task : public WorkItem{
        private:
            taskFun _task;
        public:
            // Task(taskFun task){
            //     _task = task;
            // }

            // Task(Task&& task):_task(std::move(task._task)){
            //     // cout<<"right ref"<<endl;
            //     task._task = nullptr;
            // }

            // Task(const Task& task):_task(task._task){
            //     // cout<<"left ref"<<endl;
            // }
            
            template<class T,class  ...Args>
            Task(T&& task,Args&& ...args){
                 _task = bind(std::forward<T>(task), std::forward<Args>(args)...);
            }

            void run(){
                if(_task == nullptr){
                    cout<<"ERROR"<<endl;
                    return ;
                }
                _task();
            }
    };
}

#endif