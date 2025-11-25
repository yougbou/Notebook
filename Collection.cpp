//
// Created by gbouri youssef  on 23/11/25.
//

#include "Collection.h"

Collection &Collection::operator=(const Collection &other) {
    if (this == &other)
        return *this;

    // 1. Copy simple fields
    name = other.name;

    // 2. Deep copy the notes: allocate NEW Notes so no pointers are shared
    notes.clear();
    notes.reserve(other.notes.size());

    for (const auto& notePtr : other.notes) {
        if (notePtr) {
            notes.push_back(std::make_shared<Note>(*notePtr));
        } else {
            notes.push_back(nullptr);
        }
    }
    // If you want to reset them:
    observers.clear();
    return *this;
}

void Collection::AddNote(std::shared_ptr<Note> note) {
    notes.push_back(note);
    Notify();
}


bool Collection::RemoveNote(const std::string &title) {
    for (auto it = notes.begin(); it != notes.end(); ++it ) {
        if ((*it)->GetTitle() == title) {
            if (!(*it)->IsLocked()) {
                notes.erase(it);
                Notify();
                return true;
            } else{ std::cout << "can't delete" << std::endl;
                return false;
            }
        }
    }
    return false;
}

std::shared_ptr<Note> Collection::GetNote(const std::string &title) {
    for (const auto& note : notes)
        if (note->GetTitle() == title)
            return note;
    return nullptr;
}
