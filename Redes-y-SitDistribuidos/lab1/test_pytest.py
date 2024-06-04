import requests
import pytest
import requests_mock


@pytest.fixture
def mock_response():
    with requests_mock.Mocker() as m:
        # Simulamos la respuesta para obtener todas las películas
        m.get('http://localhost:5000/peliculas', json=[
            {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
            {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'}
        ])

        # Simulamos la respuesta para agregar una nueva película
        m.post(
            'http://localhost:5000/peliculas',
            status_code=201,
            json={
                'id': 3,
                'titulo': 'Pelicula de prueba',
                'genero': 'Acción'})

        # Simulamos la respuesta para obtener detalles de una película
        # específica
        m.get(
            'http://localhost:5000/peliculas/1',
            json={
                'id': 1,
                'titulo': 'Indiana Jones',
                'genero': 'Acción'})

        # Simulamos la respuesta para actualizar los detalles de una película
        m.put(
            'http://localhost:5000/peliculas/1',
            status_code=200,
            json={
                'id': 1,
                'titulo': 'Nuevo título',
                'genero': 'Comedia'})

        # Simulamos la respuesta para eliminar una película
        m.delete('http://localhost:5000/peliculas/1', status_code=200)

        # Tests de las nuevas funciones
        # simulamos la respuesta para que devuelva peliculas de un genero
        # especifico
        m.get('http://localhost:5000/peliculas?genero=Drama',
              json=[{'id': 10,
                     'titulo': 'The Shawshank Redemption',
                     'genero': 'Drama'},
                    {'id': 12,
                     'titulo': 'Fight Club',
                     'genero': 'Drama'}])

        # Simulamos buscar una pelicula con una palabra determinada en el
        # titulo
        m.get('http://localhost:5000/peliculas?titulo=The', json=[
            {'id': 7, 'titulo': 'The Lord of the Rings', 'genero': 'Fantasía'},
            {'id': 8, 'titulo': 'The Dark Knight', 'genero': 'Acción'},
            {'id': 10, 'titulo': 'The Shawshank Redemption', 'genero': 'Drama'}
        ])

        # Simulamos una pelicula aleatoria
        m.get('http://localhost:5000/peliculas', json=[
            {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
            {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'},
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
        ])
        yield m

# -----------------

# ------------------


def test_obtener_peliculas(mock_response):
    response = requests.get('http://localhost:5000/peliculas')
    assert response.status_code == 200
    assert len(response.json()) == 2


def test_agregar_pelicula(mock_response):
    nueva_pelicula = {'titulo': 'Pelicula de prueba', 'genero': 'Acción'}
    response = requests.post(
        'http://localhost:5000/peliculas',
        json=nueva_pelicula)
    assert response.status_code == 201
    assert response.json()['id'] == 3


def test_obtener_detalle_pelicula(mock_response):
    response = requests.get('http://localhost:5000/peliculas/1')
    assert response.status_code == 200
    assert response.json()['titulo'] == 'Indiana Jones'


def test_actualizar_detalle_pelicula(mock_response):
    datos_actualizados = {'titulo': 'Nuevo título', 'genero': 'Comedia'}
    response = requests.put(
        'http://localhost:5000/peliculas/1',
        json=datos_actualizados)
    assert response.status_code == 200
    assert response.json()['titulo'] == 'Nuevo título'


def test_eliminar_pelicula(mock_response):
    response = requests.delete('http://localhost:5000/peliculas/1')
    assert response.status_code == 200


# Nuevos test de las funciones implementadas
def test_peliculas_genero_especifico(mock_response):
    genero = 'Drama'
    response = requests.get(f'http://localhost:5000/peliculas?genero={genero}')
    assert response.status_code == 201
    data = response.json()
    assert 'mensaje' in data
    assert 'peliculas' in data
    assert len(data['peliculas']) > 0
    for pelicula in data['peliculas']:
        assert pelicula['genero'] == genero


def test_buscar_palabras_titulo(mock_response):
    response = requests.get('http://localhost:5000/peliculas?titulo=The')
    assert response.status_code == 200
    data = response.json()
    assert 'mensaje' in data
    assert 'peliculas encontradas' in data
    assert len(data['peliculas encontradas']) == 3
    assert data['peliculas encontradas'][0]['titulo'] == 'The Lord of the Rings'
    assert data['peliculas encontradas'][1]['titulo'] == 'The Dark Knight'
    assert data['peliculas encontradas'][2]['titulo'] == 'The Shawshank Redemption'
