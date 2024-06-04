import requests
from proximo_feriado import NextHoliday
# Obtener todas las películas
response = requests.get('http://localhost:5000/peliculas')
peliculas = response.json()
print("Películas existentes:")
for pelicula in peliculas:
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
print()

# Agregar una nueva película
nueva_pelicula = {
    'titulo': 'Pelicula de prueba',
    'genero': 'Acción'
}
response = requests.post(
    'http://localhost:5000/peliculas',
    json=nueva_pelicula)
if response.status_code == 201:
    pelicula_agregada = response.json()
    print("Película agregada:")
    print(
        f"ID: {pelicula_agregada['id']}, Título: {pelicula_agregada['titulo']}, Género: {pelicula_agregada['genero']}")
else:
    print("Error al agregar la película.")
print()

# Obtener detalles de una película específica
id_pelicula = 1  # ID de la película a obtener
response = requests.get(f'http://localhost:5000/peliculas/{id_pelicula}')
if response.status_code == 200:
    pelicula = response.json()
    print("Detalles de la película:")
    print(
        f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
else:
    print("Error al obtener los detalles de la película.")
print()

# Actualizar los detalles de una película
id_pelicula = 1  # ID de la película a actualizar
datos_actualizados = {
    'titulo': 'Nuevo título',
    'genero': 'Comedia'
}
response = requests.put(
    f'http://localhost:5000/peliculas/{id_pelicula}',
    json=datos_actualizados)
if response.status_code == 200:
    pelicula_actualizada = response.json()
    print("Película actualizada:")
    print(
        f"ID: {pelicula_actualizada['id']}, Título: {pelicula_actualizada['titulo']}, Género: {pelicula_actualizada['genero']}")
else:
    print("Error al actualizar la película.")
print()

# Eliminar una película
id_pelicula = 3  # ID de la película a eliminar
response = requests.delete(f'http://localhost:5000/peliculas/{id_pelicula}')
if response.status_code == 200:
    print("Película eliminada correctamente.")
else:
    print("Error al eliminar la película.")
print()

# 2 Peliculas con un genero especifico
genero = 'Ciencia ficción'
response = requests.get(f'http://localhost:5000/peliculas/genero={genero}')
if response.status_code == 201:
    data = response.json()
    print("Películas del género Ciencia ficción:")
    for pelicula in data:
        if pelicula['genero'] == genero:
            print(
                f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
        else:
            print(
                "Error al obtener las películas del género Ciencia ficción. Hay películas de distinto género")
else:
    print("Error al obtener las películas del género Ciencia ficción.")
print()

# 3 Buscar una peliculas con un determinado string en el titulo
palabra = 'The'
response = requests.get(f'http://localhost:5000/peliculas/titulo={palabra}')
if response.status_code == 200:
    data = response.json()
    print("Películas con ese string en el título:")
    for pelicula in data:  # itero sobre los elementos de la lista
        if palabra in pelicula['titulo']:
            print(
                f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}")
        else:
            print("Error al obtener películas. Hay películas de distinto título.")
else:
    print("Error al obtener películas.")
print()

# test sugerir pelicula random
response = requests.get(f'http://localhost:5000/peliculas/random')
if response.status_code == 200:
    data = response.json()
    print('pelicula aleatoria sugerida: ')
    print(
        f"ID: {data['id']}, Título: {data['titulo']}, Género: {data['genero']}\n")
else:
    print('error al obtener pelicula aleatoria')

# test sugerir pelicula random según género
genero = "Acción"
response = requests.get(f'http://localhost:5000/peliculas/sugerir/genero={genero}')
if response.status_code == 200:
    pelicula = response.json()
    if pelicula['genero'] == genero:
        print('Pelicula aleatoria de acción sugerida: ')
        print(
            f"ID: {pelicula['id']}, Título: {pelicula['titulo']}, Género: {pelicula['genero']}\n")
    else:
        print('Error al obtener pelicula aleatoria. Se dió una de distinto género')
else:
    print('Error al obtener pelicula aleatoria')


# test pelicula sugerida para el proximo feriado
genero = 'Drama'
response = requests.get(f'http://localhost:5000/peliculas/feriado/genero={genero}')
if response.status_code == 200:
    data = response.json()
    print('El proximo feriado es: ')
    print(data['proximo feriado'])
    print('La pelicula sugerida del genero ' + genero + ' es:')
    print(f"ID: {data['pelicula sugerida']['id']}, Título: {data['pelicula sugerida']['titulo']}, Género: {data['pelicula sugerida']['genero']}")
else:
    print('Error al pedir pelicula sugerida por feriado')
