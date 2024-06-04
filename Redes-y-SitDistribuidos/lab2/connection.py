# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Copyright 2014 Carlos Bederián
# $Id: connection.py 455 2011-05-01 00:32:09Z carlos $

import os
import socket
from constants import *
from base64 import b64encode

class Connection(object):
    """
    Conexión punto a punto entre el servidor y un cliente.
    Se encarga de satisfacer los pedidos del cliente hasta
    que termina la conexión.
    """

    def __init__(self, socket, directory):
        # FALTA: Inicializar atributos de Connection
        self.socket = socket
        self.status = None
        self.dir = directory

    # Todos las respuestas empiezan de forma similar, se automatiza
    def message(self, code):
        return f"{code} {error_messages[code]}{EOL}".encode(encoding='ascii')
    
    # Obtiene la lista de archivos que están actualmente disponibles
    def get_file_listing(self):
        self.socket.send(self.message(CODE_OK))
        for file in os.listdir(self.dir):
            filename = os.fsdecode(file)
            print(filename)
            self.socket.send((filename+EOL).encode(encoding='ascii'))
        self.socket.send(EOL.encode(encoding='ascii'))

    # Cierra la connecion
    # no se me ocurre ningun manejo de posibles errores que pueda ir aca
    def quit(self):
        self.socket.send(self.message(CODE_OK))
        print("Closing Connection...")
        self.socket.close()

    # Devuelve un string con los contenidos del archivo desde offset hasta offset+size
    # Asume que el archivo se encuentra en el directorio self.dir
    def get_slice(self, filename, offset, size):

        # Tanto offset como size deben ser positivos
        if(offset < 0): return self.message(BAD_OFFSET)
        if(size < 0): return self.message(INVALID_ARGUMENTS)
        
        path = self.dir + '/' +filename

        # Chequeo si path no me lleva a un archivo
        print(path)
        if(not os.path.isfile(path)): return self.message(FILE_NOT_FOUND)
        
        # Abro el archivo
        f = open(path, "r")
        
        #Confirmo que size + offset sea menor al tamaño del archivo
        fsize = os.path.getsize(path)
        if(fsize < size + offset): self.message(INVALID_ARGUMENTS)
        
        # Busco el offset y leo size desde esa parte del archivo 
        f.seek(offset,0)
        file_data = f.read(size)
        f.close()
        print('Encoding: ' + file_data)
        file_data = file_data.encode('ascii')
        file_data = b64encode(file_data)
        print('Encoded to ', file_data)
        self.socket.send(self.message(CODE_OK))
        return file_data
    
    # Dado un string data lo procesa
    # Devuelve True si quiteo
    def proccess(self, data):
        while(len(data)>0):
            if(data[0] == 'quit'):
                self.quit()
                data = []
                return True
            elif(data[0] == "get_slice"):
                if(len(data)>=4):
                    buf = self.get_slice(data[1], int(data[2]), int(data[3]))
                    self.socket.send(buf)
                    self.socket.send(EOL.encode('ascii'))
                    if(len(data) == 4):
                        data = []
                    else:
                        data = data[5::]
                else:
                    self.socket.send(self.message(INVALID_ARGUMENTS))
                    data = []
            elif(data[0] == "get_file_listing"):
                self.get_file_listing()
                if(len(data)==1):
                    data = []
                else:
                    data = data[1::]
            else:
                self.socket.send(self.message(INVALID_COMMAND))
                if(len(data)>1):
                    data = data[1::]
        return False
    
    def handle(self):
        """
        Atiende eventos de la conexión hasta que termina.
        """
        # Acepto la connection 
        # Asume que ya use __init__
        data = " "
        quitflag = False
        while(not quitflag):

            # Recibo data hasta que encuentre un \r\n
            # La data recibida se guarda como string en la variable data
            while('\n' not in data):
                data = self.socket.recv(4096).decode("ascii")
            
            # Borro todos los espacios al comienzo de data
            # Si el usuario manda "   quit\r\n" se perdona
            # Tambien borro el \r\n ya que sabemos que siempre esta si llegamos hasta aca

            i = 0
            while(i<len(data) and data[i]==" "):
                i+=1
            data = data[i:len(data) - 2:]
            data = data.split(" ")
            # Una vez tengo el comando guardado en data
            # Chequeo uno por uno si coincide con uno de los comandos estipulados
            print('received:\n', data)
            # Proceso los argumentos
            quitflag = self.proccess(data)