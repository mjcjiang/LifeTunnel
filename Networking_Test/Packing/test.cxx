#include <iostream>
#include <string>
#include "message_structs.h"

using namespace std;

int main(int argc, char **argv) { 
    /*
    unsigned char buf[1024];
    memset(buf, 0x00, 1024);

    VastMessage msg;
    memset(&msg, 0x00, sizeof(VastMessage));

    msg.Field1 = 'c';
    msg.Field2 = 12.22;
    memcpy(msg.Field3, "yes, madam!", 11);
    
    unsigned int packsize = VastMessage_Packing(buf, &msg);
    cout << "packsize: " << packsize << endl;
    
    unsigned int packsize = pack(buf, "cgs", msg.Field1, msg.Field2, msg.Field3);
    cout << packsize << endl;

    VastMessage unpacked_msg;
    memset(&unpacked_msg, 0x00, sizeof(VastMessage));
    VastMessage_Unpacking(buf, &unpacked_msg);
    
    cout << unpacked_msg.Field1 << endl;
    cout << unpacked_msg.Field2 << endl;
    cout << string(unpacked_msg.Field3) << endl;
    */

    /*
     *float64_t packing and unpacking -- Success 
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
   
    /*
     * uint8_t, float64_t and char[20] packing and unpacking
     */
    float s = 3.141592, d = 2.122222;

    unsigned char buf[1024];
    memset(buf, 0x00, 1024);

    unsigned int packsize = pack(buf, "d", s);
    cout << "Pack size: " << packsize << endl;
    unpack(buf, "d", &d);
    printf("float before  : %f\n", s);
    printf("float after  : %f\n", d);
    return 0;
}