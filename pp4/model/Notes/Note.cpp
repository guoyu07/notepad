//
// Created by rchowda on 11/18/2016.
//

#include "Note.h"

Note::Note(int noteId, const std::string &title, const std::string &body, const std::string &lastModified, User *owner) : noteId(noteId), title(title), body(body), lastModified(lastModified), userName(owner) {}

Note::Note() {
    noteId = -1;
    title  = "dummy";
    body   = "dummy";
    lastModified = "never";
}

int Note::getNoteId() const {
    return noteId;
}

void Note::setNoteId(int noteId) {
    Note::noteId = noteId;
}

const std::string &Note::getTitle() const {
    return title;
}

void Note::setTitle(const std::string &title) {
    Note::title = title;
}

const std::string &Note::getBody() const {
    return body;
}

void Note::setBody(const std::string &body) {
    Note::body = body;
}

const std::string &Note::getLastModified() const {
    return lastModified;
}

void Note::setLastModified(const std::string &lastModified) {
    Note::lastModified = lastModified;
}

User *Note::getUserName() const {
    return userName;
}

void Note::setUserName(User *userName) {
    Note::userName = userName;
}
