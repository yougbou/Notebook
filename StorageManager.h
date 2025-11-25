//
// Created by gbouri youssef  on 25/11/25.
//

#ifndef NOTEBOOK_STORAGEMANAGER_H
#define NOTEBOOK_STORAGEMANAGER_H

#include <vector>
#include <string>
#include "json.hpp"
#include "Collection.h"
#include "Note.h"

class StorageManager {
public:

    static void Save(const std::vector<Collection>& collections, const std::string& filepath);
    static void Load(std::vector<Collection>& collections, const std::string& filepath);

};


#endif //NOTEBOOK_STORAGEMANAGER_H
