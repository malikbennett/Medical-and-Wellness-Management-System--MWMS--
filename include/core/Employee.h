#pragma once

#include <User.h>
#include <string>
#include <Helper.h>

class Employee : public User
{
public:
    Employee(User &data);
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
