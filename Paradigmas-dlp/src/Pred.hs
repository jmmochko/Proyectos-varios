module Pred (
  Pred,
  cambiar, anyDib, allDib, orP, andP, falla
) where

import Dibujo (Dibujo, foldDib, rot45, rotar, espejar, encimar, apilar, juntar, figura)
type Pred a = a -> Bool

-- Dado un predicado sobre básicas, cambiar todas las que satisfacen
-- El predicado por la figura básica indicada por el segundo argumento.
cambiar :: Pred a -> (a -> Dibujo a) -> Dibujo a -> Dibujo a
cambiar condicion cambio = foldDib (\fig -> if condicion fig then cambio fig else figura fig) rotar espejar rot45 apilar juntar encimar

-- Alguna básica satisface el predicado.
anyDib :: Pred a -> Dibujo a -> Bool
anyDib condicion = foldDib condicion (&& True) (&& True) (&& True) (\_ _ d1 d2 -> d1 || d2) (\_ _ d1 d2 -> d1 || d2) (||)

-- Todos los predicados satisfacen el contenido
allDib :: Pred a -> Dibujo a -> Bool
allDib condicion = foldDib condicion (|| False) (|| False) (|| False) (\_ _ d1 d2 -> d1 && d2) (\_ _ d1 d2 -> d1 && d2) (&&)

-- Ambos predicados se cumplen para el elemento recibido
andP :: Pred a -> Pred a -> Pred a
andP condicion1 condicion2 fig = condicion1 fig && condicion2 fig

-- Algún predicado se cumple para el elemento recibido.
orP :: Pred a -> Pred a -> Pred a
orP condicion1 condicion2 fig = condicion1 fig || condicion2 fig

falla :: Bool
falla = True