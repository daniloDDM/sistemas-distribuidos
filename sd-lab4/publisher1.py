import zmq
from time import time, sleep

context = zmq.Context()
pub = context.socket(zmq.PUB)
pub.connect("tcp://proxy:5555")

while True:
    pub.send_multipart([b"tempo", str(time()).encode("utf-8")])
    print("Publisher1 enviou: tempo", flush=True)

    pub.send_multipart([b"hello", b"Ola do Publisher1"])
    print("Publisher1 enviou: hello", flush=True)
    
    sleep(1)

pub.close()
context.close()
