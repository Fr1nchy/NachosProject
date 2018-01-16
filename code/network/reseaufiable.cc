#include "post.h"
#include "sysdep.h"
#include "thread.h"
#include "system.h"
#include <string.h>

#define divRoundUp(n,s)    (((n) / (s)) + ((((n) % (s)) > 0) ? 1 : 0))


int
ReseauFiable::Send(PacketHeader pktHdr, MailHeader mailHdr, const char* data){ //Donnée
    char buffer[MaxMailSize];

    mailHdr.length = strlen(data) + 1;
    int res = divRoundUp(mailHdr.length,MaxMailSize);

    if(isExitACK()){
        mailHdr.Num_ACK = 0;
        mailHdr.ACK = FALSE;
        mailHdr.FIN = FALSE;
    }else{
        mailHdr.Num_ACK = currentACK + 1;
        mailHdr.ACK = FALSE;
        mailHdr.FIN = FALSE;
    }
    
    int i = 0;
    int j = 0;
    unsigned cpt = 0;
    unsigned taille = MaxMailSize;
printf("sdata: %s\n",data);
printf("sparametre b:%s,pk.to:%d,m.to:%d,m.from:%d,m.length:%d\n",data,pktHdr.to,mailHdr.to,mailHdr.from,mailHdr.length);

    while(i < res && (j!=MAXREEMISSIONS)){
        if((taille+cpt)>mailHdr.length) taille = mailHdr.length-cpt; 

        memcpy(buffer,data+(taille*i),taille);
        postOffice->Send(pktHdr, mailHdr, buffer);

printf("ssend: %s\n",buffer);
        while(j<MAXREEMISSIONS && !AckFinReceived(mailHdr.from,taille+cpt==mailHdr.length)){
            Delay(TEMPO);
            postOffice->Send(pktHdr, mailHdr, buffer);
printf("ssend: %s\n",buffer);
printf("j:%d ",j);
            j++;
        }
printf("\n");
        strcpy(buffer,"");
        if(j!=MAXREEMISSIONS){
printf("sACK OK\n");
            mailHdr.Num_ACK = currentACK+1;
            currentACK++;
            cpt = taille;
        }
        i++;
    }
printf("sACK FIN:%d==%d && %d!=%d \n",i,res,j,MAXREEMISSIONS);
    ASSERT((i == res)&&(j!=MAXREEMISSIONS));
    
    mailHdr.Num_ACK = currentACK +1 ;
    mailHdr.ACK = TRUE;
    mailHdr.FIN = TRUE;
    postOffice->Send(pktHdr, mailHdr,"");
    
    return 0;  
}

bool
ReseauFiable::AckFinReceived(int box,bool b){
    PacketHeader inPktHdr;
    MailHeader inMailHdr;
    char * data = NULL;
    inMailHdr.Num_ACK = -1;

printf("ACK_FIN\n");
    while(!postOffice->IsThisMailboxEmpty(box) && ( (currentACK+1) != inMailHdr.Num_ACK) ){
        postOffice->Receive(box, &inPktHdr, &inMailHdr, data);//erreur allocation
    }
printf("a: %s\n",data);
    if(currentACK+1 == inMailHdr.Num_ACK){
        if(inMailHdr.FIN && b){
            printf("b\n");
            return TRUE;
        }else{
            printf("c\n");
            return inMailHdr.ACK;
        }
    }else{
        printf("d\n");
        return FALSE;
    }
}

int
ReseauFiable::Receive(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){
    PacketHeader ackPktHdr;
	MailHeader   ackMailHdr;
           
    int res = 1;
    int i = 0;
    int j = 0;
    unsigned cpt = 0;
printf("rDEB\n");
    ackMailHdr.FIN = FALSE;
    data = (char*) malloc(sizeof(char)*MaxMailSize);
printf("rparametre box:%d\n",box);
    while((i < res) &&(!ackMailHdr.FIN)){
        postOffice->Receive(box, pktHdr, mailHdr, data+(MaxMailSize*(res-1))); // tempo
printf("rdata: %s\n",data);
        if(cpt==0){
            res = divRoundUp(mailHdr->length,MaxMailSize);
            data = (char *)realloc(data,mailHdr->length);
        }

        cpt = strlen(data) + cpt;

        if(isExitACK()){
            currentACK = mailHdr->Num_ACK -1;
        }else if((currentACK+1) == mailHdr->Num_ACK ){
printf("rACK\n");
           ackPktHdr.to = pktHdr->from;
           ackMailHdr.to = mailHdr->from;
           ackMailHdr.length = 0;
           ackMailHdr.Num_ACK = currentACK +1 ;
           currentACK  = currentACK +1 ;

           if(cpt == mailHdr->length){
                ackMailHdr.FIN = TRUE;
	            ackMailHdr.ACK = FALSE;
           }else{     
                ackMailHdr.FIN = FALSE;
	            ackMailHdr.ACK = TRUE; 
           }
printf("rsend\n");
           j =0;
           postOffice->Send(ackPktHdr, ackMailHdr, "");
           while(j<MAXREEMISSIONS && postOffice->IsThisMailboxEmpty(box)){ // Moyen securité
               Delay(TEMPO);
               postOffice->Send(ackPktHdr, ackMailHdr, "");
               j++;
           }
        }
        i++; 
    }
 
    if(ackMailHdr.FIN){
printf("rFIN\n");
        char buffer[MaxMailSize]={""};
        postOffice->Receive(box, pktHdr, mailHdr, buffer);
        if(mailHdr->ACK && mailHdr->FIN){
            return 1; 
        }
    }
    char buffer[MaxMailSize]={""};
    postOffice->Receive(box, pktHdr, mailHdr, buffer);
printf("rFIN_FIN\n");
    return -1;
}

bool ReseauFiable::isExitACK(){
    return currentACK == -1;
}

