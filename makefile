# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -lprotobuf

# Source files
PROTOBUF_SRC = Example/addressbook.pb.cc
WRITER_SRC = Example/writer.cpp
READER_SRC = Example/reader.cpp

# Target files
BIN_DIR = build
WRITER_TRG = $(BIN_DIR)/writer
READER_TRG = $(BIN_DIR)/reader

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: example

example: writer reader

writer: $(BIN_DIR) $(WRITER_SRC) $(PROTOBUF_SRC)
	$(CXX) $(WRITER_SRC) $(PROTOBUF_SRC) $(CXXFLAGS) -o $(WRITER_TRG)

reader: $(BIN_DIR) $(READER_SRC) $(PROTOBUF_SRC)
	$(CXX) $(READER_SRC) $(PROTOBUF_SRC) $(CXXFLAGS) -o $(READER_TRG)
