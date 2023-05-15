#include "Admin.h"

Admin::Admin(MainManager& mainManager)
{
    this->mainManager = &mainManager;
    this->password = "Admin_1234";
}

void Admin::Delete(int ID)
{
    mainManager->DeleteEntry(ID);
    //mainManager.SaveEntriesToFile("TestingCases.csv");
}

void Admin::DeleteAll()
{
    mainManager->Delete_All();
    //mainManager.SaveEntriesToFile("TestingCases.csv");
}

void Admin::ViewAll()
{
    mainManager->ShowAll();
}

void Admin::ViewOne(int ID)
{
    mainManager->ShowEntry(ID);
}

void Admin::ViewOrderedByAge() {
    vector<pair<int, Entry>> ageVector;

    // Insert all entries into the vector
    for (auto& entry : mainManager->entries) {
        ageVector.push_back(make_pair(entry.second.age, entry.second));
    }

    // Insert all entries in the waiting list into the vector
    queue<Entry> tempWaitingList = mainManager->waitingList;
    while (!tempWaitingList.empty()) {
        ageVector.push_back(make_pair(tempWaitingList.front().age, tempWaitingList.front()));
        tempWaitingList.pop();
    }
    tempWaitingList.~queue();

    // Sort entries in ascending order of age
    std::sort(ageVector.begin(), ageVector.end(), [](auto& a, auto& b) {
        return a.second.age < b.second.age;
    });

    // Print entries in ascending order of age
    for (auto& entry : ageVector) {
        cout << "Name: " << entry.second.name << "\n"
             << "ID: " << entry.second.id << "\n"
             << "Government: " << entry.second.government << "\n"
             << "Age: " << entry.second.age << "\n"
             << "Gender: " << entry.second.gender << "\n"
             << "Vaccine Type: " << entry.second.vaccineType << "\n"
             << "Vaccinated First Dose: " << (entry.second.firstDose ? "Yes, on " + entry.second.firstDoseDate : "No") << "\n"
             << "Vaccinated Second Dose: " << (entry.second.secondDose ? "Yes, on " + entry.second.secondDoseDate : "No")
             << "\n\n";
    }
}

void Admin::ViewWaitingList()
{
    mainManager->ShowWaitingList();
}

void Admin::ViewDosesRecord() {
    char input;
    system("CLS");
    cout << "Enter 1 to view records of people who received one dose only \n"
         << "Enter 2 to view records of people who received both doses" << endl;
    cin >> input;
    vector<Entry> records;
    // Filter records based on the number of doses
    if (input == '1') {
        for (auto& entry : mainManager->entries) {
            if (entry.second.firstDose && !entry.second.secondDose) {
                records.push_back(entry.second);
            }
        }
        queue<Entry> tempList = mainManager->waitingList;
        while (!tempList.empty()) {
            if (tempList.front().firstDose && !tempList.front().secondDose) {
                records.push_back(tempList.front());
            }
            tempList.pop();
        }
        tempList.~queue();
    }
    else if (input == '2') {
        for (auto& entry : mainManager->entries) {
            if (entry.second.firstDose && entry.second.secondDose) {
                records.push_back(entry.second);
            }

        }

    }
    // Sort records by ID
    sort(records.begin(), records.end(), [](Entry a, Entry b) {
        return a.id < b.id;
    });
    // Print the filtered and sorted records
    for (auto record : records) {
        cout << "Name: " << record.name << "\n"
             << "ID: " << record.id << "\n"
             << "Government: " << record.government << "\n"
             << "Age: " << record.age << "\n"
             << "Gender: " << record.gender << "\n"
             << "Vaccine Type: " << record.vaccineType << "\n"
             << "Vaccinated First Dose: " << (record.firstDose ? "Yes, on " + record.firstDoseDate : "No") << "\n"
             << "Vaccinated Second Dose: " << (record.secondDose ? "Yes, on " + record.secondDoseDate : "No")
             << "\n\n";
    }
}

void Admin::ViewStatistics()
{
    int temp = 0;
    int allDoses = 0;
    int males = 0;
    int females = 0;
    char input;
    system("CLS");
    cout << "- Type F To see the The Amount of People Who Recieved The first Dose only  \n- Type B to see the Amount of People Who Recieved Both Doses \n- Type G To See the Amount of Males and Females on The System" << endl;
    cin >> input;
    //Function To See the Amount of People Who Recieved the First Dose Only
    if (input == 'F' || input == 'f')
    {

        queue<Entry> tempList = mainManager->waitingList;
        while (!tempList.empty()) {
            if (tempList.front().firstDose == true)
            {
                temp++;
            }
            tempList.pop();
        }
        tempList.~queue();
        cout << "The number of people that took the first dose only is: " << temp << endl;
        return;
    }
    //Function to see the Amount of People Who Recieved Both Doses
    else if (input == 'B' || input == 'b')
    {
        for (pair<int, Entry> entry : mainManager->entries) {
            if (entry.second.firstDose == true && entry.second.secondDose == true)
            {
                allDoses++;
            }
        }
        cout << "The number of people that took the two doses is: " << allDoses << endl;
        return;
    }
    //Function to See the Amount of Males and Females In the System
    else if (input == 'G' || input == 'g')
    {
        for (pair<int, Entry> entry : mainManager->entries) {
            if (entry.second.gender == 'M' || entry.second.gender == 'm')
            {
                males++;
            }
        }
        queue<Entry> tempList = mainManager->waitingList;
        while (!tempList.empty()) {
            if (tempList.front().gender == 'M' || tempList.front().gender == 'm')
            {
                males++;
            }
            tempList.pop();
        }
        tempList.~queue();
        for (pair<int, Entry> entry : mainManager->entries) {
            if (entry.second.gender == 'F' || entry.second.gender == 'f')
            {
                females++;
            }
        }
        queue<Entry> tempList2 = mainManager->waitingList;
        while (!tempList2.empty()) {
            if (tempList2.front().gender == 'F' || tempList2.front().gender == 'f')
            {
                females++;
            }
            tempList2.pop();
        }
        tempList2.~queue();
        int returnValues[2] = { males, females };
        cout << "The number of males is: " << males << endl << "The number of females is: " << females << endl;
        return;
    }
    //If the Character is wrong
    else
    {
        cout << "Please Re-Enter The Character Again";
    }

}
