#include "post.h"
#include "sysdep.h"

ReseauFiable::ReseauFiable(NetworkAddress addr, double reliability, int nBoxes){
	postOffice = new PostOffice(addr, reliability, nBoxes);
	
}

void ReseauFiable::Send(PacketHeader pktHdr, MailHeader mailHdr, const char* data){
	postOffice->Send(pktHdr, mailHdr, data);
	for(int i = 0; i<MAXREEMISSIONS ; i++){
		//	StartTimer(TEMPO);
		//En attendant de trouver mieux
		Delay(TEMPO);
		//	if timeout
		//	resend
	}
}

void ReseauFiable::ReceiveAck(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){

	//attente max d'un message = TEMPO*maxreemission
	//Si c'est atteint, on arrête de bloquer
	if(!postOffice->IsThisMailboxEmpty(box)){
		postOffice->Receive(box, pktHdr, mailHdr, data);
		ASSERT(mailHdr->ACK == true);
		//timeroff	
	}
	else{
		//Delay()
		//yield() le thread courant
	}
}


void ReseauFiable::Receive(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){
	//attente max d'un message = TEMPO*maxreemission
	//Si c'est atteint, on arrête de bloquer
	postOffice->Receive(box, pktHdr, mailHdr, data);
	//renvoyer un accusé de réception
}

void ReseauFiable::StartTimer(unsigned int tempo){
	Delay(tempo);
}

PostOffice* ReseauFiable::getPostOffice(){
    return postOffice;
}

ReseauFiable::~ReseauFiable(){
	delete postOffice;

}