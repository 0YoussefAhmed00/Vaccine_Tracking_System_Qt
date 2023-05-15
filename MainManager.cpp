#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
#include "MainManager.h"
#include "Admin.h"
#include "User.h"
using namespace std;

bool MainManager::Check_Admin(string s,string pass)
{
    if (s == pass)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to create a new entry and add it to the entries vector or waiting list
void MainManager::CreateEntry(Entry newEntry) {
    //Entry newEntry = { name, id, government, age, gender, vaccineType, firstDose, firstDate, secondDose, secondDate };
    if (newEntry.firstDose && newEntry.secondDose) {
        entries.insert({ newEntry.id, newEntry });  // Add to entries vector if already vaccinated
    }
    else {
        waitingList.push(newEntry);  // Add to waiting list if not yet vaccinated
    }
}

// Function to edit an entry and add it to the waiting list if not fully vaccinated
bool MainManager::EditEntry(int id, Entry newEntry) {
    bool found = false;
    queue<Entry> queueCopy = waitingList;
    int index = 0;
    while (!queueCopy.empty())
    {
        Entry entry = queueCopy.front();
        if (entry.id == id) {
            found = true;
            break;
        }
        index += 1;
        queueCopy.pop();
    }
    queueCopy.~queue();
    stack<Entry> tempQue;
    if (found) {
        while (index > 0) {
            tempQue.push(waitingList.front());
            waitingList.pop();
            index -= 1;
        }
        if (!(newEntry.firstDose && newEntry.secondDose))
            waitingList.front() = newEntry;
        else {
            waitingList.pop();
            entries.insert({ id, newEntry });
        }
        while (!tempQue.empty()) {
            waitingList.push(tempQue.top());
            tempQue.pop();
        }
        return true;
    }
    tempQue.~stack();

    auto it = entries.find(id);
    if (it != entries.end()) {
        if ((newEntry.firstDose && newEntry.secondDose))
            it->second = newEntry;
        else {
            waitingList.push(newEntry);
            DeleteEntry(id);
        }
        return true;
    }
    else {
        return false;
    }
}

// Function to delete all the entries everywhere
void MainManager::Delete_All() {
    entries.clear();
    while (!waitingList.empty()) {
        waitingList.pop();
    }
    // you need to save the entries to the file
}


// Function to check the vaccination status of a given entry
bool MainManager::CheckVaccineStatus(int id) {
    for (pair<int, Entry> entry : entries) {
        if (entry.second.id == id) {
            return (entry.second.firstDose && entry.second.secondDose);
        }
    }
    return NULL;  // Return NULL if no entry is found with the given name
}

// Function to delete an entry from the entries vector or waiting list
void MainManager::DeleteEntry(int id) {
    if (entries.erase(id)) {
        cout << "Entry deleted successfully from entries\n";
    }
    else {
        // Check if the entry is in the waiting list
        queue<Entry> temp;
        bool found = false;
        while (!waitingList.empty()) {
            Entry entry = waitingList.front();
            if (entry.id == id) {
                found = true;
            }
            else {
                temp.push(entry);
            }
            waitingList.pop();
        }
        while (!temp.empty()) {
            Entry entry = temp.front();
            waitingList.push(entry);
            temp.pop();
        }
        if (found) {
            cout << "Entry deleted successfully from waiting list\n";
        }
        else {
            cout << "Error: Entry not found\n";
        }
    }
}

// Function to show a certain entry
void MainManager::ShowEntry(int id) {
    auto it = entries.find(id);
    bool found = false;
    if (it != entries.end()) {
        cout << "\n" << "Entry: \nName: " << it->second.name << "\n"
             << "ID: " << it->second.id << "\n"
             << "Password: " << it->second.password << "\n"
             << "Government: " << it->second.government << "\n"
             << "Age: " << it->second.age << "\n"
             << "Gender: " << it->second.gender << "\n"
             << "Vaccine Type: " << it->second.vaccineType << "\n"
             << "Vaccinated First Dose: " << (it->second.firstDose ? "Yes, on " + it->second.firstDoseDate : "No") << "\n"
             << "Vaccinated Second Dose: " << (it->second.secondDose ? "Yes, on " + it->second.secondDoseDate : "No")
             << "\nWaiting List: " << "NO" << "\n\n";
        return;
    }

    queue<Entry> tempQueue = waitingList;
    while (!tempQueue.empty()) {
        if (tempQueue.front().id == id) {
            cout << "\n" << "Entry: \nName: " << tempQueue.front().name << "\n"
                 << "ID: " << tempQueue.front().id << "\n"
                 << "Password: " << tempQueue.front().password << "\n"
                 << "Government: " << tempQueue.front().government << "\n"
                 << "Age: " << tempQueue.front().age << "\n"
                 << "Gender: " << tempQueue.front().gender << "\n"
                 << "Vaccine Type: " << tempQueue.front().vaccineType << "\n"
                 << "Vaccinated First Dose: " << (tempQueue.front().firstDose ? "Yes, on " + tempQueue.front().firstDoseDate : "No") << "\n"
                 << "Vaccinated Second Dose: " << (tempQueue.front().secondDose ? "Yes, on " + tempQueue.front().secondDoseDate : "No")
                 << "\nWaiting List: " << "YES" << "\n\n";
            tempQueue.~queue();
            return;
        }
        else {
            tempQueue.pop();
        }
    }
    cout << "Invalid ID!!!" << endl;
    tempQueue.~queue();
}

// Function to get the entry
Entry MainManager::GetEntry(int id) {
    // Check if the entry is in the entries list
    qDebug() << "Here 2" << "\n";
    qDebug() << entries.size() << "\n";
    for (pair<int, Entry> entry : entries) {
        if (entry.second.id == id) {
            return entry.second;
        }
    }
    // Check if the entry is in the waiting list
    queue<Entry> temp = waitingList;
    while (!temp.empty()) {
        Entry entry = temp.front();
        if (entry.id == id) {
            return entry;
        }
        temp.pop();
    }
    temp.~queue();

    // Return a default-constructed Entry if the entry was not found
    return Entry(); // Modify this line based on your requirements
}

// Function to show all entries and waiting list
void MainManager::ShowAll() {
    cout << "Entries:\n";
    for (auto& entry : entries) {
        cout << "\n" << "Name: " << entry.second.name << "\n"
             << "ID: " << entry.second.id << "\n"
             << "Password: " << entry.second.password << "\n"
             << "Government: " << entry.second.government << "\n"
             << "Age: " << entry.second.age << "\n"
             << "Gender: " << entry.second.gender << "\n"
             << "Vaccine Type: " << entry.second.vaccineType << "\n"
             << "Vaccinated First Dose: " << (entry.second.firstDose ? "Yes, on " + entry.second.firstDoseDate : "No") << "\n"
             << "Vaccinated Second Dose: " << (entry.second.secondDose ? "Yes, on "+entry.second.secondDoseDate : "No") << "\n\n";
    }
    cout << "Waiting list:\n";
    int i = 1;
    queue<Entry> tempQue = waitingList;
    while (!tempQue.empty()) {
        Entry entry = tempQue.front();
        cout << "\n" << i << ". Name: " << entry.name << "\n"
             << "ID: " << entry.id << "\n"
             << "Password: " << entry.password << "\n"
             << "Government: " << entry.government << "\n"
             << "Age: " << entry.age << "\n"
             << "Gender: " << entry.gender << "\n"
             << "Vaccine Type: " << entry.vaccineType << "\n"
             << "Vaccinated First Dose: " << (entry.firstDose ? "Yes, on " + entry.firstDoseDate : "No") << "\n"
             << "Vaccinated Second Dose: " << (entry.secondDose ? "Yes, on " + entry.secondDoseDate : "No") << "\n\n";
        tempQue.pop();
        i++;
    }
    tempQue.~queue();
}

// Function to show all the netries in the waiting lists
void MainManager::ShowWaitingList() {
    cout << "Waiting list:\n";
    queue<Entry> tempQueue = waitingList;
    int i = 1;
    while (!tempQueue.empty()) {
        Entry entry = tempQueue.front();
        cout << "\n" << i << ". Name: " << entry.name << "\n"
             << "ID: " << entry.id << "\n"
             << "Password: " << entry.password << "\n"
             << "Government: " << entry.government << "\n"
             << "Age: " << entry.age << "\n"
             << "Gender: " << entry.gender << "\n"
             << "Vaccine Type: " << entry.vaccineType << "\n"
             << "Vaccinated First Dose: " << (entry.firstDose ? "Yes, on " + entry.firstDoseDate : "No") << "\n"
             << "Vaccinated Second Dose: " << (entry.secondDose ? "Yes, on " + entry.secondDoseDate : "No") << "\n\n";
        tempQueue.pop();
        i++;
    }
    tempQueue.~queue();
}

// Function to show all the entries in the entries map
void MainManager::ShowEntriesMap() {
    cout << "Entries:\n";
    for (auto& entry : entries) {
        cout << "\n" << "Name: " << entry.second.name << "\n"
             << "ID: " << entry.second.id << "\n"
             << "Password: " << entry.second.password << "\n"
             << "Government: " << entry.second.government << "\n"
             << "Age: " << entry.second.age << "\n"
             << "Gender: " << entry.second.gender << "\n"
             << "Vaccine Type: " << entry.second.vaccineType << "\n"
             << "Vaccinated First Dose: " << (entry.second.firstDose ? "Yes, on " + entry.second.firstDoseDate : "No") << "\n"
             << "Vaccinated Second Dose: " << (entry.second.secondDose ? "Yes, on " + entry.second.secondDoseDate : "No") << "\n\n";
    }
}

// Function to write the entries and waiting list to a CSV file
void MainManager::SaveEntriesToFile(string filename) {
    if (entries.size() < 1) {
        ofstream file(filename);
        file << "";
    }
    ofstream file(filename);
    file << "Name,ID,Government,Age,Gender,Vaccine Type,First Dose,First Date,Second Dose,Second Date,Password\n";  // Write the header row
    for (pair<int, Entry> entry : entries) {
        file << entry.second.name
             << "," << entry.second.id
             << "," << entry.second.government
             << "," << entry.second.age
             << "," << entry.second.gender
             << "," << entry.second.vaccineType
             << "," << ((entry.second.firstDose) ? "Yes" : "No")
             << "," << ((entry.second.firstDose) ? entry.second.firstDoseDate : "")
             << "," << ((entry.second.secondDose) ? "Yes" : "No")
             << "," << ((entry.second.secondDose) ? entry.second.secondDoseDate : "")
             << "," << (entry.second.password)
             << "\n";
    }
    queue<Entry> tempList = waitingList;
    while (!tempList.empty()) {
        Entry entry = tempList.front();
        file << entry.name
             << "," << entry.id
             << "," << entry.government
             << "," << entry.age
             << "," << entry.gender
             << "," << entry.vaccineType
             << "," << (entry.firstDose ? "Yes" : "No")
             << "," << (entry.firstDose ? entry.firstDoseDate : "")
             << "," << (entry.secondDose ? "Yes" : "No")
             << "," << (entry.secondDose ? entry.secondDoseDate : "")
             << "," << (entry.password)
             << "\n";
        tempList.pop();
    }
    //ShowAll();
    //tempList.~queue();
    file.close();
    cout << "Entries saved to file: " << filename << "\n";
}

// Function to load entries and waiting list from a CSV file
void MainManager::LoadEntriesFromFile(string filename) {
    entries.clear();  // Clear existing entries
    while (!waitingList.empty()) {
        waitingList.pop();  // Clear existing waiting list
    }
    vector<vector<string>> data;

    ifstream infile(filename);

    // Check if file is open
    if (!infile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;

    // Read header row
    getline(infile, line);

    // Read data rows
    while (getline(infile, line)) {
        vector<string> row;

        stringstream ss(line);

        for (int i = 0; i <= 10; i++) {
            string field= "";
            getline(ss, field, ',');
            row.push_back(field);
        }
        //cout << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "," << row[4] << "," << row[5] << "," << row[6] << "," << row[7] << "," << row[8] << "," << row[9] << endl;
        //cout << (row[6] == "Yes") << endl;
        Entry newEntry = { row[0], stoi(row[1]), row[2], stoi(row[3]), row[4][0], row[5], row[6] == "Yes", row[7], row[8] == "Yes", row[9], row[10] };
        CreateEntry(newEntry);
    }

    infile.close();
}

bool MainManager::CheckID(int id)
{
    //bool found1 = false, found2 = false;
    queue<Entry> tempwaitingList = waitingList;
    auto it = entries.find(id);
    if (it != entries.end()) {
        if (it->second.id == id)
            return true;
    }
    /*if (entries.find(id) != entries.end()) {
        return true;
    }*/
    while (!tempwaitingList.empty())
    {
        Entry entry = tempwaitingList.front();
        if (entry.id == id)
        {
            return true;
        }
        tempwaitingList.pop();
    }
    return false;
}


