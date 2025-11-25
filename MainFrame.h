//
// Created by gbouri youssef  on 23/11/25.
//

#ifndef NOTEBOOK_MAINFRAME_H
#define NOTEBOOK_MAINFRAME_H


#include <wx/wx.h>
#include "Collection.h"
#include "CollectionObserver.h"
#include "StorageManager.h"


class MainFrame : public wxFrame {
private:
    Collection mainCollection;
    Collection importantCollection;
    std::vector<Collection> collections;
    CollectionObserver observerMain;
    CollectionObserver observerImportant;
    //Lists
    wxListBox* noteList;
    wxTextCtrl* titleCtrl;
    wxTextCtrl* noteCtrl;
    wxTextCtrl* collectionCtrl;
    //Buttons
    wxButton* addButton;
    wxButton* deleteButton;
    wxButton* lockButton;
    wxButton* importantButton;
    //Combo Box
    wxComboBox* collectionCombo;

public:
    MainFrame();

    void OnClose(wxCloseEvent& event);
    void OnAddNote(wxCommandEvent&);
    void OnDeleteNote(wxCommandEvent&);
    void OnLockNote(wxCommandEvent&);
    void OnImportantNote(wxCommandEvent&);
    void OnSelectedNote(wxCommandEvent&);
    void OnCollectionSelected(wxCommandEvent&);

    void UpdateNoteList(const std::string& collectionName);

};


#endif //NOTEBOOK_MAINFRAME_H
