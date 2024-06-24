# -*- coding: utf-8 -*-
# @Author: Xia Yunkai
# @Date:   2024-06-23 14:47:46
# @Last Modified by:   Xia Yunkai
# @Last Modified time: 2024-06-23 15:32:29

import xviz_msgs_pb2 as xviz_msgs
import zmq
import time

def send_protobuf(socket, proto_msg):
    socket.send(proto_msg.SerializeToString())



def main():
    context = zmq.Context()
    publisher = context.socket(zmq.PUB)
    publisher.bind("tcp://127.0.0.1:8888")

    polygon = xviz_msgs.Polygon2f
    polygon_str =  polygon.SerializeToString()
    # message = ["haha","4",polygon.SerializeToString()]   
    # while 1:
            
    #     publisher.send_multipart(message)
    #     publisher.send("haha")
    #     publisher.send("5")
    #     send_protobuf(socket,polygon)
    #     time.sleep(1)

    

    
    print("Hello, World!")


if __name__ == "__main__":
    main()
