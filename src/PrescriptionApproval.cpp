#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "core/Prescription.h"

using namespace std;

vector<Prescription> prescriptions;

void loadPrescriptions(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No existing prescription file found.\n";
        return;
    }

    while (!inFile.eof()) {
        Prescription p;
        p.loadFromFile(inFile);
        if (inFile) prescriptions.push_back(p);
    }

    inFile.close();
}

void savePrescriptions(const string& filename) {
    ofstream outFile(filename);
    for (const auto& p : prescriptions) {
        p.saveToFile(outFile);
    }
    outFile.close();
}

void showPrescriptions() {
    for (size_t i = 0; i < prescriptions.size(); ++i) {
        cout << i + 1 << ". Prescription #" << prescriptions[i].getPrescriptionNumber()
             << " | Approved: " << (prescriptions[i].getApprovalStatus() ? "Yes" : "No") << "\n";
    }
}

void approvePrescription() {
    int index;
    showPrescriptions();
    cout << "Enter prescription number to approve: ";
    cin >> index;
    if (index >= 1 && index <= prescriptions.size()) {
        prescriptions[index - 1].approve();
        cout << "Prescription approved!\n";
    } else {
        cout << "Invalid selection.\n";
    }
}

int main() {
    const string filename = "prescriptions.txt";

    loadPrescriptions(filename);

    int choice;
    do {
        cout << "\n--- MWMS Prescription Panel ---\n";
        cout << "1. View Prescriptions\n";
        cout << "2. Approve Prescription\n";
        cout << "3. Save Prescriptions to File\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: showPrescriptions(); break;
            case 2: approvePrescription(); break;
            case 3: savePrescriptions(filename); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }

    } while (choice != 4);

    return 0;
}
