#include "message_packing.h"

// This is a message structure for testing
struct TestMessage {
    uint8_t	Field1;
    float64_t	Field2;
    char	Field3[10];
};

unsigned int TestMessage_Packing(unsigned char *buf, const TestMessage* p);
void TestMessage_Unpacking(unsigned char *buf, TestMessage* p);

// This is a message structure for testing
struct VastMessage {
    int8_t	Field1;
    float64_t	Field2;
    char	Field3[20];
};

unsigned int VastMessage_Packing(unsigned char *buf, const VastMessage* p);
void VastMessage_Unpacking(unsigned char *buf, VastMessage* p);

