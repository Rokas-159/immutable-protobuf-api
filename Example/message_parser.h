#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

template <typename T>
bool ParseDelimitedMessage(T& message, std::istream& input) {
  uint64_t size = 0;

  for (int i = 7; i >= 0; i--) {
    char byte;
    if (!input.get(byte)) {
      return false;
    }

    size |= (static_cast<uint8_t>(byte) << i*8);
  }

  std::string buffer(size, '\0');
  if (!input.read(&buffer[0], size)) {
    return false;
  }

  return message.ParseFromString(buffer);
}