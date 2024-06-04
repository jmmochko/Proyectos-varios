#!/usr/bin/env python
# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Revisión 2014 Carlos Bederián
# Revisión 2011 Nicolás Wolovick
# Copyright 2008-2010 Natalia Bidart y Daniel Moisset
# $Id: server.py 656 2013-03-18 23:49:11Z bc $

import optparse
import socket
import connection
import sys
from constants import *


class Server(object):
    """
    El servidor, que crea y atiende el socket en la dirección y puerto
    especificados donde se reciben nuevas conexiones de clientes.
    """

    def __init__(self, addr=DEFAULT_ADDR, port=DEFAULT_PORT,
                 directory=DEFAULT_DIR):
        print("Serving %s on %s:%s." % (directory, addr, port))
        # FALTA: Crear socket del servidor, configurarlo, asignarlo
        # a una dirección y puerto, etc.
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        #self.s.bind -> indica la direccion local
        self.socket.bind((addr,port))
        #socket en metodo escucha (establece el maximo de conexiones pendientes que se pueden encolar)
        self.socket.listen(5)
        #asigno el directorio
        self.directory = directory
        self.count_connection = 0

    def serve(self):
        """
        Loop principal del servidor. Se acepta una conexión a la vez
        y se espera a que concluya antes de seguir.
        """
        while True:
            #pass
            # FALTA: Aceptar una conexión al server, crear una
            # Connection para la conexión y atenderla hasta que termine.
             # Connection para la conexión y atenderla hasta que termine.
            print("Esperamos una nueva conexión")
            #conn- devuelve el nuevo objeto del socket, a-la direccion del cliente que se ha conectado 
            conn,address= self.socket.accept()
            self.count_connection += 1
            print("La conexión fue establecida")
            #indicamos numero de conexion y junto con la direccion y puerto del cliente
            print(f"Conexión {self.count_connection} aceptada de {address[0]}:{address[1]}")
            new_conn = connection.Connection(conn, self.directory)
            new_conn.handle()
            
            


def main():
    """Parsea los argumentos y lanza el server"""

    parser = optparse.OptionParser()
    parser.add_option(
        "-p", "--port",
        help="Número de puerto TCP donde escuchar", default=DEFAULT_PORT)
    parser.add_option(
        "-a", "--address",
        help="Dirección donde escuchar", default=DEFAULT_ADDR)
    parser.add_option(
        "-d", "--datadir",
        help="Directorio compartido", default=DEFAULT_DIR)

    options, args = parser.parse_args()
    if len(args) > 0:
        parser.print_help()
        sys.exit(1)
    try:
        port = int(options.port)
    except ValueError:
        sys.stderr.write(
            "Numero de puerto invalido: %s\n" % repr(options.port))
        parser.print_help()
        sys.exit(1)

    server = Server(options.address, port, options.datadir)
    server.serve()


if __name__ == '__main__':
    main()
