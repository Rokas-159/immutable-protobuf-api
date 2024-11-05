# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -lprotobuf

# Source files
ADDRESSBOOK_SRC = addressbook.proto

PROTOBUF_SRC = addressbook.pb.cc
WRITER_SRC = writer.cpp
READER_SRC = reader.cpp

# Target files
BIN_DIR = build
WRITER_TRG = $(BIN_DIR)/writer
READER_TRG = $(BIN_DIR)/reader

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: fullexample

fullexample: addressbook example

addressbook: $(ADDRESSBOOK_SRC)
	protoc -I=./ --cpp_out=./ $(ADDRESSBOOK_SRC)

example: writer reader

writer: $(BIN_DIR) $(WRITER_SRC) $(PROTOBUF_SRC)
	$(CXX) $(WRITER_SRC) $(PROTOBUF_SRC) $(CXXFLAGS) -o $(WRITER_TRG)

reader: $(BIN_DIR) $(READER_SRC) $(PROTOBUF_SRC)
	$(CXX) $(READER_SRC) $(PROTOBUF_SRC) $(CXXFLAGS) -o $(READER_TRG)
