def my_proto_library(name, srcs):
    header_name = srcs[0].replace(".proto", ".mypb.h")
    native.genrule(
        name = name + "cc_gen",
        srcs = srcs,
        outs = [header_name],
        cmd = "./$(location //Generator:generator) $< $@",
        tools = ["//Generator:generator"],
    )

    native.cc_library(
        name = name,
        srcs = [],
        hdrs = [header_name]
    )