// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdint>

class MedicalRecordNumber {
public:
  MedicalRecordNumber() = default;
  explicit MedicalRecordNumber(uint64_t mrn)
  : mMRN{mrn}
  {}

private:
  uint64_t mMRN;
};

int main()
{
  MedicalRecordNumber mrn0{};
  MedicalRecordNumber mrn1{3};
}