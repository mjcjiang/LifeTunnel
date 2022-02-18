#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

#include <nng/nng.h>
#include <nng/protocol/pipeline0/pull.h>
#include <nng/protocol/pipeline0/push.h>

using namespace std;

#define COMM_URL "ipc:///tmp/pipeline.ipc"

void fatal(const char *func, int rv)
{
    fprintf(stderr, "%s: %s\n", func, nng_strerror(rv));
    exit(1);
}

int write_netmsg(const char *url, char *msg)
{
    cout << "Enter: " << endl;
    int sz_msg = strlen(msg) + 1; // '\0' too
    cout << "msg size: " << sz_msg << endl;

    nng_socket sock;
    int rv;
    int bytes;

    if ((rv = nng_push0_open(&sock)) != 0) {
        fatal("nng_push0_open", rv);
    }

    if ((rv = nng_dial(sock, url, NULL, 0)) != 0) {
        fatal("nng_dial", rv);
    }
    
    if ((rv = nng_send(sock, msg, strlen(msg)+1, 0)) != 0) {
        fatal("nng_send", rv);
    }
    
    sleep(1); // wait for messages to flush before shutting down
    nng_close(sock);
    return (0);
}

/*
* This function fills in a Person message based on user input
*/
void PromptForAddress(tutorial::Person* person) {
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    while (true) {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        tutorial::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
    
        if (type == "mobile") {
            phone_number->set_type(tutorial::Person::MOBILE);
        } else if (type == "home") {
            phone_number->set_type(tutorial::Person::HOME);
        } else if (type == "work") {
            phone_number->set_type(tutorial::Person::WORK);
        } else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
}

/*
* marshal a addressbook for send
*/
int GenAddressBookForSend(std::string *buf) {
    tutorial::AddressBook address_book;

    PromptForAddress(address_book.add_people());

    if(!address_book.SerializeToString(buf)) {
        cerr << "Failed to write address book." << endl;
        return -1;
    }

    return 0;
}

int main(int argc, char **argv) {
    std::string msg;
    cout << "tag1" << endl;

    if (GenAddressBookForSend(&msg) != 0) {
        return -1;
    }

    cout << msg << endl;

    int size = 10 * 1024 * 1024;
    char *buffer = (char *)malloc(size);
    memset(buffer, 0x00, sizeof(size));

    
    memcpy(buffer, msg.c_str(), msg.size());
    write_netmsg(COMM_URL, buffer);
    
    free(buffer);

    return 0;
}