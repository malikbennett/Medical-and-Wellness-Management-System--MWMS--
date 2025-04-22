#include <Employee.h>
#include <Helper.h>

Employee::Employee(User &data) : User(data)
{
    auto pR = data.getProfileRecords();
    this->id = stoi(pR[1]);
    this->firstName = trimString(pR[2]);
    this->middleName = trimString(pR[3]);
    this->lastName = trimString(pR[4]);
    this->dob = Date::toDate(pR[5]);
    this->employmentDate = Date::toDate(pR[6]);
    this->department = trimString(pR[7]);
    this->gender = trimString(pR[8]);
    this->trn = trimString(pR[9]);
    this->jobTitle = trimString(pR[10]);
    this->supervisor = trimString(pR[11]);
};

int Employee::getId() const { return id; }
string Employee::getFirstName() const { return firstName; }
string Employee::getMiddleName() const { return middleName; }
string Employee::getLastName() const { return lastName; }
Date Employee::getDob() const { return dob; }
Date Employee::getEmploymentDate() const { return employmentDate; }
string Employee::getDepartment() const { return department; }
string Employee::getGender() const { return gender; }
string Employee::getTrn() const { return trn; }
string Employee::getJobTitle() const { return jobTitle; }
string Employee::getSupervisor() const { return supervisor; }
