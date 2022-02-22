#include <iostream>
#include <string>
#include "message_structs.h"

using namespace std;

int main(int argc, char **argv) { 
    unsigned char buf[1024];
    memset(buf, 0x00, 1024);

    VastMessage msg;
    memset(&msg, 0x00, sizeof(VastMessage));

    msg.Field1 = 'c';
    msg.Field2 = 12.22;
    memcpy(msg.Field3, "yes, madam!", 11);

    /*
    unsigned int packsize = VastMessage_Packing(buf, &msg);
    cout << "packsize: " << packsize << endl;
    */
    unsigned int packsize = pack(buf, "cgs", msg.Field1, msg.Field2, msg.Field3);
    cout << packsize << endl;

    /*
    VastMessage unpacked_msg;
    memset(&unpacked_msg, 0x00, sizeof(VastMessage));
    VastMessage_Unpacking(buf, &unpacked_msg);
    
    cout << unpacked_msg.Field1 << endl;
    cout << unpacked_msg.Field2 << endl;
    cout << string(unpacked_msg.Field3) << endl;
    */

    /*
    float64_t x = 12.22;
    unsigned char buf[1024];

    uint64_t coded = pack754_64(x);
    cout << coded << endl;

    float64_t y;
    y = unpack754_64(coded);
    cout << y << endl;
    */

    return 0;
}