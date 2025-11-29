//
// Created by gbouri youssef  on 23/11/25.
//

#ifndef NOTEBOOK_COLLECTIONOBSERVER_H
#define NOTEBOOK_COLLECTIONOBSERVER_H

#include <iostream>
#include "Observer.h"

class CollectionObserver : public Observer {
private:
    std::string collectionName;
    int noteCount;

public:
    explicit CollectionObserver(const std::string& name) : collectionName(name) {}

    int& GetNoteCount() {
        return noteCount;
    }

    void Update(int noteCount) override {
        this->noteCount = noteCount;
        std::cout << "Collection [" << collectionName
                  << "] now has " << this->noteCount << " notes.\n";
    }
};

#endif //NOTEBOOK_COLLECTIONOBSERVER_H
