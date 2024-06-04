from flask import Flask, jsonify, request
import random
import proximo_feriado
app = Flask(__name__)
peliculas = [
    {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
    {'id': 2, 'titulo': 'Star Wars', 'genero': 'Ciencia ficción'},
    {'id': 3, 'titulo': 'Interstellar', 'genero': 'Ciencia ficción'},
    {'id': 4, 'titulo': 'Jurassic Park', 'genero': 'Aventura'},
    {'id': 5, 'titulo': 'The Avengers', 'genero': 'Acción'},
    {'id': 6, 'titulo': 'Back to the Future', 'genero': 'Ciencia ficción'},
    {'id': 7, 'titulo': 'The Lord of the Rings', 'genero': 'Fantasía'},
    {'id': 8, 'titulo': 'The Dark Knight', 'genero': 'Acción'},
    {'id': 9, 'titulo': 'Inception', 'genero': 'Ciencia ficción'},
    {'id': 10, 'titulo': 'The Shawshank Redemption', 'genero': 'Drama'},
    {'id': 11, 'titulo': 'Pulp Fiction', 'genero': 'Crimen'},
    {'id': 12, 'titulo': 'Fight Club', 'genero': 'Drama'}
]


def obtener_peliculas():
    return jsonify(peliculas)


def obtener_pelicula(id):
    # Lógica para buscar la película por su ID y devolver sus detalles
    for pelicula_encontrada in peliculas:
        if pelicula_encontrada['id'] == id:
            return jsonify(pelicula_encontrada), 200
    return jsonify({'mensaje': 'La pelicula no fue encontrada'}), 400


def agregar_pelicula():
    nueva_pelicula = {
        'id': obtener_nuevo_id(),
        'titulo': request.json['titulo'],
        'genero': request.json['genero']
    }
    peliculas.append(nueva_pelicula)
    return jsonify(nueva_pelicula), 201


def actualizar_pelicula(id):
  # Lógica para buscar la película por su ID y actualizar sus detalles
    for pelicula_actualizada in peliculas:
      # si cumple la condicion que tenga el mismo id
        if pelicula_actualizada['id'] == id:
          # verifico si titulo esta en en el request.json, significa que hay
          # datos nuevos para actualizar
            if 'titulo' in request.json:
                pelicula_actualizada['titulo'] = request.json['titulo']
            if 'genero' in request.json:
                pelicula_actualizada['genero'] = request.json['genero']
          # devuelvo la pelicula actualizada
            return jsonify(pelicula_actualizada), 200
    return jsonify({'mensaje': 'No hay peliculas para actualizar'}), 204


def eliminar_pelicula(id):
    # Lógica para buscar la película por su ID y eliminarla
    for pelicula_eliminada in peliculas:
        if pelicula_eliminada['id'] == id:
            peliculas.remove(pelicula_eliminada)
            return jsonify(
                {'mensaje': 'Película eliminada correctamente'}), 200
    return jsonify({'mensaje': 'No hay pelicula para eliminar'}), 404


# 2-Implementa la funcionalidad para devolver el listado de películas de
# un género específico.

def peliculas_genero_especifico(genero):
    genero_peliculas = [
        pelicula for pelicula in peliculas if pelicula['genero'] == genero]
    if genero_peliculas:
        return jsonify(genero_peliculas), 201
    else:
        return jsonify(
            {'mensaje': 'No se encontraron peliculas de ese genero'}), 404

# 3-implemente la funcionalidad de búsqueda de películas, devolviendo la
# lista de películas que tengan determinado string en el título.


def buscar_peliculas(titulo):
    buscar = [pelicula for pelicula in peliculas if titulo in pelicula['titulo']]
    if len(buscar) >= 1:
        return jsonify(buscar), 200
    else:
        return jsonify(
            {'mensaje': 'No se encontraron peliculas que contengan esta(s) palabra(s) en el titulo'}), 204


# 4-Implemente la funcionalidad de sugerir una película aleatoria
def sugerir_pelicula_aleatoria():
  # el random.choice, elije una pelicula aleatoria de la lista peliculas
    pelicula_aleatoria = random.choice(peliculas)
    return jsonify(pelicula_aleatoria), 200

# 5-Implemente la funcionalidad de sugerir una película aleatoria según género


def pelicula_aleatoria_genero(genero):
    genero_de_peliculas = [
        pelicula for pelicula in peliculas if pelicula['genero'] == genero]
    if len(genero_de_peliculas) > 0:
        return jsonify(random.choice(genero_de_peliculas)), 200
    else:
        return jsonify(
            {'mensaje': 'No se encontraron peliculas de ese genero'}), 204


def aux_pelicula_aleatoria_genero(genero):
    genero_de_peliculas = [
        pelicula for pelicula in peliculas if pelicula['genero'] == genero]
    if len(genero_de_peliculas) > 0:
        return random.choice(genero_de_peliculas)
    else:
        return None


def obtener_nuevo_id():
    if len(peliculas) == 0:
        return 1
    ids = [pelicula['id'] for pelicula in peliculas]
    ids.sort()
    for i in range(len(ids)):
        if ids[i] != i + 1:
            return i + 1
    return len(ids) + 1

# 3B pelicula sugerida para el proximmo feriado


def sugerir_pelicula_feriado(genero):
    pelicula_sugerida = aux_pelicula_aleatoria_genero(genero)
    if (pelicula_sugerida is None):
        return jsonify('Error: No se pudo sugerir pelicula'), 418
    return jsonify({'pelicula sugerida': pelicula_sugerida,
                   'proximo feriado': proximo_feriado.next_holiday.holiday}), 200


app.add_url_rule(
    '/peliculas',
    'obtener_peliculas',
    obtener_peliculas,
    methods=['GET'])
app.add_url_rule(
    '/peliculas/<int:id>',
    'obtener_pelicula',
    obtener_pelicula,
    methods=['GET'])
app.add_url_rule(
    '/peliculas',
    'agregar_pelicula',
    agregar_pelicula,
    methods=['POST'])
app.add_url_rule(
    '/peliculas/<int:id>',
    'actualizar_pelicula',
    actualizar_pelicula,
    methods=['PUT'])
app.add_url_rule(
    '/peliculas/<int:id>',
    'eliminar_pelicula',
    eliminar_pelicula,
    methods=['DELETE'])

# Rutas de las nuevas funciones
app.add_url_rule(
    '/peliculas/genero=<genero>',
    'peliculas_genero_especifico',
    peliculas_genero_especifico,
    methods=['GET'])
app.add_url_rule(
    '/peliculas/titulo=<titulo>',
    'buscar_peliculas',
    buscar_peliculas,
    methods=['GET'])
app.add_url_rule(
    '/peliculas/random',
    'sugerir_pelicula_aleatoria',
    sugerir_pelicula_aleatoria,
    methods=['GET'])
app.add_url_rule(
    '/peliculas/sugerir/genero=<genero>',
    'pelicula_aleatoria_genero',
    pelicula_aleatoria_genero,
    methods=['GET'])
app.add_url_rule(
    '/peliculas/feriado/genero=<genero>',
    'sugerir_pelicula_feriado',
    sugerir_pelicula_feriado,
    methods=['GET'])

if __name__ == '__main__':
    app.run()
