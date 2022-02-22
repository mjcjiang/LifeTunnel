import sys
import getopt
import json
import os

packing_dict = {
    "int8_t": "c",    #signed int8_t
    "uint8_t": "C",   #unsigned int8_t
    "int16_t": "h",   #signed int16_t
    "uint16_t": "H",  #unsigned int16_t
    "float16_t": "f", #half-precision float number
    "int32_t": "l",   #signed int32_t
    "uint32_t": "L",  #unsigned int32_t
    "float32_t": "d", #float32
    "int64_t": "q",   #signed int64_t
    "uint64_t": "Q",  #unsigned int64_t
    "float64_t": "g", #float64
    "char": "s",      #for string
}

def help():
    print("Usage:")
    print("  python struct_code_gen.py -i your_path_if_struct_config_file")

def build_c_struct_from_config_info(info):
    res = ""
    res += "// " + info["Comment"] + "\n"
    res += "struct " + info["StructName"] + " {" + "\n"
    for fieldinfo in info["Fields"]:
        if fieldinfo["Type"] == "char":
            res += "    " + "char" + "\t" + fieldinfo["Name"] + "[" + fieldinfo["ByteLen"] + "];" + "\n"
        else:
            res += "    " + fieldinfo["Type"] + "\t" + fieldinfo["Name"] + ";\n"
    res += "};\n"
    return res

def gen_packing_format_str(info):
    format_str = ""
    for fieldinfo in info["Fields"]:
        field_type = fieldinfo["Type"]
        if field_type not in packing_dict:
            raise Exception("wrong field type.")
        else:
            format_str += packing_dict[field_type]
    return "\"" + format_str + "\""

def gen_unpacking_format_str(info):
    format_str = ""
    for fieldinfo in info["Fields"]:
        field_type = fieldinfo["Type"]
        if field_type not in packing_dict:
            raise Exception("wrong field type.")
        else:
            if field_type == "char":
                format_str += fieldinfo["ByteLen"]
            format_str += packing_dict[field_type]
    return "\"" + format_str + "\""

def gen_packing_function_signature(info):
    res = ""
    res += "unsigned int " + info["StructName"] + "_Packing(unsigned char *buf, const " + info["StructName"] + "* p)"
    return res

def gen_unpacking_function_signature(info):
    res = ""
    res += "void " + info["StructName"] + "_Unpacking(unsigned char *buf, " + info["StructName"] + "* p)"
    return res

def build_packing_function_from_config_info(info):
    res = ""
    res += gen_packing_function_signature(info) + " {" + "\n"
    packing_format_str = gen_packing_format_str(info) #generate packing format string
    res += "    unsigned int packsize = pack(buf, " + packing_format_str + ","
    for fieldinfo in info["Fields"]:
        if fieldinfo["Type"] == "char":
            res += " p->" + fieldinfo["Name"] + ","
        else:
            res += " p->" + fieldinfo["Name"] + ","
    res = res[0:-1]
    res += ");\n"
    res += "    return packsize;\n"
    res += "}\n"
    return res

def build_unpacking_function_from_config_info(info):
    res = ""
    res += gen_unpacking_function_signature(info) + " {" + "\n"
    unpacking_format_str = gen_unpacking_format_str(info) #generate packing format string
    res += "    unpack(buf, " + unpacking_format_str + ","
    for fieldinfo in info["Fields"]:
        if fieldinfo["Type"] == "char":
            res += " p->" + fieldinfo["Name"] + ","
        else:
            res += " &p->" + fieldinfo["Name"] + ","
    res = res[0:-1]
    res += ");\n"
    res += "}\n"
    return res

if __name__ == "__main__":
    argv = sys.argv[1:]  
    opts, args = getopt.getopt(argv, "i:o:h", ["input_config =",])
    
    c_code_output_path = "."

    for opt, arg in opts:
        if opt in ['-i', '--input_config']:
            structs_config_path = arg
        if opt in ['-o', '--output_path']:
            c_code_output_path = arg
        if opt in ['-h', '--help']:
            help()
            exit()

    cxx_header_file = os.path.join(c_code_output_path, "message_structs.h")
    cxx_code_file = os.path.join(c_code_output_path, "message_structs.cxx")

    with open(structs_config_path) as f, open(cxx_header_file, "w") as hf, open(cxx_code_file, "w") as cf:
        c = json.load(f)
        hf.write("#include \"message_packing.h\"\n\n")
        cf.write("#include \"message_structs.h\"\n\n")
        for info in c["Structs"]:
            hf.write(build_c_struct_from_config_info(info) + "\n")
            hf.write(gen_packing_function_signature(info) + ";" + "\n")
            hf.write(gen_unpacking_function_signature(info) + ";" + "\n\n")

            cf.write(build_packing_function_from_config_info(info) + "\n")
            cf.write(build_unpacking_function_from_config_info(info) + "\n")