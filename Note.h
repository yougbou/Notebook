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

public:
    Note(const std::string &t, const std::string &txt)
            : title(t), text(txt), locked(false) {}

    //Getters
    const std::string &GetTitle() const { return title; }
    const std::string &GetText() const { return text; }

    bool IsLocked() const { return locked; }

    //Setters
    void SetTitle(const std::string &t) { if(!locked) title = t; }
    void SetText(const std::string &t) { if(!locked) text = t; }

    void Lock() { locked = true; }
    void Unlock() { locked = false; }
};
#endif //NOTEBOOK_NOTE_H
