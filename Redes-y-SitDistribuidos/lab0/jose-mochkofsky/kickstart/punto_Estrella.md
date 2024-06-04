Internationalized domain name(IDNA) es la codificacion por default que se le debe dar a los nombres de dominios.
Para codificar a IDNA en python se puede usar og_string.encode('idna').

Por ejemplo:
>>> import socket 
>>> server_name = '中文.tw'
>>> server_name.encode('idna')
>>> print("中文.tw -> Encoded to " + repr(server_name))
中文.tw -> Encoded to b'xn--fiq228c.tw'
>>> print(socket.gethostbyname(b'xn--fiq228c.tw'))
60.199.218.199

Buscar 'xn--fiq228c.tw' en el buscador efectivamente me redirige a la pagina 中文.tw cuya direccion IP es 60.199.218.199

Fuentes: 
https://en.wikipedia.org/wiki/Internationalized_domain_name
https://www.honeybadger.io/blog/python-character-encoding/