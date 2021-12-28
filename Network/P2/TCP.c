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
    unsigned long headerlength :4;
    unsigned long version :4;
    unsigned long ds :8;
    unsigned long total_length :16;
     
    unsigned short id;
    unsigned short flag_offset; /* (flag)3 + (offset)13 bits*/
    unsigned char TTL;
    unsigned char protocol; /* 0x01:ICMP 0x06:TCP 0x11:UDP */
    unsigned short checksum;
    unsigned char src_ip[4];
    unsigned char dst_ip[4];
    /*IP 20 B (Non-option)*/

}IPHeader;

typedef struct TCPHeader{
    unsigned long src_port:16;
    unsigned long dst_port:16;
    unsigned int seq_num;
    unsigned char ack_num[4];

    unsigned long reserved1:4; /*reserved 4 bits(0000) endian 고려*/
    unsigned long hlen:4; /* hlen 4 bit */
    unsigned long fin:1;
    unsigned long syn:1;
    unsigned long rst:1;
    unsigned long psh:1;
    unsigned long ack:1;
    unsigned long urg:1;
    unsigned long reserved2:2;
    
    unsigned long window_size:16;
    unsigned long checksum:16;
    unsigned long urg_pointer:16;
    /*TCP 20 B (Non-option)*/
}TCPHeader;

typedef struct UDPHeader{
    unsigned long src_port:16;
    unsigned long dst_port:16;
    unsigned long t_len:16;
    unsigned long checksum:16;
    /*UDP 8 B */
}UDPHeader;

int TCP_max_payload =0;
int UDP_max_payload =0;

void LocalTime(int captime, int caputime){
    time_t time = captime;
    struct tm* timeinfo = localtime(&time);
    
    int hour = timeinfo->tm_hour;
    int min = timeinfo->tm_min;
    int sec = timeinfo->tm_sec;
    int micro = caputime;
    printf("Local Time : %02u:%02u:%02u.%06u\n",hour,min,sec,micro);
}

void PacketHeaderinfo(FILE *f, PacketHeader *header,int packetnumber){ 
    printf("%d 번째\n",packetnumber); 

    /* 현재 시간 출력*/
    LocalTime(header->captime,header->caputime);

    /*Capture length , Actual Length*/
    printf("capture length :%u, Actual length: %u\n",header->caplen,header->packlen);
}

void UDPHeaderInfo(FILE *f,UDPHeader* header){
    /*Port number*/
    printf("source : %u, destination : %u\n",ntohs(header->src_port),ntohs(header->dst_port));

    /*Payload = Total length - Header length(8 bytes)*/
    unsigned int payload = ntohs(header->t_len)-8;
    printf("Payload size : %u\n", payload);

    /*maximum payload*/
    if (UDP_max_payload < payload){
        UDP_max_payload = payload;
    }
    /*App type*/
    if((ntohs(header->src_port)==80) || (ntohs(header->dst_port)==80)){
        printf("Application : HTTP\n");
    }
    else if((ntohs(header->src_port)==443) || (ntohs(header->dst_port)==443)){
        printf("Application : HTTPS\n");
    }
    else if((ntohs(header->src_port)==53) || (ntohs(header->dst_port)==53)){
        printf("Application : DNS\n");
    }
}

void TCPHeaderInfo(FILE *f,TCPHeader* header,IPHeader * ipheader){
    /*Port number*/
    printf("source : %u, destination : %u\n",ntohs(header->src_port),ntohs(header->dst_port));
    /*payload*/
    unsigned int payload = 0;
    payload = ntohs(ipheader->total_length) - (ipheader->headerlength*4) - (header->hlen*4);

    /*maximum payload*/
    if (TCP_max_payload < payload){
        TCP_max_payload = payload;
    }
    /*Sequence number*/
    unsigned int seq = ntohl(header->seq_num);
    if (payload == 0){
        printf("Start sequence number : %u\n",seq);    
    }
    else
        printf("Start sequence number : %u, End squence number : %u\n",seq, seq + payload -1);
    /*Ack number*/
    unsigned int ack = (header->ack_num[0]);
    for (int i=1;i<4;i++){
        ack = ack<<8;
        ack = ack + header->ack_num[i];
    }
    printf("Acknowledgement number : %u\n", ack);

    printf("Payload : %u\n",payload);

    /*window size*/
    printf("Window size : %u\n",ntohs(header->window_size));

    /*segment type (flag)*/
    if(header->syn)
        printf(("SYN\n"));
    if(header->fin)
        printf(("FIN\n"));
    if(header->rst)
        printf(("RST\n"));
    if(header->psh)
        printf(("PSH\n"));
    if(header->ack)
        printf(("ACK\n"));
    if(header->urg)
        printf(("URG\n"));
        
    /*App type*/
    if((ntohs(header->src_port)==80) || (ntohs(header->dst_port)==80)){
        printf("Application : HTTP\n");
    }
    else if((ntohs(header->src_port)==443) || (ntohs(header->dst_port)==443)){
        printf("Application : HTTPS\n");
    }
    else if((ntohs(header->src_port)==22) || (ntohs(header->dst_port)==22)){
        printf("Application : SSH\n");
    }
    else if((ntohs(header->src_port)==23) || (ntohs(header->dst_port)==23)){
        printf("Application : Telnet\n");
    }

}

