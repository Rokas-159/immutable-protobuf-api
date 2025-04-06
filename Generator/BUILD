cc_binary(
    name="generator",
    srcs=["generator.cc"],
    deps = [
        "@protobuf//src/google/protobuf",
		"@protobuf//src/google/protobuf/compiler:importer",
        "@abseil-cpp//absl/strings",
    ],
    visibility=["//visibility:public"],
)
