// nettest.cc 
//	Test out message delivery between two "Nachos" machines,
//	using the Post Office to coordinate delivery.
//
//	Two caveats:
//	  1. Two copies of Nachos must be running, with machine ID's 0 and 1:
//		./nachos -m 0 -o 1 &
//		./nachos -m 1 -o 0 &
//
//	  2. You need an implementation of condition variables,
//	     which is *not* provided as part of the baseline threads 
//	     implementation.  The Post Office won't work without
//	     a correct implementation of condition variables.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "system.h"
#include "network.h"
#include "post.h"
#include "interrupt.h"

// Test out message delivery, by doing the following: 
//	1. send a message to the machine with ID "farAddr", at mail box #0
//	2. wait for the other machine's message to arrive (in our mailbox #0)
//	3. send an acknowledgment for the other machine's message
//	4. wait for an acknowledgement from the other machine to our 
//	    original message

void
MailTestClient(int farAddr)
{
    PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    ReseauFiable *reseauFiable = new ReseauFiable();

    const char *data = "Hello client!";
    char buffer[MaxMailSize];

    // construct packet, mail header for original message
    // To: destination machine, mailbox 0
    // From: our machine, reply to: mailbox 1
    outPktHdr.to = farAddr;     
    outMailHdr.to = 0;
    outMailHdr.from = 1;
    outMailHdr.length = strlen(data) + 1;

    // Send the first message
    reseauFiable->Send(outPktHdr, outMailHdr,  data); 
    fflush(stdout);

    // Wait for the ack from the other machine to the first message we sent.
    reseauFiable->Receive(1, &inPktHdr, &inMailHdr, buffer);
    printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
    fflush(stdout);
   
    // Then we're done!
    interrupt->Halt();
}

void
MailTestServeur(int farAddr)
{
    ReseauFiable *reseauFiable = new ReseauFiable();
    PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    const char *data = "Hello serveur!";
    char buffer[MaxMailSize];

    reseauFiable->Receive(1, &inPktHdr, &inMailHdr, buffer);
    printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);

    outPktHdr.to = farAddr;     
    outMailHdr.to = 0;
    outMailHdr.from = 1;
    outMailHdr.length = strlen(data) + 1;

    reseauFiable->Send(outPktHdr, outMailHdr,  data); 
    
    fflush(stdout);
    interrupt->Halt();
}


    // Test constitué de n machines reliées par un anneau logique
void
AnneauLogiqueTest(int farAddr){
    /*PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize];
    const char *data = "Jeton de 0";

    outPktHdr.to = farAddr;
    if (reseauFiable->getPostOffice()->GetNetworkAddress() == 0)
    {
        outMailHdr.to = 0;
        outMailHdr.from = 0;
        outMailHdr.length = strlen(data) + 1;

        // Envoyer le jeton
        reseauFiable->getPostOffice()->Send(outPktHdr, outMailHdr, data);
        printf("Sent \"%s\"\n", data);
        fflush(stdout);

        // Wait for the first message from the other machine
        reseauFiable->getPostOffice()->Receive(0, &inPktHdr, &inMailHdr, buffer);
        printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
        fflush(stdout);

    }else{
        // Wait for the first message from the other machine
        reseauFiable->getPostOffice()->Receive(0, &inPktHdr, &inMailHdr, buffer);
        printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
        fflush(stdout);

        Delay(5);

        // Transfer the message received
        outMailHdr.to = 0;
        outMailHdr.from = 0;
        outMailHdr.length = strlen(buffer) + 1;

         // Envoyer le jeton
        reseauFiable->getPostOffice()->Send(outPktHdr, outMailHdr, buffer);
        printf("Sent \"%s\"\n", buffer);
        fflush(stdout);

    }

    interrupt->Halt();*/
}
