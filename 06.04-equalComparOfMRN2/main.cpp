// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdint>

class MedicalRecordNumber {
public:
  MedicalRecordNumber() = default;
  explicit MedicalRecordNumber(uint64_t mrn)
  : mMRN{mrn}
  {}

  // #A The initial member functions
  bool operator==(const MedicalRecordNumber& other) const
  {
    return mMRN == other.mMRN;
  }

  bool operator!=(const MedicalRecordNumber& other) const
  {
    return !(*this == other);
  }

  // #B The additional overloads for uint64_t
  friend bool operator==(const MedicalRecordNumber& rec,
                         const uint64_t&            num)
  {
    return rec.mMRN == num;
  }

  friend bool operator!=(const MedicalRecordNumber& rec,
                         const uint64_t&            num)
  {
    return !(rec == num);
  }

  // #C The additional overloads with swapped arguments for  uint64_t
  friend bool operator==(const uint64_t&            num,
                         const MedicalRecordNumber& rec)
  {
    return (rec == num);
  }

  friend bool operator!=(const uint64_t&            num,
                         const MedicalRecordNumber& rec)
  {
    return !(rec == num);
  }

private:
  uint64_t mMRN;
};

int main()
{
  MedicalRecordNumber mrn0{};
  MedicalRecordNumber mrn1{3};

  const bool sameMRN              = mrn0 == mrn1;
  const bool differentMRN         = mrn0 != mrn1;
  const bool sameMRNasNumber      = 8 == mrn0;
  const bool sameMRNasNumberOther = mrn0 == 8;
}