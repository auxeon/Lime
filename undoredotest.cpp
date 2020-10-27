#include <iostream>
#include "./UndoRedo.hpp"


int main(){

    // UndoRedo<int> commandUR;

    // commandUR.doaction(1);
    // commandUR.doaction(2);
    // commandUR.doaction(3);
    // commandUR.doaction(4);
    // commandUR.doaction(5);
    // commandUR.undoaction();
    // commandUR.undoaction();
    // commandUR.redoaction();
    // commandUR.undoaction();
    // commandUR.undoaction();
    // commandUR.undoaction();
    // commandUR.undoaction();
    // commandUR.undoaction();
    // commandUR.redoaction();
    // commandUR.redoaction();
    // commandUR.redoaction();
    // commandUR.redoaction();
    // commandUR.redoaction();
    // commandUR.redoaction();
    // commandUR.reset();

    UndoRedo<Command*> ur;

    IntCommand ic;
    Command* cmd = &ic;

    ur.doaction(cmd);
    ur.doaction(cmd);
    ur.doaction(cmd);
    
    ur.undoaction();
    ur.undoaction();
    ur.undoaction();
    ur.redoaction();
    ur.redoaction();
    ur.redoaction();
    ur.redoaction();

    ur.redoaction();
    ur.reset();


    return 0;
}