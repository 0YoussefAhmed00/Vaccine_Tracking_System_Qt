#ifndef ADMIN_H
#define ADMIN_H
#pragma once
#include "MainManager.h"
#include <string>
#include <iostream>
#include <queue>

using namespace std;

class Admin {
public:
    //string password;
    string password;
    MainManager* mainManager;
    Admin(MainManager& mainManager);
    void Delete(int ID);
    void DeleteAll();
    void ViewAll();
    void ViewOne(int ID);
    void ViewOrderedByAge();
    void ViewWaitingList();
    void ViewDosesRecord();
    void ViewStatistics();
};
#endif // ADMIN_H
