Funcionalidades y como usar:
GET '/peliculas' devuelve una lista con todas las peliculas.
POST '/peliculas,{pelicula a agregar}' agrega la pelicula en cuestion.
PUT '/peliculas,{pelicula a modificar}' modifica la informacion de la pelicula en cuestion.
DELETE '/peliculas/{id}' elimina, de existir, la pelicula con dicho {id}.
GET '/peliculas/{id}' devuelve, de existir la informacion de la pelicula con el {id} dado.
GET '/peliculas/genero={genero}' devuelve una lista de todas las peliculas con dicho genero. (cuidado, es sensible a mayusculas. ej: Drama =/= drama)
GET '/peliculas/titulo={fragmento de titulo}' devuelve una lista de todas las peliculas con ese fragmento de titulo en el titulo. (sensible a mayusculas)
GET '/peliculas/random' devuelve una pelicula aleatoriamente.
GET '/peliculas/sugerir/genero={genero}' devuelve aleatoriamente una pelicula de el generp {genero}. (sensible a mayusculas)
GET '/peliculas/feriado/genero={genero}' devuelve la informacion del proximo feriado y una pelicula del genero {genero} recomendada para ver ese dia. (sensible a mayusculas)