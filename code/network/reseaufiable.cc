#include "post.h"
#include "sysdep.h"

ReseauFiable::ReseauFiable(NetworkAddress addr, double reliability, int nBoxes){
	PostOffice *postOffice = new PostOffice(addr, reliability, nBoxes);
	
}

ReseauFiable::Send(PacketHeader pktHdr, MailHeader mailHdr, const char* data){
	PostOffice::Send(pktHdr, mailHdr, data);
	for(int i = 0; i<MAXREEMISSIONS ; i++){
		//	StartTimer(TEMPO);
		//En attendant de trouver mieux
		Delay(TEMPO);
		//	if timeout
		//	resend
	}
}

ReseauFiable::ReceiveAck(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){

	//attente max d'un message = TEMPO*maxreemission
	//Si c'est atteint, on arrête de bloquer
	if(!PostOffice::IsThisMailboxEmpty(int box)){
		PostOffice::Receive(box, pktHdr, mailHdr, data);
		ASSERT(mailHdr->ACK == true);
		//timeroff	
	}
	else{
		//Delay()
		//yield() le thread courant
	}
}


ReseauFiable::Receive(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){
	//attente max d'un message = TEMPO*maxreemission
	//Si c'est atteint, on arrête de bloquer
	PostOffice::Receive(box, pktHdr, mailHdr, data);
	//renvoyer un accusé de réception
}

ReseauFiable::StartTimer(unsigned int tempo){
	Delay(tempo);
}

ReseauFiable::~ReseauFiable(){
	delete postOffice;

}