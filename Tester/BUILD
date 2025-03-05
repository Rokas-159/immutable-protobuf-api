load("@protobuf//bazel:proto_library.bzl", "proto_library")
load("@protobuf//bazel:cc_proto_library.bzl", "cc_proto_library")
load("//Generator:mypb.bzl", "my_proto_library")

proto_library(
    name = "graph_proto",
    srcs = ["graph.proto"],
)

cc_proto_library(
    name = "graph_cc_proto",
    deps = [":graph_proto"],
)

my_proto_library(
    name = "graph_my_proto",
    srcs = ["graph.proto"],
)

cc_binary(
    name="officialtester",
    srcs=["officialtester.cpp"],
    deps = [
        "@protobuf//src/google/protobuf",
        "@google_benchmark//:benchmark",
        ":graph_cc_proto",
    ],
)

cc_binary(
    name="mytester",
    srcs=["mytester.cpp"],
    deps = [
        "@protobuf//src/google/protobuf",
        "@google_benchmark//:benchmark",
        ":graph_my_proto",
    ],
)