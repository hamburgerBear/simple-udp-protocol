#include <iostream>
#include <unistd.h>
#include "CUdpCommunication.h"

int main()
{
	CUdpCommunication udp_receive;
	udp_receive.configReceiver();
	
	while(1)
	{
		udp_receive.receive();
		std::cout << "[CUdpCommunication] receive heart : " 
		          <<  (int)udp_receive.m_udp_packet.heart 
		          << std::endl;
		std::cout << "[CUdpCommunication] receive x : " 
		          <<  (float)udp_receive.m_udp_packet.x 
		          << std::endl;
		std::cout << "[CUdpCommunication] receive y : " 
		          <<  (float)udp_receive.m_udp_packet.y 
		          << std::endl;
		usleep(20 * 1000);
	}
	return 0;
}