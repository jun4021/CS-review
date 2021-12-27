#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct PacketHeader 
{
    unsigned int captime; /*second*/
    unsigned int caputime; /*microsecond*/
    unsigned int caplen; /*capture length*/
    unsigned int packlen; /*packet length*/
}PacketHeader;

typedef struct EthernetHeader
{
    unsigned char dst_MAC[6];
    unsigned char src_MAC[6];
    unsigned short iptype;
    /* Ethernet 14 B*/
}EthernetHeader;

typedef struct IPHeader{
    unsigned int non_use; /*version, HLEN, Total length 등 필요 시 쪼개서 사용.*/
    unsigned short id;
    unsigned short flag_offset; /* (flag)3 + (offset)13 bits*/
    unsigned char TTL;
    unsigned char protocol; /* 0x01:ICMP 0x06:TCP 0x11:UDP */
    unsigned short checksum;
    unsigned char src_ip[4];
    unsigned char dst_ip[4];
    /*IP 20 B (Non-option)*/

}IPHeader;

void LocalTime(int captime, int caputime){
    time_t time = captime;
    struct tm* timeinfo = localtime(&time);
    
    int hour = timeinfo->tm_hour;
    int min = timeinfo->tm_min;
    int sec = timeinfo->tm_sec;
    int micro = caputime;
    printf("Local Time : %02d:%02d:%02d.%06d\n",hour,min,sec,micro);
}

void PacketHeaderinfo(FILE *f, PacketHeader *header,int packetnumber){ 
    printf("%d 번째\n",packetnumber); 

    /* 현재 시간 출력*/
    LocalTime(header->captime,header->caputime);

    /*Capture length , Actual Length*/
    printf("capture length :%d, Actual length: %d\n",header->caplen,header->packlen);
}

void EthernetHeaderInfo(FILE *f, EthernetHeader *header,int len){
    /*Source MAC*/
    for (int i=0;i<5;i++)
        printf("%02x:",header->src_MAC[i]);
    printf("%02x -> ",header->src_MAC[5]);
    
    /*Destination MAC*/
    for (int i=0;i<5;i++)
        printf("%02x:",header->dst_MAC[i]);
    printf("%02x\n",header->dst_MAC[5]);
}

void IPHeaderInfo(FILE *f,IPHeader* header){
    /*Source IP*/
    for (int i=0;i<3;i++)
        printf("%d.",header->src_ip[i]);
    printf("%d -> ",header->src_ip[3]);

    /*Destination IP*/
    for (int i=0;i<3;i++)
        printf("%d.",header->dst_ip[i]);
    printf("%d \n",header->dst_ip[3]);
    
    /*Protocol*/
    switch(header->protocol){
        case 0x01:
            printf("protocol: ICMP (%#x)\n",header->protocol);
            break;
        case 0x06:
            printf("protocol: TCP (%#x)\n",header->protocol);
            break;
        case 0x11:
            printf("protocol: UDP (%#x)\n",header->protocol);
            break;
        default:
            printf("protocol: %#x\n",header->protocol);
            break;
            
    }
    
    /*Identification*/
    printf("ID: %d\n",ntohs(header->id));
    
    /*flag, fragmentation offset*/
    int flag =header->flag_offset; 
    if((0x40&flag)==0){
        printf("DF = 0\n");
    }
    else{
        printf("DF = 1\n");
    }

    if((0x20&flag)==0){
        printf("MF = 0\n");
    }
    else{
        printf("MF = 1\n");
    }
    
    int offset = ntohs(flag&0xff1f)*8;
    printf("Fragement Offset: %d\n",offset);

    /*TTL*/
    printf("TTL: %d \n",header->TTL);
}

int main(int argc, char* argv[])
{
    FILE *fp =0;
    
    fp = fopen("frag.pcap","rb"); // argv[1] 변경예정
    if (fp == 0){
        printf("Error: Cannot Open");
        return 0;
    }

    /*Pcap File Header */
    unsigned char fileheader[24];
    fread(fileheader,sizeof(fileheader),1,fp); 

    /*원하는 packet 개수만큼*/
    for(int i=0;i<10;i++) 
    {
        PacketHeader *Pheader = malloc(sizeof(PacketHeader));
        fread(Pheader, sizeof(PacketHeader),1,fp);
        PacketHeaderinfo(fp,Pheader,i+1); /*(i+1) 번째 packet*/
        int len = Pheader->caplen;

        EthernetHeader *Eheader = malloc(sizeof(EthernetHeader));
        fread(Eheader,sizeof(EthernetHeader),1,fp);
        EthernetHeaderInfo(fp,Eheader,len);
        
        IPHeader *IPheader = malloc(sizeof(IPHeader));
        fread(IPheader,sizeof(IPHeader),1,fp);
        IPHeaderInfo(fp,IPheader);
        
        len = len - 34; /*20 + 14*/
        unsigned char* non_use = malloc(len);
        fread(non_use,len,1,fp);
        printf("\n\n");

        free(Pheader);
        free(Eheader);
        free(IPheader);
        free(non_use);
    }
    
    
    return 0;
}
