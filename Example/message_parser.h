#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

bool ParseDelimitedMessage(tutorial::AddressBook& message, std::istream& input) {
  uint64_t size;
  
  if (!input.read(reinterpret_cast<char*>(&size), sizeof(size))) {
    return false;
  }

  std::string buffer(size, '\0');
  if (!input.read(&buffer[0], size)) {
    return false;
  }

  return message.ParseFromString(buffer);
}