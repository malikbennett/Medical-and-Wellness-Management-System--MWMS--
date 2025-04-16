#include <UserManager.h>
#include <User.h>
#include <Employee.h>

Employee::Employee(UserDataBuffer *data, EmployeeProfile *userProfile) : User(data)
{
    this->id = stoi(userProfile->records[0]);
    this->firstName = userProfile->records[1];
    this->middleName = userProfile->records[2];
    this->lastName = userProfile->records[3];
    this->dob = Date::toDate(userProfile->records[4]);
    this->employmentDate = Date::toDate(userProfile->records[5]);
    this->department = userProfile->records[6];
    this->gender = userProfile->records[7];
    this->trn = userProfile->records[8];
    this->jobTitle = userProfile->records[9];
    this->supervisor = userProfile->records[10];
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
