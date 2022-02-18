g++ recv_proto_message.cxx addressbook.pb.cc -lprotobuf -lnng -lpthread -o recv_proto_message
g++ write_proto_message.cxx addressbook.pb.cc -lprotobuf -lnng -lpthread -o write_proto_message