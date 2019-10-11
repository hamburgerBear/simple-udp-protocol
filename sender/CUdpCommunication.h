#pragma once

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#include "CUdpDisplayProtocol.h"

class CUdpCommunication
{

#define DEST_PORT 8000
#define SERV_PORT 8000
	
#define DSET_IP_ADDRESS  "172.16.11.118"  	
#define SERV_IP_ADDRESS  "172.16.11.118"   

public:
	CUdpCommunication()
	{
		m_heart = 0;
	}

	~CUdpCommunication()
	{
		close(m_sock_fd);  
	}

	void configSender()
	{
		m_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);  
		if(m_sock_fd < 0)  
		{
			std::cout << "[CUdpCommunication]connect fail!!" << std::endl;  
			exit(1);
		}
		memset(&m_addr_serv, 0, sizeof(m_addr_serv));  
		m_addr_serv.sin_family = AF_INET;  
		m_addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS);  
		m_addr_serv.sin_port = htons(DEST_PORT);  
		m_len = sizeof(m_addr_serv); 
	}

	void configReceiver()
	{
		m_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if(m_sock_fd < 0)
		{
			std::cout << "[CUdpCommunication]connect fail!!" << std::endl;  
		    exit(1);
		}
		memset(&m_addr_serv, 0, sizeof(struct sockaddr_in));
		m_addr_serv.sin_family = AF_INET;
  		m_addr_serv.sin_port = htons(SERV_PORT);
  		m_addr_serv.sin_addr.s_addr = inet_addr(SERV_IP_ADDRESS); 

  		m_len = sizeof(m_addr_serv);
	    if(bind(m_sock_fd, (struct sockaddr*)&m_addr_serv, sizeof(m_addr_serv)) < 0)
	    {
	    	std::cout << "[CUdpCommunication]bind error!!" << std::endl;  
	    	exit(1);
	    }
	}

	void send(float x, float y)
	{

		m_udp_packet.heart = m_heart;
		m_udp_packet.x     = x;
		m_udp_packet.y     = y;
		sendto(m_sock_fd, &m_udp_packet, 23, 0, (struct sockaddr *)&m_addr_serv, m_len);  
		m_heart++;
	}

	void receive()
	{
		std::cout << "[CUdpCommunication]server wait!!" << std::endl;  
		int recv_num;
		char recv_buf[20];
		struct sockaddr_in addr_client;
		recv_num = recvfrom(m_sock_fd, &m_udp_packet, sizeof(m_udp_packet), 0, (struct sockaddr *)&addr_client, (socklen_t *)&m_len);
	    if(recv_num < 0)
	    {
	    	std::cout << "[CUdpCommunication]recvfrom error!!" << std::endl;  
	        exit(1);
	    }
	}

	int                  m_sock_fd; 
	struct sockaddr_in   m_addr_serv;  
	int                  m_len;  

	TUdpDisplayProtocol  m_udp_packet;
	uint8_t              m_heart;
}; 
