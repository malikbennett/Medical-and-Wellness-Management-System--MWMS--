#pragma once

#include <User.h>

constexpr int EMPLOYEE_ID = 5;
constexpr int EMPLOYEE_NAME = 16;
constexpr int EMPLOYEE_GENDER = 64;
constexpr int EMPLOYEE_DOB = 10;
constexpr int EMPLOYEE_ADDRESS = 1;

struct EmployeeProfile;

class Employee : public User
{
public:
    Employee(UserDataBuffer *data, EmployeeProfile *userProfile);
    // Getters
    int getId() const;
    string getFirstName() const;
    string getMiddleName() const;
    string getLastName() const;
    Date getDob() const;
    Date getEmploymentDate() const;
    string getDepartment() const;
    string getGender() const;
    string getTrn() const;
    string getJobTitle() const;
    string getSupervisor() const;

private:
    int id;
    string firstName, middleName, lastName;
    Date dob, employmentDate;
    string department;
    string gender, trn, jobTitle, supervisor;
};
