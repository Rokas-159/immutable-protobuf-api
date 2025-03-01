# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -O2 -lbenchmark -lpthread

# Source files
MY_PROTOBUF_SRC = graph.mypb.h

MY_TESTER_SRC = mytester.cpp

# Target files
BIN_DIR = build
MY_TESTER_TRG = $(BIN_DIR)/mytester
OFFICIAL_TESTER_TRG = $(BIN_DIR)/officialtester

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: mytester

mytester: $(BIN_DIR) $(MY_PROTOBUF_SRC:.proto=.mypb.h)
	$(CXX) $(MY_TESTER_SRC) $(CXXFLAGS) -o $(MY_TESTER_TRG)

%.mypb.h : %.proto # Replace with paths to the rule and .proto file
	bazelisk run //src/ProtocolBuffers/Generator:generator -- ~/protobuf/src/ProtocolBuffers/Tester/graph.proto

clean:
	rm -f *.o *.pb.* *.mypb.* $(MY_TESTER_TRG) $(OFFICIAL_TESTER_TRG)