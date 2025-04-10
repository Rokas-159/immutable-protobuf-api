#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

std::string CppType(const google::protobuf::FieldDescriptor* field) {
    switch (field->cpp_type()) {
        case google::protobuf::FieldDescriptor::CPPTYPE_STRING:
            return "std::string";
        case google::protobuf::FieldDescriptor::CPPTYPE_INT32:
            return "int32_t";
        case google::protobuf::FieldDescriptor::CPPTYPE_INT64:
            return "int64_t";
        case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT:
            return "float";
        case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE:
            return "double";
        case google::protobuf::FieldDescriptor::CPPTYPE_BOOL:
            return "bool";
        case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE:
            return std::string(field->message_type()->name());
        default:
            std::abort();
    }
}

bool IsMutable(const google::protobuf::FieldDescriptor* field) {
    return field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING || field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE;
}

void GenerateIncludes(std::ostream& out) {
    out << "#include <string>\n";
    out << "#include <memory>\n";
    out << "#include <vector>\n";
    out << "\n";
}

void GenerateStruct(const google::protobuf::Descriptor* file_descriptor, std::ostream& out) {
    out << "struct " << file_descriptor->name() << "Internal {\n";
    for (int i = 0; i < file_descriptor->field_count(); i++) {
        const google::protobuf::FieldDescriptor* field = file_descriptor->field(i);
        if (field->is_repeated()) {
            out << "\tstd::vector<" << CppType(field) << "> " << field->name() << ";\n";
        } else {
            out << "\t" << CppType(field) << " " << field->name() << ";\n";
        }
    }
    out << "};\n\n";
}

void GenerateRepeatedSize(const google::protobuf::FieldDescriptor* field, std::ostream& out) {
    out << "size_t " << field->name() << "_size() const { ";
    out << "return data->" << field->name() << ".size(); ";
    out << "}\n";
}

void GenenerateRepeatedAdder(const google::protobuf::FieldDescriptor* field, std::ostream& out) {
    out << "void add_" << field->name() << "(" << CppType(field) << " value) { ";
    out << "data->" << field->name() << ".push_back(value); ";
    out << "}\n";
}

void GenerateRepeatedEraser(const google::protobuf::FieldDescriptor* field, std::ostream& out) {
    out << "void erase_" << field->name() << "(size_t index) { ";
    out << "data->" << field->name() << ".erase(data->" << field->name() << ".begin() + index); ";
    out << "}\n";
}

void GenerateMutable(const google::protobuf::FieldDescriptor* field, std::ostream& out) {
    if (field->is_repeated()) {
        out << CppType(field) << "* mutable_" << field->name() << "(size_t index) { ";
        out << "return &data->" << field->name() << "[index]; ";
        out << "}\n";
    } else {
        out << CppType(field) << "* mutable_" << field->name() << "() { ";
        out << "return &data->" << field->name() << "; ";
        out << "}\n";
    }
}

void GenerateSetter(const google::protobuf::FieldDescriptor* field, std::ostream& out) {
    if (field->is_repeated()) {
        out << "void set_" << field->name() << "(size_t index, " << CppType(field) << " value) { ";
        out << "data->" << field->name() << "[index] = value; ";
        out << "}\n";
    } else {
        out << "void set_" << field->name() << "(" << CppType(field) << " value) { ";
        out << "data->" << field->name() << " = value; ";
        out << "}\n";
    }
}

void GenerateGetter(const google::protobuf::FieldDescriptor* field, std::ostream& out) {
    if (field->is_repeated()) {
        out << CppType(field) << " get_" << field->name() << "(size_t index) const { ";
        out << "return data->" << field->name() << "[index]; ";
        out << "}\n";
    } else {
        out << CppType(field) << " get_" << field->name() << "() const { ";
        out << "return data->" << field->name() << "; ";
        out << "}\n";
    }
}

void GenerateBuilder(const google::protobuf::Descriptor* file_descriptor, std::ostream& out) {
    out << "\tpublic:\n";
    out << "\tclass Builder {\n";
    out << "\t\tpublic:\n";
    out << "\t\tBuilder() : data(std::make_unique<" << file_descriptor->name() << "Internal>()) {}\n";
    out << "\n";

    for (int i = 0; i < file_descriptor->field_count(); i++) {
        const google::protobuf::FieldDescriptor* field = file_descriptor->field(i);
        out << "\t\t"; GenerateSetter(field, out);
        if (IsMutable(field)) {
            out << "\t\t"; GenerateMutable(field, out);
        }
        if (field->is_repeated()) {
            out << "\t\t"; GenenerateRepeatedAdder(field, out);
            out << "\t\t"; GenerateRepeatedEraser(field, out);
        }
        out << "\n";
    }

    out << "\n";

    for (int i = 0; i < file_descriptor->field_count(); i++) {
        const google::protobuf::FieldDescriptor* field = file_descriptor->field(i);
        out << "\t\t"; GenerateGetter(field, out);
        if (field->is_repeated()) {
            out << "\t\t"; GenerateRepeatedSize(field, out);
        }
    }

    out << "\n";

    out << "\t\t" << file_descriptor->name() << " Build() && { return " << file_descriptor->name() << "(std::move(data)); }\n";

    out << "\n";

    out << "\t\tprivate:\n";
    out << "\t\tstd::unique_ptr<" << file_descriptor->name() << "Internal> data;\n";
    out << "\t};\n";
}

void GenerateClass(const google::protobuf::Descriptor* file_descriptor, std::ostream& out) {
    out << "class " << file_descriptor->name() << " {\n";
    GenerateBuilder(file_descriptor, out);
    out << "\n";
    out << "\t" << file_descriptor->name() << "(): data(std::make_shared<" << file_descriptor->name() << "Internal>()) {}\n";
    out << "\n";

    for (int i = 0; i < file_descriptor->field_count(); i++) {
        const google::protobuf::FieldDescriptor* field = file_descriptor->field(i);
        out << "\t"; GenerateGetter(field, out);
        if (field->is_repeated()) {
            out << "\t"; GenerateRepeatedSize(field, out);
        }
    }

    out << "\n";

    out << "\tprivate:\n";
    out << "\t" << file_descriptor->name() << "(std::unique_ptr<" << file_descriptor->name() << "Internal> data): data(std::move(data)) {}\n";
    out << "\tstd::shared_ptr<" << file_descriptor->name() << "Internal> data;\n";

    out << "};\n\n";
}

void GenerateHeader(const google::protobuf::Descriptor* descriptor, std::ostream& out) {
    GenerateStruct(descriptor, out);
    GenerateClass(descriptor, out);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <proto_file> <output_file>" << std::endl;
        return 1;
    }

    std::string src_file = argv[1];
    std::string dst_file = argv[2];

    google::protobuf::compiler::DiskSourceTree source_tree;
    const char* current_dir = getenv("PWD");
    source_tree.MapPath("", current_dir ? current_dir : "/");

    google::protobuf::compiler::Importer importer(&source_tree, nullptr);
    const google::protobuf::FileDescriptor* file_descriptor = importer.Import(src_file);

    if (!file_descriptor) {
        std::cerr << "Failed to parse .proto file: " << src_file << std::endl;
        return 1;
    }

    std::cout << "Successfully parsed .proto file: " << src_file << std::endl;

    std::string input = argv[1];
    std::ofstream out(dst_file);

    GenerateIncludes(out);
    for (int i = 0; i < file_descriptor->message_type_count(); i++) {
        const google::protobuf::Descriptor* descriptor = file_descriptor->message_type(i);
        GenerateHeader(descriptor, out);
    }

    return 0;
}
