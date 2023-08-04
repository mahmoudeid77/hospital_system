#include <iostream>
#include <queue>
#include <string>
using namespace std;


const int NUM_SPECIALIZATIONS = 20;
const int MAX_PATIENTS = 5;

struct Patient {
    string name;
    bool urgent;
};
queue<Patient> specializations[NUM_SPECIALIZATIONS];//here each element of the array is a queue that
// stores elements of type Patient. The size of the array is determined by the value of
//the constant NUM_SPECIALIZATIONS.


void addPatient() {
    int spec;
    cout << "Enter the requested specialization (1-20): ";
    cin >> spec;
    if (spec < 1 || spec > NUM_SPECIALIZATIONS) {
        cout << "Invalid specialization." << endl;
        return;
    }
    spec--; // Convert to 0-indexed
    //to make sure you will exit the progarm if you have enough patients in spec
    if (specializations[spec].size() == MAX_PATIENTS) {
        cout << "Sorry, there are already 5 patients waiting for this specialization." << endl;
        return;
    }
    Patient p;
    cout << "Enter the patient's name: ";
    cin >> p.name;
    cout << "Enter the patient's status (0 = regular, 1 = urgent): ";
    cin >> p.urgent;
    if (p.urgent) {
        // Add to front of queue
        queue<Patient> temp;
        temp.push(p);
        while (!specializations[spec].empty()) {//make the urgent in the front
            temp.push(specializations[spec].front());
            specializations[spec].pop();
        }
        specializations[spec] = temp;
    } else {
        // Add to end of queue if he is regular

        specializations[spec].push(p);
    }
}

void printPatients() {
    for (int i = 0; i < NUM_SPECIALIZATIONS; i++) {
        if (!specializations[i].empty()) {
            cout << "Specialization " << i+1 << ":" << endl;
            queue<Patient> temp = specializations[i];
            while (!temp.empty()) {
                Patient p = temp.front();
                temp.pop();
                cout << "  - " << p.name << " (" << (p.urgent ? "urgent" : "regular") << ")" << endl;
            }
        }
    }
}

void pickupPatient() {
    int spec;
    cout << "Enter the requested specialization (1-20): ";
    cin >> spec;
    if (spec < 1 || spec > NUM_SPECIALIZATIONS) {
        cout << "Invalid specialization." << endl;
        return;
    }
    spec--; // Convert to 0-indexed
    if (specializations[spec].empty()) {
        cout << "There are no patients waiting for this specialization." << endl;
        return;
    }
    Patient p = specializations[spec].front();
    specializations[spec].pop();
    cout << p.name << ", please go with the doctor." << endl;
}



int main() {


    int choice;
    do {
        cout << "1. Add patient" << endl;
        cout << "2. Print patients" << endl;
        cout << "3. Doctor pickup patient" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                printPatients();
                break;
            case 3:
                pickupPatient();
                break;
            case 4:
                break; // Quit
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    } while (choice != 4);
    return 0;
}
