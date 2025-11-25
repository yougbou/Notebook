//
// Created by gbouri youssef  on 25/11/25.
//

#include "StorageManager.h"
#include <fstream>
#include <vector>

using json = nlohmann::json;


std::shared_ptr<Note> CreateNoteFromJson(const json& jnote) {
    // We rely on .value() to provide defaults if a key is missing,
    // making the code more robust against old/corrupted save files.

    std::string title = jnote.value("title", "Untitled Note");
    std::string text = jnote.value("text", "");
    bool isLocked = jnote.value("locked", false);

    auto note = std::make_shared<Note>(title,text);
    if(isLocked)
        note->Lock();
    else note->Unlock();


    return note;
}


void StorageManager::Save(const std::vector<Collection>& collections,
                          const std::string& filepath)
{
    std::cout << "Attempting to save notes..." << std::endl;

    json root;
    root["collections"] = json::array();

    for (const auto& coll : collections) {
        json jcoll;
        jcoll["name"] = coll.GetName();
        jcoll["notes"] = json::array();

        for (const auto& notePtr : coll.GetNotes()) {
            if (!notePtr) continue; // Skip null pointers

            const Note& note = *notePtr;

            json jnote;
            jnote["title"] = note.GetTitle();
            jnote["text"] = note.GetText();
            jnote["locked"] = note.IsLocked();

            // We omit collectionName as it's redundant (it's the parent key)
            jcoll["notes"].push_back(jnote);
        }

        root["collections"].push_back(jcoll);
    }

    std::ofstream out(filepath);
    if (out.is_open()) {
        out << root.dump(4); // 4 spacing for reading
        out.close(); // ensure data is flushed to the file
        std::cout << "Notes successfully saved to: " << filepath << std::endl;
    } else {
        std::cerr << "Error: Could not open file for saving: " << filepath << std::endl;
    }
}


void StorageManager::Load(std::vector<Collection>& collections,
                          const std::string& filepath)
{
    std::cout << "Attempting to load notes..." << std::endl;

    std::ifstream in(filepath);
    if (!in.is_open()) {
        std::cout << "Note: Save file not found or could not be opened. Starting fresh." << std::endl;
        return; // file does not exist or first time running the app
    }

    json root;
    try {
        in >> root; // read the json into root
        in.close();
    } catch (const json::parse_error& e) {
        std::cerr << "Error: JSON file corrupted or invalid format. " << e.what() << std::endl;
        in.close();
        return;
    }

    collections.clear(); // Clear any old collections

    // Check if the expected "collections" key exists and is an array
    if (root.contains("collections") && root["collections"].is_array()) {


        for (const auto& jcoll : root["collections"]) {

            std::string name = jcoll.value("name", "Unnamed Collection");
            Collection coll(name);


            if (jcoll.contains("notes") && jcoll["notes"].is_array()) {
                for (const auto& jnote : jcoll["notes"]) {

                    // Create Note using the helper function
                    auto note = CreateNoteFromJson(jnote);

                    // Add the note to the collection
                    coll.AddNote(note);
                }
            }

            collections.push_back(coll);
        }
        std::cout << "Notes loaded successfully." << std::endl;
    }
}