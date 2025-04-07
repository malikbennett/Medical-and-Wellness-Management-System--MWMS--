#include <Role.h>

Role::Role(int rNumber, const string &rName, const string &rLevel)
    : roleNumber(rNumber), roleName(rName), roleLevel(rLevel){};

map<string, int> Role::roleMap = {
    {"Admin", 1},
    {"Doctor", 2},
    {"Psychologist", 3},
    {"Dietitian", 4},
    {"Nurse", 5},
    {"Receptionist", 6},
    {"Patient", 7}};
