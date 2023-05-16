#ifndef USER_H
#define USER_H
#pragma once
#include <string>
#include <iostream>
#include"MainManager.h"

using namespace std;

class User {
public:
    Entry userEntry;
    MainManager* mainManager;
    User(MainManager& mainManager) {
        this->mainManager = &mainManager;
    };
    User(Entry entry) {
        this->userEntry = entry;
    };

    //Inherited Functions From Main Manager
    void CreateUserEntry();
    void EditUserEntry(int id);
    void DeleteUserEntry(int id);
    void ShowUserEntry(int id);
    /*Entry ShowEntry(int id) {};
    bool ShowVaccineStatue(int id) {};*/
};
#endif // USER_H
