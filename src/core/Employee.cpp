#include <UserManager.h>
#include <User.h>
#include <Employee.h>

Employee::Employee(UserDataBuffer *data) : User(data)
{
    this->id = stoi(data->ProfileRecords[1]);
    this->firstName = data->ProfileRecords[2];
    this->middleName = data->ProfileRecords[3];
    this->lastName = data->ProfileRecords[4];
    this->dob = Date::toDate(data->ProfileRecords[5]);
    this->employmentDate = Date::toDate(data->ProfileRecords[6]);
    this->department = data->ProfileRecords[7];
    this->gender = data->ProfileRecords[8];
    this->trn = data->ProfileRecords[9];
    this->jobTitle = data->ProfileRecords[10];
    this->supervisor = data->ProfileRecords[11];
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
