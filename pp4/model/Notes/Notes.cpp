//
// Created by rchowda on 11/18/2016.
//

#include "Notes.h"

Notes::Notes(int noteId, const std::string &title, const std::string &body, User *owner) : noteId(noteId), title(title), body(body), owner(owner) {}
