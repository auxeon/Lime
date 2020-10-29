#ifndef UNDOREDO_HPP
#define UNDOREDO_HPP

#include <iostream>
#include <stack>

//#define VERBOSE


class Command{
    public:
    virtual void execute()=0; 
    virtual void unexecute()=0; 
};

// example command
class IntCommand : public Command{
    public:
    IntCommand():a(0){

    }
    ~IntCommand(){

    }
    void execute() override{
        ++a;
        std::cout<<"execute : "<<a<<std::endl;
    }
    void unexecute() override{
        --a;
        std::cout<<"unexecute : "<<a<<std::endl;
    }
    private:
        int a=0;
};




template <typename T=int>
class UndoRedo{

private:
std::stack<T> m_undo;
std::stack<T> m_redo;
T m_command;


public:
    // to simulate global event system
    void doaction(T a){
        m_undo.push(a);
        a->execute();
        #ifdef VERBOSE
            std::cout<<"(usize,rsize) : ("<<m_undo.size()<<", "<<m_redo.size()<<")"<<std::endl;
        #endif

    }
    void undoaction(){
        if(m_undo.size() > 0){
            auto top = m_undo.top();
            top->unexecute();
            m_redo.push(top);
            m_undo.pop();
            #ifdef VERBOSE
                std::cout<<"undo : "<<top<<" (usize,rsize) : ("<<m_undo.size()<<", "<<m_redo.size()<<")"<<std::endl;
            #endif
        }
        else{
            std::cout<<"nothing to undo\n";
        }
    }
    void redoaction(){
        if(m_redo.size() > 0){
            auto top = m_redo.top();
            top->execute();
            m_undo.push(top);
            m_redo.pop();
            #ifdef VERBOSE
                std::cout<<"redo : "<<top<<" (usize,rsize) : ("<<m_undo.size()<<", "<<m_redo.size()<<")"<<std::endl;
            #endif
        }
        else{
            std::cout<<"nothing to redo\n";
        }
    }
    void reset(){
        while(m_undo.size()>0){
            #ifdef VERBOSE
                std::cout<<"(usize,rsize) : ("<<m_undo.size()<<", "<<m_redo.size()<<")"<<std::endl;
            #endif
            m_undo.pop();
        }
        std::cout<<"undo history cleared\n";
        while(m_redo.size()>0){
            #ifdef VERBOSE
                std::cout<<"(usize,rsize) : ("<<m_undo.size()<<", "<<m_redo.size()<<")"<<std::endl;
            #endif
            m_redo.pop();
        }
        std::cout<<"redo history cleared\n";
    }
};

#endif