#include "post.h"
#include "sysdep.h"
#include "thread.h"
#include "system.h"
#include <string.h>

#define divRoundUp(n,s)    (((n) / (s)) + ((((n) % (s)) > 0) ? 1 : 0))

/******************************************************************************/
int
ReseauFiable::Send(PacketHeader pktHdr, MailHeader mailHdr, const char* data){ //Donnée
    char buffer[MaxMailSize];

    mailHdr.length = strlen(data) + 1;
    int res = divRoundUp(mailHdr.length,MaxMailSize);

    if(isExitACK()){
        currentACK = 0;
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
//printf("sdata: %s\n",data);
printf("sparametre b:%s,pk.to:%d,m.to:%d,m.from:%d,m.length:%d\n",data,pktHdr.to,mailHdr.to,mailHdr.from,mailHdr.length);

    while(i < res && (j!=MAXREEMISSIONS)){
        if((taille+cpt)>mailHdr.length) taille = mailHdr.length-cpt; 

        memcpy(buffer,data+(taille*i),taille);
        postOffice->Send(pktHdr, mailHdr, buffer);
printf("ssend1: %s,%d,%d\n",buffer,mailHdr.Num_ACK,currentACK);
        while(j<MAXREEMISSIONS && !AckFinReceived(mailHdr.from,taille+cpt==mailHdr.length)){
            Delay(TEMPO);
            postOffice->Send(pktHdr, mailHdr, buffer);
printf("ssendn: %s,%d\n",buffer,mailHdr.Num_ACK);
//printf("j:%d ",j);
            j++;
        }
//printf("\n");
        strcpy(buffer,"");
        if(j!=MAXREEMISSIONS){
//printf("sACK OK\n");
            mailHdr.Num_ACK = currentACK+1;
            currentACK++;
            cpt = taille;
        }
        i++;
    }
//printf("sACK FIN:%d==%d && %d!=%d \n",i,res,j,MAXREEMISSIONS);
    ASSERT((i == res)&&(j!=MAXREEMISSIONS));
    
    mailHdr.Num_ACK = currentACK +1 ;
    mailHdr.ACK = TRUE;
    mailHdr.FIN = TRUE;
    mailHdr.length = 8;
    currentACK = currentACK+1;
printf("ssend: ACK_FIN\n");

    postOffice->Send(pktHdr, mailHdr,"ACK_FIN");

printf("FinFIN envoie\n");
    return 0;  
}
/******************************************************************************/
bool
ReseauFiable::AckFinReceived(int box,bool b){
    PacketHeader inPktHdr;
    MailHeader inMailHdr;
    char data[MaxMailSize];
    inMailHdr.Num_ACK = -1;


    while(!postOffice->IsThisMailboxEmpty(box) && ( (currentACK+1) != inMailHdr.Num_ACK) ){
        postOffice->Receive(box, &inPktHdr, &inMailHdr, data);//erreur allocation
        printf("ackreceive:%s,num:%d,ack:%d,fin:%d\n",data,inMailHdr.Num_ACK,inMailHdr.ACK,inMailHdr.FIN);
    }
    if(currentACK+1 == inMailHdr.Num_ACK){
        if(inMailHdr.FIN && b){
            return TRUE;
        }else{
            return inMailHdr.ACK;
        }
    }else{

        return FALSE;
    }
}
/******************************************************************************/
int
ReseauFiable::Receive(int box, PacketHeader *pktHdr, MailHeader *mailHdr, char* data){
    PacketHeader ackPktHdr;
	MailHeader   ackMailHdr;
           
    int res = 1;
    int i = 0;
    int j = 0;
    unsigned cpt = 0;

    ackMailHdr.FIN = FALSE;
    while((i < res)){

        postOffice->Receive(box, pktHdr, mailHdr, data+(MaxMailSize*(res-1))); // tempo
        printf("receive: %s,Fin:%d,ACk:%d\n",data,mailHdr->FIN,mailHdr->ACK);
        if(cpt==0){
            res = divRoundUp(mailHdr->length,MaxMailSize);
        }
        cpt = strlen(data)+1 + cpt;
        if(isExitACK()){
            currentACK = mailHdr->Num_ACK -1;
            printf("current init\n");
        }
        
printf("rACK: %d==%d\n",currentACK,mailHdr->Num_ACK );
        if((currentACK+1) == mailHdr->Num_ACK ){
           currentACK  = currentACK +1 ;
           ackPktHdr.to = pktHdr->from;
           ackMailHdr.to = mailHdr->from;
           ackMailHdr.length = 4;
           ackMailHdr.Num_ACK = currentACK +1 ;
           
printf("cpt:%d == %d \n",cpt,mailHdr->length);
char str[10];
           if(cpt == mailHdr->length){
                ackMailHdr.FIN = TRUE;
	            ackMailHdr.ACK = FALSE;
                strcpy(str,"Fin");
printf("rsend FIN\n");
           }else{     
                ackMailHdr.FIN = FALSE;
	            ackMailHdr.ACK = TRUE; 
                strcpy(str,"Ack");
printf("rsend ACK\n");
           }
           j =0;
           postOffice->Send(ackPktHdr, ackMailHdr,str);
printf("send:%s,%d\n",str,ackMailHdr.Num_ACK);     
           while(j<MAXREEMISSIONS && postOffice->IsThisMailboxEmpty(box)){ // Moyen securité
               Delay(TEMPO);
               postOffice->Send(ackPktHdr, ackMailHdr,str);
printf("send:%s,%d\n",str,ackMailHdr.Num_ACK);     
               j++;
           } 
        }else if(!postOffice->IsThisMailboxEmpty(box)){
            printf("aaaaaa\n");
            i--;
        }
        i++;
    }

    char buffer[MaxMailSize]={""};

    if(ackMailHdr.FIN){

        while((!mailHdr->ACK) && (!mailHdr->FIN)&& ((currentACK+1)!= mailHdr->Num_ACK)){
            postOffice->Receive(box, pktHdr, mailHdr, buffer);
            printf("Finreceive:%s\n",buffer);
        }    
        
        if(mailHdr->ACK && mailHdr->FIN && ((currentACK+1)== mailHdr->Num_ACK)){
            return 1; 
        }
    }

    printf("rFIN_FIN\n");
    return -1;
}
/******************************************************************************/
bool ReseauFiable::isExitACK(){
    return currentACK == -1;
}
/******************************************************************************/
