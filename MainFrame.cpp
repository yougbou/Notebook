//
// Created by gbouri youssef  on 23/11/25.
//

#include "MainFrame.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "NoteApp", wxDefaultPosition, wxSize(500, 400)),
                         mainCollection("Default"), importantCollection("Important"),
                         observerMain("Default"), observerImportant("Important")
{

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    //Combo Box
    wxBoxSizer* comboSizer = new wxBoxSizer(wxHORIZONTAL);
    comboSizer->AddStretchSpacer(1);
    comboSizer->Add(new wxStaticText(this, wxID_ANY, "Collection:"), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    collectionCombo = new wxComboBox(this, wxID_ANY);
    collectionCombo->Append("Default");
    collectionCombo->Append("Important");
    collectionCombo->SetSelection(0);
    //UpdateNoteList("Default");
    comboSizer->Add(collectionCombo, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    comboSizer->AddStretchSpacer(1);
    mainSizer->Add(comboSizer, 0, wxEXPAND | wxALL, 5);

    //Note List
    noteList = new wxListBox(this, wxID_ANY);
    mainSizer->Add(noteList, 1, wxEXPAND | wxALL, 5);

    //Title and Collection Name
    wxBoxSizer* titleSizer = new wxBoxSizer(wxHORIZONTAL);
    titleSizer->Add(new wxStaticText(this, wxID_ANY, "Title:"), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    titleCtrl = new wxTextCtrl(this, wxID_ANY);
    titleSizer->Add(titleCtrl, 1, wxEXPAND | wxALL, 5);

    titleSizer->Add(new wxStaticText(this, wxID_ANY, "Collection name (optional):"), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    collectionCtrl = new wxTextCtrl(this, wxID_ANY, "");
    titleSizer->Add(collectionCtrl, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(titleSizer, 0, wxEXPAND | wxALL, 5);

    // Text area
    wxBoxSizer* noteSizer = new wxBoxSizer(wxVERTICAL);
    noteSizer->Add(new wxStaticText(this, wxID_ANY, "Note:"), 0, wxALL, 5);
    noteCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    noteSizer->Add(noteCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(noteSizer, 2, wxEXPAND | wxALL, 5);

    //Buttns
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addButton = new wxButton(this, wxID_ANY, "Add"), 1, wxEXPAND | wxALL, 5);
    buttonSizer->Add(deleteButton = new wxButton(this, wxID_ANY, "Delete"), 1, wxEXPAND | wxALL, 5);
    buttonSizer->Add(lockButton = new wxButton(this, wxID_ANY, "Lock / Unlock"), 1, wxEXPAND | wxALL, 5);
    buttonSizer->Add(importantButton = new wxButton(this, wxID_ANY, "Important"), 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);

    SetSizer(mainSizer);
    Centre();


    Bind(wxEVT_BUTTON, &MainFrame::OnAddNote, this, addButton->GetId());
    Bind(wxEVT_BUTTON, &MainFrame::OnDeleteNote, this, deleteButton->GetId());
    Bind(wxEVT_BUTTON, &MainFrame::OnLockNote, this, lockButton->GetId());
    Bind(wxEVT_BUTTON, &MainFrame::OnImportantNote, this, importantButton->GetId());

    noteList->Bind(wxEVT_LISTBOX, &MainFrame::OnSelectedNote, this);
    collectionCombo->Bind(wxEVT_COMBOBOX, &MainFrame::OnCollectionSelected, this);
}
void MainFrame::OnAddNote(wxCommandEvent&) {
    auto title = titleCtrl->GetValue().ToStdString();
    auto text = noteCtrl->GetValue().ToStdString();
    auto collName = collectionCtrl->GetValue().ToStdString();

    if (title.empty() || text.empty())
        return;

    if (collName.empty())
        collName = "Default";

    auto note = std::make_shared<Note>(title, text);
    if (collName == "Default") {
        mainCollection.AddNote(note);
        UpdateNoteList("Default");
    }
    else {

       Collection* it = nullptr;
        for (auto& c : collections) {
            if (c.GetName() == collName) {
                it = &c;
                break; // Stop searching once found
            }
        }

        // create new collection
        if (it == nullptr) {
            collections.emplace_back(collName);
            collectionCombo->Append(collName);
            it = &collections.back();
        }

        it->AddNote(note);

        if (collectionCombo->GetValue().ToStdString() == collName)
            noteList->Append(title);

        std::cout << "note title : " << title << ", note text : " << text << std::endl;
    }
    noteCtrl->Clear();
    titleCtrl->Clear();
    collectionCtrl->Clear();

}

void MainFrame::OnDeleteNote(wxCommandEvent &) {
    int sel = noteList->GetSelection();
    if (sel == wxNOT_FOUND) return;

    std::string title = noteList->GetString(sel).ToStdString();
    if(mainCollection.RemoveNote(title))
        noteList->Delete(sel);
    else wxMessageBox(wxT("Note is locked, Can't delete"),
                      wxT("Warning"), wxICON_WARNING);
}

void MainFrame::OnLockNote(wxCommandEvent&){
    int sel = noteList->GetSelection();
    if (sel == wxNOT_FOUND) return;

    std::string title = noteList->GetString(sel).ToStdString();
    std::shared_ptr<Note> note = mainCollection.GetNote(title);

    if(note->IsLocked()) {
        mainCollection.GetNote(title)->Unlock();
        wxMessageBox("Note is unlocked", "Success");
    }
    else {
        mainCollection.GetNote(title)->Lock();
        wxMessageBox("Note is locked", "Success");
    }
}

void MainFrame::OnImportantNote(wxCommandEvent&) {
    int sel = noteList->GetSelection();
    if (sel == wxNOT_FOUND)
        return;

    std::string title = noteList->GetString(sel).ToStdString();
    std::string selectedCollection = collectionCombo->GetValue().ToStdString();
    std::shared_ptr<Note> note = nullptr;

    // find note collection
    if (selectedCollection == "Default") {
        note = mainCollection.GetNote(title);
        mainCollection.RemoveNote(title);
        UpdateNoteList("Default");
    }
    else if (selectedCollection == "Important") {
        return;
    }
    else {
        for (int i = 0; i < collections.size(); ++i) {
            if (collections[i].GetName() == selectedCollection) {
                note = collections[i].GetNote(title);
                collections[i].RemoveNote(title);
                break;
            }
        }
    }

    //add note
    if (note) {
        importantCollection.AddNote(note);
        wxMessageBox("Note added to Important Collection!", "Success");
    }
}


void MainFrame::OnSelectedNote(wxCommandEvent&) {
    std::string selectedTitle = noteList->GetStringSelection().ToStdString();
    if (selectedTitle.empty())
        return;

    std::string selectedCollection = collectionCombo->GetValue().ToStdString();
    std::shared_ptr<Note> note = nullptr;


    if (selectedCollection == "Default") {
        note = mainCollection.GetNote(selectedTitle);
    } else if(selectedCollection == "Important"){
        note = importantCollection.GetNote(selectedTitle);
    }
    else{
        for (int i = 0; i < collections.size(); ++i) {
            if (collections[i].GetName() == selectedCollection) {
                note = collections[i].GetNote(selectedTitle);
                break;
            }
        }
    }

    if (note)
        noteCtrl->SetValue(note->GetText());
    else
        noteCtrl->Clear();
}


void MainFrame::OnCollectionSelected(wxCommandEvent&) {
    std::string selectedName = collectionCombo->GetValue().ToStdString();
    UpdateNoteList(selectedName);
}

void MainFrame::UpdateNoteList(const std::string &collectionName) {
    noteList->Clear();

    if (collectionName == "Default") {
        const auto& notes = mainCollection.GetNotes();
        for (const auto& note : notes)
            noteList->Append(note->GetTitle());
        return;
    }

    if (collectionName == "Important") {
        const auto& notes = importantCollection.GetNotes();
        for (const auto& note : notes)
            noteList->Append(note->GetTitle());
        return;
    }

    for (const auto& coll : collections) {
        if (coll.GetName() == collectionName) {
            const auto& notes = coll.GetNotes();
            for (const auto& note : notes)
                noteList->Append(note->GetTitle());
            break;
        }
    }
}



