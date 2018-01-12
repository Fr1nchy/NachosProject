#include "reseaufiable.h"
#include "sysdep.h"

ReseauFiable::ReseauFiable(){
	
}

ReseauFiable::Send(PacketHeader pktHdr, MailHeader mailHdr, const char* data){
	PostOffice::Send(pktHdr, mailHdr, data);
	StartTimer(TEMPO);
}

ReseauFiable::Receive(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){
	if(mailHdr->ACK == true)
		
	PostOffice::Receive(box, pktHdr, mailHdr, data);
}

ReseauFiable::StartTimer(unsigned int tempo){
	Delay(tempo);
}

ReseauFiable::~ReseauFiable(){

}