# TCP header parsing

## 목표 
- WireShark에서 얻어낸 pcap file을 이용하여 정보를 얻어낸다.
-----------
## 구조체 소개
- pcap file의 구조는 "global_header" 뒤에 "Packet_header"+"Packet_data"가 연달아 오는 방식이다. 

+ pcap_global 구조체
    + pcap file 전체의 정보를 담았다.

    ```
    typedef struct pcap_global {
        uint32_t magic_number; /* magic number */
        uint16_t version_major; /* major version number */
        uint16_t version_minor; /* minor version number */
        int32_t timezone; /* GMT to local correction */
        uint32_t accuracy; /* accuracy of timestamps */
        uint32_t snaplen; /* max length of captured packets, in octets */
        uint32_t network; /* data link type */
    };
    ```
    #### 특이사항
    1. magic_number : 0xA1B2C3D4로 pcap file임을 확인하는 정보이다. 이때 little endian으로 작성되어 있어 "D4 C3 B2 A1"으로 확인 가능하다.

- pcap_pkthdr 구조체
    - Packet 별 정보를 담았다.

    ```
    struct pcap_pkthdr {
        struct timeval ts;	/* time stamp */
        bpf_u_int32 caplen;	/* length of portion present */
        bpf_u_int32 len;	/* length this packet (off wire) */
    };
    ```

* Ethernet Header, IP Header
    ```
    struct EthernetHeader
    {
        unsigned char dst_MAC[6];
        unsigned char src_MAC[6];
        unsigned short iptype;
        /* Ethernet 14 B*/
    };
    ```
    ```
    struct IPHeader{
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
    };
    ```
---------
## 구현
- 각 header를 순서에 맞게 pcap file에서 읽어 각 구조체 정보에 맞게 저장한다.
- binary file로 이루어진 pcap file을 fread 함수를 이용해 읽는다.
- 그 외 특이사항으로는 Packet Header에서 packet의 길이를 불러와 읽어온 header 길이를 제외한 나머지 정보는 packet data이고, 이번에는 header를 parsing하는 것이 목적이므로 data는 읽고 사용하지 않았다. 
- little endian으로 작성되어 있어 parsing할 때 조심해야 한다. (ntohs 함수 사용)

```
size_t fread (void * DstBuf, size_t ElementSize, size_t Count, FILE * FileStream)
```
* 인수
    * DstBuf : 입력받은 데이터를 저장할 버퍼의 주소
    * ElementSize : 원소 1개의 크기
    * Count : 입력 받을 원소의 개수
    * FileStream

---------
## 결과
- linux 환경에서 컴파일 후 다음 방식으로 출력하였다.
```
$./IP file.pcap  
```
<img width="50%" src="https://user-images.githubusercontent.com/86395683/147477125-1e1bcc41-8d52-4bf7-aa74-ab445ca69c16.PNG">
