#include "post.h"
#include "sysdep.h"
#include "thread.h"
#include "system.h"

/*ReseauFiable::ReseauFiable(NetworkAddress addr, double reliability, int nBoxes){
	postOffice = new PostOffice(addr, reliability, nBoxes);
	
}*/

void ReseauFiable::Send(PacketHeader pktHdr, MailHeader mailHdr, const char* data){
	postOffice->Send(pktHdr, mailHdr, data);
	for(int i = 0; i<MAXREEMISSIONS ; i++){
		//	StartTimer(TEMPO);
		//if(AckRecieved)
		//	break;
		//else
		//Delay(TEMPO);
		//	if timeout
		//	resend
	//}
}

void ReseauFiable::ReceiveAck(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){

	//attente max d'un message = TEMPO*maxreemission
	//Si c'est atteint, on arrête de bloquer
	if(!postOffice->IsThisMailboxEmpty(box)){
		postOffice->Receive(box, pktHdr, mailHdr, data);
		if(mailHdr->ACK == true) return true;
		else return false;
		//timeroff	
	}
	else{
		//Delay(1);
		currentThread->Sleep();
		return false;
		//utilisation de std et chrono ?
		//std::this_thread::sleep_for(1);
		//yield() le thread courant
		//currentThread::Yield();
		//pthread_yield() ou this_thread::yield();
	}
}


void ReseauFiable::Receive(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){
	//attente max d'un message = TEMPO*maxreemission
	//Si c'est atteint, on arrête de bloquer
	postOffice->Receive(box, pktHdr, mailHdr, data);

	//renvoyer un accusé de réception
	PacketHeader ackPktHdr;
	MailHeader   ackMailHdr;
    ackPktHdr.to = pktHdr->from;
    ackMailHdr.to = mailHdr->from;
    ackMailHdr.length = 0;
	ackMailHdr.ACK =true;
	
	ReseauFiable::Send(ackPktHdr, ackMailHdr, "");
}

void ReseauFiable::StartTimer(unsigned int tempo){
	Delay(tempo);
}

PostOffice* ReseauFiable::getPostOffice(){
    return postOffice;
}

/*ReseauFiable::~ReseauFiable(){
	delete postOffice;

}*/