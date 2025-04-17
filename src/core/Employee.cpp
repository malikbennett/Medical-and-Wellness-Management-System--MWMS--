#include <UserManager.h>
#include <User.h>
#include <Employee.h>
#include <Helper.h>

Employee::Employee(UserDataBuffer *data) : User(data)
{
    this->id = stoi(data->ProfileRecords[1]);
    this->firstName = trimString(data->ProfileRecords[2]);
    this->middleName = trimString(data->ProfileRecords[3]);
    this->lastName = trimString(data->ProfileRecords[4]);
    this->dob = Date::toDate(data->ProfileRecords[5]);
    this->employmentDate = Date::toDate(data->ProfileRecords[6]);
    this->department = trimString(data->ProfileRecords[7]);
    this->gender = trimString(data->ProfileRecords[8]);
    this->trn = trimString(data->ProfileRecords[9]);
    this->jobTitle = trimString(data->ProfileRecords[10]);
    this->supervisor = trimString(data->ProfileRecords[11]);
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
