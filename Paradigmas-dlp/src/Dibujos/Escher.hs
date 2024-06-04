module Dibujos.Escher where

import Dibujo (Dibujo, figura, juntar, apilar, rot45, rotar, encimar, espejar, r180, r270, cuarteto)
import FloatingPic(Conf(..), Output)
import qualified Graphics.Gloss.Data.Point.Arithmetic as V
import Graphics.Gloss ( Picture, blue, red, color, line, blank )

data Color = Azul | Rojo
    deriving (Show, Eq)

-- True si tengo que poner un bloque
type BasicaSinColor = Bool

-- Escher es una sola picture, el bloque basico para la imagen
type Escher = (BasicaSinColor, Color)

colorear :: Color -> Picture -> Picture
colorear Azul = color blue
colorear Rojo = color red

-- Esta implamentacion usa triangulos, para cambiar a otra figura simplemente modificar "interpBasicaSinColor True"
interpBasicaSinColor :: Output BasicaSinColor
interpBasicaSinColor True x y w = line $ map (x V.+) [(0,0), y, w, (0,0)]
interpBasicaSinColor False _ _ _ = blank

interpBas :: Output Escher
interpBas (b, c) x y w = colorear c $ interpBasicaSinColor b x y w

bloque :: Dibujo Escher
bloque = figura (True, Azul)

vacio :: Dibujo Escher
vacio = figura (False, Azul)

tile2 :: Dibujo Escher -> Dibujo Escher
tile2 p = espejar (rot45 p)

tile3 :: Dibujo Escher -> Dibujo Escher
tile3 p = r270 (tile2 p)

-- El dibujo u.
dibujoU :: Dibujo Escher -> Dibujo Escher
dibujoU p = encimar (encimar (tile2 p) (rotar (tile2 p))) (encimar (r180 (tile2 p)) (tile3 p))

-- El dibujo t.
dibujoT :: Dibujo Escher -> Dibujo Escher
dibujoT p = encimar p (encimar (tile2 p) (tile3 p))

-- Lado con nivel de detalle.
lado :: Int -> Dibujo Escher -> Dibujo Escher
lado 1 p = cuarteto vacio vacio (rotar (dibujoT p)) (dibujoT p)
lado n p = cuarteto (lado (n-1) p) (lado (n-1) p) (rotar (dibujoT p)) (dibujoT p)

-- Esquina con nivel de detalle en base a la figura p.
esquina :: Int -> Dibujo Escher -> Dibujo Escher
esquina 1 p = cuarteto vacio vacio vacio (dibujoU p)
esquina n p = cuarteto (esquina (n-1) p) (lado (n-1) p) (rotar (lado (n-1) p)) (dibujoU p)

-- Por suerte no tenemos que poner el tipo!
noneto :: Dibujo Escher -> Dibujo Escher -> Dibujo Escher -> Dibujo Escher -> Dibujo Escher -> Dibujo Escher -> Dibujo Escher -> Dibujo Escher -> Dibujo Escher -> Dibujo Escher
noneto p q r s t u v w x = apilar 1 2 (juntar 1 2 p (juntar 1 1 q r)) (apilar 1 1 (juntar 1 2 s (juntar 1 1 t u)) (juntar 1 2 v (juntar 1 1 x w)))

-- El dibujo de Escher:
escher :: Int -> Escher -> Dibujo Escher
escher n e = noneto (esquina n (figura e)) (lado n (figura e)) (r270 (esquina n (figura e))) (rotar (lado n (figura e))) (dibujoU (figura e)) (r270 (lado n (figura e))) (rotar(esquina n (figura e))) (r180 (esquina n (figura e))) (r180 (lado n (figura e)))

row :: [Dibujo a] -> Dibujo a
row [] = error "row: no puede ser vacío"
row [d] = d
row (d:ds) = juntar 1 (fromIntegral $ length ds) d (row ds)

column :: [Dibujo a] -> Dibujo a
column [] = error "column: no puede ser vacío"
column [d] = d
column (d:ds) = apilar 1 (fromIntegral $ length ds) d (column ds)

grilla :: [[Dibujo a]] -> Dibujo a
grilla = column . map row

testAll :: Int -> Dibujo Escher
testAll x = grilla [
    [escher x (True,Azul)]
    ]

escherConf :: Int -> Conf
escherConf n = Conf {
    name = "Escher"
    , pic = testAll n
    , bas = interpBas
}