void TCPoption(char * opt,int len){
    int cursor = 0;
    printf("TCP Option: ");
    while(cursor != len){
        switch(opt[cursor]){
            case 0:
                printf("End of options list, ");
                cursor = cursor + 1;
                break;
            case 1:
                printf("No operation, ");
                cursor = cursor + 1;
                break;
            case 2:
                printf("Maximum segment size");
                cursor = cursor + 2;
                unsigned char first = opt[cursor]; 
                unsigned char second =opt[cursor+1];
                printf("(value:%d), ",first*256+second);

                cursor = cursor + 2;
                break;
            case 3:
                printf("Window scale");
                cursor = cursor + 2;
                printf("(shift count:%d), ",opt[cursor]);
                cursor = cursor + 1;
                break;
            case 4:
                printf("Selective Acknowledgement permitted, ");
                cursor = cursor + 2;
                break;
            case 5:
                printf("Sack");
                cursor = cursor + 1;
                printf("(length : %d), ",opt[cursor]);
                cursor = cursor + opt[cursor] - 1;
                break;
            case 8:
                printf("Timestamp and echo of previous timestamp, ");
                cursor = cursor + 10;
                break;
            case 14:
                printf("TCP alternate checksum request, ");
                cursor = cursor + 3;
                break;
            default:
                printf("Unknown option, ");
                cursor = cursor +1;
                break;
            

        } 
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    FILE *fp =0;
    
    fp = fopen("packet_test.pcap","rb"); // argv[1] 변경예정
    if (fp == 0){
        printf("Error: Cannot Open");
        return 0;
    }

    /*Pcap File Header */
    unsigned char fileheader[24];
    fread(fileheader,sizeof(fileheader),1,fp); 

    /*원하는 packet 개수만큼*/
    for(int i=0;i<500;i++) 
    {
        PacketHeader *Pheader = malloc(sizeof(PacketHeader));
        fread(Pheader, sizeof(PacketHeader),1,fp);
        PacketHeaderinfo(fp,Pheader,i+1); /*(i+1) 번째 packet*/
        int len = Pheader->caplen;

        EthernetHeader *Eheader = malloc(sizeof(EthernetHeader));
        fread(Eheader,sizeof(EthernetHeader),1,fp);
        IPHeader *IPheader = malloc(sizeof(IPHeader));
        fread(IPheader,20,1,fp);

        int iplen =IPheader->headerlength*4 -20;
        if (iplen != 0){
            unsigned char * ip_option = malloc(iplen);
            fread(ip_option,iplen,1,fp);
            free(ip_option);   
        }
        len = len - (14 + IPheader->headerlength*4);
        TCPHeader *TCPheader = malloc(sizeof(TCPHeader));
        UDPHeader *UDPheader = malloc(sizeof(UDPHeader));

        /*Protocol*/
        switch(IPheader->protocol){
            case 0x01:
                printf("protocol: ICMP (%#x)\n",IPheader->protocol);
                break;
            case 0x06:
                printf("protocol: TCP (%#x)\n",IPheader->protocol);
                fread(TCPheader,20,1,fp);
                TCPHeaderInfo(fp,TCPheader,IPheader);
                int optionlen =TCPheader->hlen*4 -20;
                if (optionlen != 0){
                    unsigned char * TCP_option = malloc(optionlen);
                    fread(TCP_option,optionlen,1,fp);
                    TCPoption(TCP_option,optionlen);
                    free(TCP_option);
                }
                len = len - (TCPheader->hlen*4);
                break;
            case 0x11:
                printf("protocol: UDP (%#x)\n",IPheader->protocol);
                fread(UDPheader,sizeof(UDPHeader),1,fp);
                UDPHeaderInfo(fp,UDPheader);
                len = len - 8;
                break;
            default:
                printf("protocol: %#x\n",IPheader->protocol);
                break;
        }        
        /*conncetion check*/

        /*data payload*/    
        unsigned char* data = malloc(len);
        fread(data,len,1,fp);
        printf("\n\n");

        free(Pheader);
        free(Eheader);
        free(IPheader);
        free(data);
    }
    
    printf("UDP max payload: %u\n",UDP_max_payload);
    printf("TCP max payload: %u\n",TCP_max_payload);

    return 0;
}