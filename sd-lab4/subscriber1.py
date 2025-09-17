import zmq

context = zmq.Context()
sub = context.socket(zmq.SUB)
sub.connect("tcp://proxy:5556")

sub.setsockopt(zmq.SUBSCRIBE, b"hora")

while True:
    topic, message = sub.recv_multipart()
    print(f"[Subscriber1] Recebido [{topic.decode()}]: {message.decode()}", flush=True)

sub.close()
context.term()
