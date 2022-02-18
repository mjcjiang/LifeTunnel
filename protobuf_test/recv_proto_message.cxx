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

/*
* Iterates though all people in the AddressBook and prints info about them.
*/
void ListPeople(const tutorial::AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const tutorial::Person& person = address_book.people(i);

    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.has_email()) {
      cout << "  E-mail address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); j++) {
      const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

      switch (phone_number.type()) {
        case tutorial::Person::MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case tutorial::Person::HOME:
          cout << "  Home phone #: ";
          break;
        case tutorial::Person::WORK:
          cout << "  Work phone #: ";
          break;
      }
      cout << phone_number.number() << endl;
    }
  }
}

/*
* unmarshal recved net buffer into a protobuff message and print out
*/
int unmarshal_message(const char *buff) {
    tutorial::AddressBook address_book;
    
    if(!address_book.ParseFromString(buff)) {
        cerr << "Failed to parse address book." << endl;
        return -1;
    }

    ListPeople(address_book);
    return 0;
}

/*
* create a node which recv message on a specific url
*/
int recv_loop(const char *url)
{
    nng_socket sock;
    int rv;

    if ((rv = nng_pull0_open(&sock)) != 0) {
            fatal("nng_pull0_open", rv);
    }
    
    if ((rv = nng_listen(sock, url, NULL, 0)) != 0) {
            fatal("nng_listen", rv);
    }
        
    for (;;) {
        char *buf = NULL;
        size_t sz;
        if ((rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC)) != 0) {
            fatal("nng_recv", rv);
        }
            
        unmarshal_message(buf);
        nng_free(buf, sz);
    }
}

int main(int argc, char **argv)
{
    return (recv_loop(COMM_URL));
}
