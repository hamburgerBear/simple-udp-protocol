#include <iostream>
#include <unistd.h>
#include "CUdpCommunication.h"

int main()
{
	CUdpCommunication udp_sender;
	udp_sender.configSender();

	while(1)
	{
		static float x = 1.0;
		static float y = 1.2;

		// udp_sender.send(100.0, 200.0);
		udp_sender.send(x, y);
		std::cout << "send udp message" << std::endl; 

		x = x + 0.1;
		y = y + 0.1;

		usleep(100 * 1000);
	}

	return 0;
}