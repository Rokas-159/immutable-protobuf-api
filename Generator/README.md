# How to compile a proto file

Copy the Generator folder to protobuf/src/ and run this command:

```
bazelisk run //src/Generator:generator -- <path_to_proto_file>
```