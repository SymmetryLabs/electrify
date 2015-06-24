#include "opc_client.h"
#include <iostream>
#include <vector>
#include <unistd.h>
int main()
{
	std::vector<uint8_t> frameBuffer= {0};
	int frameBytes = 10000 * 3;
	OPCClient opc = OPCClient();
	frameBuffer.resize(sizeof(OPCClient::Header) + frameBytes);
	int i=0;
	

	opc.resolve("10.200.1.44", 7890);

	while(opc.tryConnect()) {
		for(std::vector<uint8_t>::iterator it = frameBuffer.begin() ; it != frameBuffer.end(); ++it)
		{
			(*it) = i % 3 ==0 ? i : 
			i % 2 ==0? i : 0x55u;
			i++;
		}
		OPCClient::Header::view(frameBuffer).init(0, opc.SET_PIXEL_COLORS, frameBytes);
		bool res = opc.write(frameBuffer);
		std::cout << res;
		
		usleep(1000000);
	}

	return 0;
}