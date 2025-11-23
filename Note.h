//
// Created by gbouri youssef  on 23/11/25.
//

#ifndef NOTEBOOK_NOTE_H
#define NOTEBOOK_NOTE_H
#include <string>

class Note {
private:
    std::string title;
    std::string text;
    bool locked;
    bool important;
    std::string collectionName;

public:
    Note(const std::string &t, const std::string &txt, const std::string &collection)
            : title(t), text(txt), locked(false), important(false), collectionName(collection) {}

    //Getters
    const std::string &GetTitle() const { return title; }
    const std::string &GetText() const { return text; }
    const std::string &GetCollectionName() const { return collectionName; }
    bool IsLocked() const { return locked; }
    bool IsImportant() const { return important; }

    //Setters
    void SetTitle(const std::string &t) { if(!locked) title = t; }
    void SetText(const std::string &t) { if(!locked) text = t; }
    void SetCollectionName(const std::string &c) { if (!locked) collectionName = c; }
    void SetImportant(bool imp) { if (!locked) important = imp; }


    void Lock() { locked = true; }
    void Unlock() { locked = false; }
};
#endif //NOTEBOOK_NOTE_H
