//
// Created by gbouri youssef  on 27/11/25.
//

#include <gtest/gtest.h>
#include "Note.h"
#include "Collection.h"

#include <gtest/gtest.h>
#include "Note.h"
#include "Collection.h"

//Note test
TEST(NoteTest, CreateNoteStoresData) {
    Note n("Title", "Text");

    EXPECT_EQ(n.GetTitle(), "Title");
    EXPECT_EQ(n.GetText(), "Text");
    EXPECT_FALSE(n.IsLocked());
}

TEST(NoteTest, SettersWorkWhenUnlocked) {
    Note n("Old", "Old Text");

    n.SetTitle("New");
    n.SetText("New Text");

    EXPECT_EQ(n.GetTitle(), "New");
    EXPECT_EQ(n.GetText(), "New Text");
}

TEST(NoteTest, SettersDontWorkWhenLocked) {
    Note n("Original", "Original Text");
    n.Lock();

    n.SetTitle("Changed");
    n.SetText("Changed Text");

    EXPECT_EQ(n.GetTitle(), "Original");
    EXPECT_EQ(n.GetText(), "Original Text");
    EXPECT_TRUE(n.IsLocked());
}

//Collection test
TEST(CollectionTest, AddNoteStoresNote) {
    Collection coll("MyCollection");

    auto note = std::make_shared<Note>("Note1", "Text1");
    coll.AddNote(note);

    EXPECT_EQ(coll.GetNotes().size(), 1);
    EXPECT_EQ(coll.GetNotes().at(0)->GetTitle(), "Note1");
}

TEST(CollectionTest, GetNoteFindsCorrectNote) {
    Collection coll("C");
    coll.AddNote(std::make_shared<Note>("Note", "Text"));

    auto n = coll.GetNote("Note");
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->GetText(), "Text");
}

TEST(CollectionTest, RemoveNoteDeletesCorrectNote) {
    Collection coll("C");
    coll.AddNote(std::make_shared<Note>("Note1", "Text1"));
    coll.AddNote(std::make_shared<Note>("Note2", "Text2"));

    bool removed = coll.RemoveNote("Note1");
    EXPECT_TRUE(removed);
    EXPECT_EQ(coll.GetNotes().size(), 1);
    EXPECT_EQ(coll.GetNotes().at(0)->GetTitle(), "Note2");
}

TEST(CollectionTest, RemoveNoteFailsIfNotFound) {
    Collection coll("C");
    coll.AddNote(std::make_shared<Note>("N", "T"));

    EXPECT_FALSE(coll.RemoveNote("DoesNotExist"));
    EXPECT_EQ(coll.GetNotes().size(), 1);
}