#include "core/Prescription.h"

void Prescription::approve() {
    isApproved = true;
}

bool Prescription::getApprovalStatus() const {
    return isApproved;
}


