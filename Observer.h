//
// Created by gbouri youssef  on 23/11/25.
//

#ifndef NOTEBOOK_OBSERVER_H
#define NOTEBOOK_OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(int noteCount) = 0;
};

#endif //NOTEBOOK_OBSERVER_H
