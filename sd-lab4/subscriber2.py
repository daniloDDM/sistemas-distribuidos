import zmq

context = zmq.Context()
sub = context.socket(zmq.SUB)
sub.connect("tcp://proxy:5556")

sub.setsockopt(zmq.SUBSCRIBE, b"hello")

while True:
    topic, message = sub.recv_multipart()
    print(f"[Subscriber2] Recebido [{topic.decode()}]: {message.decode()}", flush=True)

sub.close()
context.term()
