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

public:
    explicit CollectionObserver(const std::string& name) : collectionName(name) {}

    void Update(int noteCount) override {
        std::cout << "Collection [" << collectionName
                  << "] now has " << noteCount << " notes.\n";
    }
};

#endif //NOTEBOOK_COLLECTIONOBSERVER_H
