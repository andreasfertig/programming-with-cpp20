// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdint>

class MedicalRecordNumber {
public:
  MedicalRecordNumber() = default;
  explicit MedicalRecordNumber(uint64_t mrn)
  : mMRN{mrn}
  {}

  bool operator==(const MedicalRecordNumber& other) const
  {
    return other.mMRN == mMRN;
  }

  bool operator!=(const MedicalRecordNumber& other) const
  {
    return !(other == *this);
  }

private:
  uint64_t mMRN;
};

int main()
{
  MedicalRecordNumber mrn0{};
  MedicalRecordNumber mrn1{3};

  const bool sameMRN      = mrn0 == mrn1;
  const bool differentMRN = mrn0 != mrn1;
}