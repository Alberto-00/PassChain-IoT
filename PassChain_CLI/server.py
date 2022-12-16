from socket import socket, AF_INET, SOCK_STREAM
from ssl import SSLContext, PROTOCOL_TLS_SERVER
from Loader import *
from main import select_actions
import json
import netifaces


def get_ip():
    for iface in netifaces.interfaces():
        iface_details = netifaces.ifaddresses(iface)
        if netifaces.AF_INET in iface_details:
            for ip_interfaces in iface_details[netifaces.AF_INET]:
                for key1, ip_add in ip_interfaces.items():
                    if key1 == 'addr' and ip_add != '127.0.0.1':
                        return ip_add


def init_server():
    loader = Loader("Loading Esp32 connection...", "Done!", 0.05).start()
    ip = get_ip()
    port = 11111
    context = SSLContext(PROTOCOL_TLS_SERVER)

    context.load_cert_chain("certs/server/domain.pem", "certs/server/domainK.pem")

    # client authentication
    context.load_verify_locations("certs/clients/domainClient.pem")

    with socket(AF_INET, SOCK_STREAM) as server:
        server.bind((ip, port))
        server.listen(1)
        with context.wrap_socket(server, server_side=True) as tls:
            connection, address = tls.accept()
            loader.stop()
            print(f'Connected by {address}')
            welcome_mex = connection.recv(12).decode('utf-8')

            # remove \r\n
            connection.recv(2)
            key = connection.recv(16)

            # remove \r\n
            connection.recv(2)
            con_len = int(connection.recv(6).decode('utf-8'))

            # remove \r\n
            connection.recv(2)

            data = bytearray()
            max_chunk = 16384
            num_chunks = int(con_len / max_chunk)
            for i in range(0, num_chunks + 1):
                data.extend(connection.recv(max_chunk))

            print(f'Client Says: {welcome_mex}')

            select_actions(json.loads(data.decode('utf-8')), connection, key)

            # connection.close() # close the connection
            # socket.close(self=True)
