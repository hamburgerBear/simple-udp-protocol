# simple-udp-protocol

a simple udp protocol,communication "heart x y theta idx idy flag" for motion robot map and pose

/* 
	heart     :心跳包            
	x         :世界坐标x         
	y         :世界坐标y
	theta     :世界坐标theta
	idx       :栅格地图idx
	idy       :栅格地图idy
	flag      :栅格地图标签flag
	checksum  :协议校验和
*/

#define UDP_PROTOCOL_LEN 23

struct TUdpDisplayProtocol //23bytes
{
	uint8_t  heart;
	float    x;
	float    y;
	float    theta;
	int32_t  idx;
	int32_t  idy;
	uint8_t  flag;
	uint8_t  checksum;   
};
