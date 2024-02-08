// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <cstdio>
#include <string>
#include <vector>

using std::byte;

static const byte ESC{'H'};
static const byte SOF{0x10};

template<typename T>
void ProcessNextByte(byte b, T&& frameCompleted)
{
  static std::string frame{};
  static bool        inHeader{false};
  static bool        wasESC{false};
  static bool        lookingForSOF{false};

  if(inHeader) {
    if((ESC == b) && not wasESC) {
      wasESC = true;
      return;
    } else if(wasESC) {
      wasESC = false;

      if((SOF == b) || (ESC != b)) {
        // if b is not SOF discard the frame
        if(SOF == b) { frameCompleted(frame); }

        frame.clear();
        inHeader = false;
        return;
      }
    }

    frame += static_cast<char>(b);

  } else if((ESC == b) && !lookingForSOF) {
    lookingForSOF = true;
  } else if((SOF == b) && lookingForSOF) {
    inHeader      = true;
    lookingForSOF = false;
  } else {
    lookingForSOF = false;
  }
}

int main()
{
  const std::vector<byte> fakeBytes1{byte{0x70},
                                     byte{0x24},
                                     ESC,
                                     SOF,
                                     ESC,
                                     byte{'H'},
                                     byte{'e'},
                                     byte{'l'},
                                     byte{'l'},
                                     byte{'o'},
                                     ESC,
                                     SOF,
                                     byte{0x7},
                                     ESC,
                                     SOF};

  auto frameCompleteHandler = [](std::string& res) { printf("CCCB: %s\n", res.c_str()); };
  for(const auto& b : fakeBytes1) { ProcessNextByte(b, frameCompleteHandler); }

  puts("----------");

  const std::vector<byte> fakeBytes2{
    byte{'W'}, byte{'o'}, byte{'r'}, byte{'l'}, byte{'d'}, ESC, SOF, byte{0x99}};

  for(const auto& b : fakeBytes2) { ProcessNextByte(b, frameCompleteHandler); }
}