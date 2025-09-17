import zmq
import random
from time import time, sleep

context = zmq.Context()
pub = context.socket(zmq.PUB)
pub.connect("tcp://proxy:5555")

while True:
    pub.send_multipart([b"hello", b"Mensagem do Publisher2"])
    print("Publisher2 enviou: hello", flush=True)

    numero = str(random.randint(1, 10)).encode("utf-8")
    pub.send_multipart([b"random", numero])
    print(f"Publisher2 enviou: random -> {numero.decode()}", flush=True)
    
    sleep(2)

pub.close()
context.close()
