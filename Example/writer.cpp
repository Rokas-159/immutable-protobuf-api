#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
#include "message_parser.h"
using namespace std;

// This function fills in a Person message based on user input.
void PromptForAddress(tutorial::Person* person) {
  cout << "Enter person ID number: ";
  int id;
  cin >> id;
  person->set_id(id);
  cin.ignore(256, '\n');

  cout << "Enter name: ";
  getline(cin, *person->mutable_name());

  cout << "Enter email address (blank for none): ";
  string email;
  getline(cin, email);
  if (!email.empty()) {
    person->set_email(email);
  }

  while (true) {
    cout << "Enter a phone number (or leave blank to finish): ";
    string number;
    getline(cin, number);
    if (number.empty()) {
      break;
    }

    tutorial::Person::PhoneNumber* phone_number = person->add_phones();
    phone_number->set_number(number);

    cout << "Is this a mobile, home, or work phone? ";
    string type;
    getline(cin, type);
    if (type == "mobile") {
      phone_number->set_type(tutorial::Person::PHONE_TYPE_MOBILE);
    } else if (type == "home") {
      phone_number->set_type(tutorial::Person::PHONE_TYPE_HOME);
    } else if (type == "work") {
      phone_number->set_type(tutorial::Person::PHONE_TYPE_WORK);
    } else {
      cout << "Unknown phone type.  Using default." << endl;
    }
  }
}

vector<tutorial::AddressBook> ParseMultipleDelimitedMessages(istream& input) {
  vector<tutorial::AddressBook> messages;
  tutorial::AddressBook message;

  while (ParseDelimitedMessage(message, input)) {
    messages.push_back(message);
  }

  return messages;
}

bool WriteDelimitedMessage(const tutorial::AddressBook& message, ostream& output) {
  string serialized;
  if (!message.SerializeToString(&serialized)) {
    return false;
  }

  uint64_t size = serialized.size();
  output.write(reinterpret_cast<const char*>(&size), sizeof(size));
  output.write(serialized.data(), serialized.size());
  return output.good();
}

void WriteMultipleDelimitedMessages(const vector<tutorial::AddressBook>& messages, ostream& output) {
  for (const tutorial::AddressBook& message : messages) {
    WriteDelimitedMessage(message, output);
  }
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  vector<tutorial::AddressBook> messages;
  uint64_t message_index;

  {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found.  Creating a new file." << endl;
    }

    messages = ParseMultipleDelimitedMessages(input);

    cout << "Found " << messages.size() << " messages. Select which one to modify (" << messages.size() << " to append a new one): ";
    cout.flush();
    cin >> message_index;

    if (message_index < 0 || message_index > static_cast<int>(messages.size())) {
      cerr << "Message index out of bounds." << endl;
      return -1;
    } else if (message_index == static_cast<int>(messages.size())) {
      messages.emplace_back();
      cout << "Modifying a newly appended message at index " << message_index << "." << endl;
    } else {
      cout << "Modifying message at index " << message_index << "." << endl;
    }
  }

  // Add an address.
  PromptForAddress(messages[message_index].add_people());

  {
    // Write the new address book back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    
    WriteMultipleDelimitedMessages(messages, output);
  }

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}

// g++ writer.cpp addressbook.pb.cc -o writer -lprotobuf