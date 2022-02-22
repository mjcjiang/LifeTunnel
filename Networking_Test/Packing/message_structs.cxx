#include "message_structs.h"

unsigned int TestMessage_Packing(unsigned char *buf, const TestMessage* p) {
    unsigned int packsize = pack(buf, "Cgs", p->Field1, p->Field2, p->Field3);
    return packsize;
}

void TestMessage_Unpacking(unsigned char *buf, TestMessage* p) {
    unpack(buf, "Cg10s", &p->Field1, &p->Field2, p->Field3);
}

unsigned int VastMessage_Packing(unsigned char *buf, const VastMessage* p) {
    unsigned int packsize = pack(buf, "cgs", p->Field1, p->Field2, p->Field3);
    return packsize;
}

void VastMessage_Unpacking(unsigned char *buf, VastMessage* p) {
    unpack(buf, "cg20s", &p->Field1, &p->Field2, p->Field3);
}

