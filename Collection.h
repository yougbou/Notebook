//
// Created by gbouri youssef  on 23/11/25.
//

#ifndef NOTEBOOK_COLLECTION_H
#define NOTEBOOK_COLLECTION_H


#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>
#include "Note.h"
#include "Observer.h"


class Collection {
private:
    std::string name;
    std::vector<std::shared_ptr<Note>> notes;
    std::vector<Observer*> observers;

public:
    explicit Collection(const std::string& n) : name(n) {}

    void AddNote(std::shared_ptr<Note> note);
    bool RemoveNote(const std::string& title);
    void LockNote(const std::string& title);
    std::shared_ptr<Note> GetNote(const std::string& title);

    const std::vector<std::shared_ptr<Note>>& GetNotes() const {
        return notes;
    }
    const std::string& GetName() const {
        return name;
    }

    void Attach(Observer* obs){
        observers.push_back(obs);
    }
    void Detach(Observer* obs){
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

private:
    void Notify() {
        for (auto obs : observers)
            obs->Update(static_cast<int>(notes.size())); // .size() return a size type
    }
};


#endif //NOTEBOOK_COLLECTION_H
