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

all: example

example: writer reader

writer: $(BIN_DIR) $(PROTOBUF_SRC:.proto=.pb.h,.pb.cc) $(WRITER_SRC:.cpp=.o)
	$(CXX) $(WRITER_SRC) $(PROTOBUF_SRC) $(CXXFLAGS) -o $(WRITER_TRG)

reader: $(BIN_DIR) $(PROTOBUF_SRC:.proto=.pb.h,.pb.cc) $(READER_SRC:.cpp=.o)
	$(CXX) $(READER_SRC) $(PROTOBUF_SRC) $(CXXFLAGS) -o $(READER_TRG)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.pb.h %.pb.cc : %.proto
	protoc -I=./ --cpp_out=./ $<

clean:
	rm -f *.o *.pb.* $(WRITER_TRG) $(READER_TRG)