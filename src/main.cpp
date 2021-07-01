#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>

#include "pcs.h"

#include "transport_udp.h"


unsigned char sendBuff[64];

bool sendFlag = 0;

int forward = 1;
int backward = 2;
int turnleft = 3 ;
int turnright = 4;
int stop = 5;



int main()
{
	std::cout<<"------------------ Robot Control -------------------"<<std::endl;
	//---------------- Init the PCS tool ----------------------//
	pcs::PCS pcs;
	pcs::Publisher<int> pub = pcs.advertise<int>( "192.168.72.135", 2333 );
	

	//---------------- Init the KeyBoard Device ---------------//
	int keys_fd;
	struct input_event t;
	keys_fd = open( "/dev/input/event1", O_RDONLY );
	if( keys_fd <= 0 ){
		std::cout<<" open failed ..."<<std::endl;
		return false;
	}
	
	while(1){
		if( read( keys_fd, &t, sizeof( t ) ) == sizeof( t ) ){
			if( t.type == EV_KEY && t.code == 17  ){ // W
				if( t.value == 1 && sendFlag == 0 ){
					// send a forward //
					std::cout<<"forward"<<std::endl;
					//client.sendCommand( forward );
					pub.publish( forward );
					sendFlag = 1 ;
				}
				else if( t.value == 0 ){// 
					std::cout<<"stop"<<std::endl;
					//client.sendCommand( stop );
					pub.publish( stop );
					sendFlag = 0;
				}
			}

			if( t.type == EV_KEY && t.code == 30  ){ // A
                                if( t.value == 1 && sendFlag == 0 ){
                                        // send a turnleft //
                                        std::cout<<"turnleft"<<std::endl;
					pub.publish( turnleft );
                                        sendFlag = 1 ;
                                }
                                else if( t.value == 0 ){
                                        std::cout<<"stop"<<std::endl;
					pub.publish( stop );
					sendFlag = 0;
                                }
                        }
			
			if( t.type == EV_KEY && t.code == 32  ){ // D
                                if( t.value == 1 && sendFlag == 0 ){
                                        // send a trunright //
                                        std::cout<<"turnright"<<std::endl;
					pub.publish( turnright );
					sendFlag = 1 ;
                                }
                                else if( t.value == 0 ){
                                        std::cout<<"stop"<<std::endl;
					pub.publish( stop );
                                        sendFlag = 0;
                                }
                        }

			if( t.type == EV_KEY && t.code == 31  ){
                                if( t.value == 1 && sendFlag == 0 ){
                                        // send a backward //
                                        std::cout<<"backward"<<std::endl;
					pub.publish( backward );
                                        sendFlag = 1 ;
                                }
                                else if( t.value == 0 ){
                                        std::cout<<"stop"<<std::endl;
					pub.publish( stop );
                                        sendFlag = 0;
                                }
                        }


		}
	}
	return 0;
}
