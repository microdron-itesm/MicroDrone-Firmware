//
// Created by abiel on 8/16/20.
//

#include "comms.h"
#include <stdio.h>

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdbool.h>

char target_ip[100];
const uint16_t target_send_port = 14551;
const uint16_t target_recv_post = 14550;

struct sockaddr_in gcAddr; //IP addr of QGroundControl server
struct sockaddr_in locAddr; //Local IP addr
socklen_t fromLen;

int sock;

void hal_comms_init(){
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1){
        perror("Socket open failed");
        exit(EXIT_FAILURE);
    }

    memset(&locAddr, 0, sizeof(locAddr));
    locAddr.sin_family = AF_INET;
    locAddr.sin_addr.s_addr = INADDR_ANY;
    locAddr.sin_port = htons(target_send_port);

    int ret = bind(sock, (struct sockaddr *) &locAddr, sizeof(struct sockaddr));
    if(ret < 0){
        perror("UDP bind failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    ret = fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC);
    if(ret < 0){
        perror("Nonblocking set failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    strcpy(target_ip, "127.0.0.1");
    memset(&gcAddr, 0, sizeof(gcAddr));
    gcAddr.sin_family = AF_INET;
    gcAddr.sin_addr.s_addr = inet_addr(target_ip);
    gcAddr.sin_port = htons(target_recv_post);
    fromLen = sizeof(gcAddr);
}

size_t hal_comms_send_buffer(uint8_t *buf, char len){
    return sendto(sock, buf, len, 0, (struct sockaddr*) &gcAddr, sizeof(struct sockaddr_in));
}

size_t hal_comms_recev_buffer(uint8_t *buf, char buf_len){
    return recvfrom(sock, (void*) buf, buf_len, 0, (struct sockaddr *) &gcAddr, &fromLen);
}

void hal_comms_close(){
    close(sock);
}