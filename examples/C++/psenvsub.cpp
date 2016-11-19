//
//  Pubsub envelope subscriber
//
// Olivier Chamoux <olivier.chamoux@fr.thalesgroup.com>

#include "zhelpers.hpp"

int main () {
    //  Prepare our context and subscriber
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5563");

    // 设置订阅内容
    // subscriber.setsockopt( ZMQ_SUBSCRIBE, "B", 1);

    int i = 1;
    while (1) {

        if (i % 10 < 5) {
            std::cout<<"AAA"<<std::endl;
            subscriber.setsockopt( ZMQ_UNSUBSCRIBE, "B", 1);
            subscriber.setsockopt( ZMQ_SUBSCRIBE, "A", 1);
        }
        else {
            std::cout<<"BBB"<<std::endl;
            subscriber.setsockopt( ZMQ_UNSUBSCRIBE, "A", 1);
            subscriber.setsockopt( ZMQ_SUBSCRIBE, "B", 1);
        }
 
		//  Read envelope with address
		std::string address = s_recv (subscriber);
		//  Read message contents
		std::string contents = s_recv (subscriber);
		
        std::cout << "[" << address << "] " << i << ", " << contents << std::endl;
        ++i;
    }
    return 0;
}
