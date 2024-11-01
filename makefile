# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -lprotobuf

# Source files
EXAMPLE_DIR = Example
ADDRESSBOOK_SRC = $(EXAMPLE_DIR)/addressbook.proto

PROTOBUF_SRC = $(EXAMPLE_DIR)/addressbook.pb.cc
WRITER_SRC = $(EXAMPLE_DIR)/writer.cpp
READER_SRC = $(EXAMPLE_DIR)/reader.cpp

# Target files
BIN_DIR = build
WRITER_TRG = $(BIN_DIR)/writer
READER_TRG = $(BIN_DIR)/reader

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: fullexample

fullexample: addressbook example

addressbook: $(ADDRESSBOOK_SRC)
	protoc -I=$(EXAMPLE_DIR) --cpp_out=$(EXAMPLE_DIR) $(ADDRESSBOOK_SRC)

example: writer reader

writer: $(BIN_DIR) $(WRITER_SRC) $(PROTOBUF_SRC)
	$(CXX) $(WRITER_SRC) $(PROTOBUF_SRC) $(CXXFLAGS) -o $(WRITER_TRG)

reader: $(BIN_DIR) $(READER_SRC) $(PROTOBUF_SRC)
	$(CXX) $(READER_SRC) $(PROTOBUF_SRC) $(CXXFLAGS) -o $(READER_TRG)
