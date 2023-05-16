#---------------------------------------------#
# INTEGRANTES DO GRUPO:
## João Pedro Clemente Borges - 95654
## Marcelo Castro Grossi - 95686
#---------------------------------------------#

import os
import logging
import socket
import threading
import time

PORT = 20000 
SERVER = str(socket.gethostbyname(socket.gethostname())) #recebe o IP da máquina local por meio do nome da máquina local
ADDR = (SERVER, PORT) #endereço de conexão padrão
MSIZE = 1024 #tamanho fixo para mensagens
SERVERSIDE_DISCONNECT_MESSAGE = 'BYE' #messagem para desconexão do servidor

logging.basicConfig(filename='server_logs.log', level=logging.INFO, format='%(asctime)s %(message)s') #log criado para armazenar mensagens relativas ao servidor (não guarda mensagens de clientes)
conn_clients = {} #lista de clientes conectados

#implementando protocolo UDP
server_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_udp.bind(ADDR)

#método para enviar mensagens para outros clientes ativos
def forwardToAllClients(msg, client):
    for curr_socket in conn_clients: #verifica a lista de clientes ativos e envia para todos, exceto o cliente que enviou a mensagem
        if curr_socket != client: 
            server_udp.sendto(msg.encode(), curr_socket) 

#ao receber arquivos, cria uma pasta server_files (caso não exista) onde são armazenados os arquivos do servidor
def receiveFiles(con, name):
    directory = './server_files'
    if not os.path.exists(directory):
        os.makedirs(directory)
    f = open(f'{directory}/{name}','wb')  #especifica a pasta server_files no caminho para abertura
    while True:
        data = con.recv(MSIZE)
        if not data:
            break
        f.write(data)  #escreve o arquivo recebido dentro da pasta de arquivos do servidor
    f.close()
    print("Arquivo recebido.")

    return

def sendFiles(con, name):
    error = ''
    try:
        with open(f"./server_files/{name}", "rb") as f:
            for msg in f.readlines(): #ê os dados do arquivo selecionado para envios e os envia de volta
                con.send(msg)
            f.close()
            print('Arquivo enviado.')
    except FileNotFoundError:
        error = 'INFO:Esse arquivo não está disponível'
        print('Arquivo indisponível')

    return error

#função principal que executa protocolos de acordo com as mensagens dos clientes
def receive():

    while True:
        #inicia conexão TCP
        tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        tcp.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        tcp.bind(ADDR)
        tcp.listen(1)

        msg, client = server_udp.recvfrom(MSIZE)
        msg = msg.decode().split(":")

        #recebendo usuário
        if msg[0] == 'USER':
            conn_clients[client] = msg[1] 
            text = 'INFO:' + msg[1] + ' entrou'
            logging.info(text)
            forwardToAllClients(text, client)

        #recebendo mensagem normal
        elif msg[0] == 'MSG':
            text = "MSG:" + conn_clients[client] + " disse:" + msg[1]
            forwardToAllClients(text, client)

        #listando usuários online no momento
        elif msg[0] == 'LIST':
            print('[LISTING] Sending list of all clients that are currently online...')
            logging.info('[LISTING] Sending list of all clients that are currently online...')
            text = 'INFO:Online:\n'
            for client_socket in conn_clients: 
                text += conn_clients[client_socket] + ", "
            server_udp.sendto(text.encode(), client) 

        #recebendo arquivo
        elif msg[0] == 'FILE':
            con, trash_TCP = tcp.accept()
            receiveFiles(con, msg[1])
            text = 'INFO:' + conn_clients[client] + ' enviou ' + msg[1] #notify message
            logging.info(text)
            forwardToAllClients(text, client)
            con.close()

        #enviando arquivo para o cliente
        elif msg[0] == 'GET':
            con, trash_TCP = tcp.accept()
            text = sendFiles(con, msg[1])
            if len(text):
                server_udp.sendto(text.encode(), client) 
            con.close()

        #desconectando do servidor
        elif msg[0] == SERVERSIDE_DISCONNECT_MESSAGE:
            text = 'INFO:' + conn_clients[client] + ' saiu' #notify message
            logging.info(text)
            forwardToAllClients(text, client)
            del conn_clients[client] 
            server_udp.sendto('INFO:disconnect'.encode(), client) 

        #caso não existam outros usuários online, finaliza conexão
        if len(conn_clients) == 0:
            print("[ENDING] No more clients connected. Closing server...")
            logging.info('[ENDING] No more clients connected. Closing server...')
            break

    tcp.close() #fecha conexão
    return

#início da execução do servidor
print("[STARTING] Starting server execution...")
logging.info('[STARTING] Starting server execution...')
t1 = threading.Thread(target=receive, args=())
t1.start()
