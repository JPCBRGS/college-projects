import socket
import threading

PORT = 20000 #porta para conectar
SERVER = str(socket.gethostbyname(socket.gethostname())) #recebe o IP da máquina local por meio do nome da máquina local
ADDR = (SERVER, PORT) #endereço para conexão
CLIENTSIDE_DISCONNECT_MESSAGE = '/bye' #messagem para desconexão do servidor
MSIZE = 1024 #tamanho fixo para mensagens

#declarando socket UDP
server_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

connected = True

def receiveFile(con, name):
    data = con.recv(MSIZE)
    if (data):
        f = open('./client_files/' + name,'wb') #arquivos do cliente armazenados em uma pasta específica para ver se estão sendo transferidos para pasta do servidor
        while 1:
            f.write(data)
            data = con.recv(MSIZE)
            if not data:
                break
        f.close()

    return

def sendFile(name):
    try:
        with open(f"./client_files/{name}", "rb") as f:
            tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            tcp.connect(ADDR)
            text = "FILE:" + name
            server_udp.sendto(text.encode(), ADDR)
            for msg in f:
                tcp.send(msg)
            tcp.close()
    except FileNotFoundError:
        print(f"Arquivo '{name}' não foi encontrado na pasta client_files.")

def send():
    while True:
        msg = input().split(" ")

        #solicita lista de clientes ativos no momento
        if msg[0] == '/list':
            text = "LIST"
            server_udp.sendto(text.encode(), ADDR)

        #envia um arquivo
        elif msg[0] == '/file':
            sendFile(msg[1])

        #baixa arquivo
        elif msg[0] == '/get':
            tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            tcp.connect(ADDR)
            text = "GET:" + msg[1]
            server_udp.sendto(text.encode(), ADDR)
            receiveFile(tcp, msg[1])
            tcp.close()

        #desconectando usuário
        elif msg[0] == CLIENTSIDE_DISCONNECT_MESSAGE:
            text = "BYE"
            server_udp.sendto(text.encode(), ADDR)
            connected = False
            break

        #envio de mensagens normais
        else:
            text = "MSG:" + " ".join(msg)
            server_udp.sendto(text.encode(), ADDR)

    server_udp.close()
    return

def listen():
    while connected:
        msg, client = server_udp.recvfrom(MSIZE)
        msg = msg.decode().split(":")
        if msg[0] == 'INFO':
            if msg[1] == 'disconnect': #caso seja desconectado
                break             
            elif len(msg) < 3:
                print(msg[1])
            else:
                print(msg[1] + ': ' + msg[2])
        elif msg[0] == 'MSG':
            print(msg[1] + ': ' + msg[2])
    return

msg = input('Nome de usuário: ') #input inicial de usuário
text = "USER:" + msg
server_udp.sendto(text.encode(), ADDR)

t1 = threading.Thread(target=send, args=())
t1.start()

t2 = threading.Thread(target=listen, args=())
t2.start()
