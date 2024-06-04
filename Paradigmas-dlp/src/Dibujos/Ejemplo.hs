module Dibujos.Ejemplo where

import Dibujo (Dibujo, figura, juntar, apilar, rot45, rotar, encimar, espejar)
import FloatingPic(Conf(..), Output, half, zero)
import qualified Graphics.Gloss.Data.Point.Arithmetic as V
import Graphics.Gloss ( Picture, blue, red, color, circle, pictures )

data Color = Rojo
    deriving (Show, Eq)

data BasicaSinColor = Circulo
    deriving (Show, Eq)

type Basica = (BasicaSinColor, Color)

colorear :: Color -> Picture -> Picture
colorear Rojo = color red

-- Las coordenadas que usamos son:
--
--  x + y
--  |
--  x --- x + w
--

-- por ahi deban ajustarlas
interpBasicaSinColor :: Output BasicaSinColor
interpBasicaSinColor Circulo _ _ _ = circle 1

interpBas :: Output Basica
interpBas (b, c) x y w = colorear c $ interpBasicaSinColor b x y w

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


testAll = grilla [
    [figura (Circulo, Rojo)]
    ]

ejemploConf :: Conf
ejemploConf = Conf {
    name = "Ejemplo"
    , pic = testAll
    , bas = interpBas
}
