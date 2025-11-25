//
// Created by gbouri youssef  on 23/11/25.
//

#include "Collection.h"

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
