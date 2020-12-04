# Lime
Game Engine 3.0


# Instructions
----------------

## Build
0. make sure no spaces exist in the absolute path
1. launch WINBUILD.bat
2. open Lime.sln located at project rootdir
3. build 
4. run 

## Milestone 4
0. **EVENT TYPES** 
    List of events can be found in ```Lime/core/Types.hpp```

1. **SUBSCRIPTION EVENTS**
    ```Lime/core/EventManager.hpp```
    All events are subscription based events by default

2. **BROADCAST EVENTS** 
    Press space to trigger broadcast event
    ```Lime/systems/BroadcastSystem.hpp```
    all entities get registered into the broadcast system
    each system has a system archetype that registers entities with the same archetype signature

3. **TEMPORAL EVENTS**
    ```Lime/core/EventManager.hpp```
    has function ```sendTimedEvent(Event&e, long long ms)```
    temporal events are sent as showin in
    ```Lime/core/Lime.hpp : Lines 283-292``` 
    toggle debug draw every 2 secs


4. **SPECIFIC ENTITY**
    ```Lime/systems/DMSystem.hpp```
    If entity ID matches the recipient ID then the handle function is called


Controls
---------

0. **Camera**
    movement : TGFH

1. **Kakashi**
    movement : IKJL
    rotate : UO
    global toggle debug : X
    speak : B (Direct Message)

2. **Goku**
    movement : WASD
    rotate : QE
    global toggle debug : Z
    speak : N (Direct Message)

3. **Trigger Broadcast**
    trigger : SPACE