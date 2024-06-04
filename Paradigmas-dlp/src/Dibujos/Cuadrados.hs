module Dibujos.Cuadrados where

import Dibujo (Dibujo, figura, juntar, apilar, rot45, rotar, encimar, espejar)
import FloatingPic(Conf(..), Output, half, zero)
import qualified Graphics.Gloss.Data.Point.Arithmetic as V
import Graphics.Gloss ( Picture, blue, red, color, line, pictures )

data Color = Azul
    deriving (Show, Eq)

data BasicaSinColor = Rectangulo
    deriving (Show, Eq)

type Basica = (BasicaSinColor, Color)

colorear :: Color -> Picture -> Picture
colorear Azul = color blue

-- Las coordenadas que usamos son:
--
--  x + y
--  |
--  x --- x + w
--
-- por ahi deban ajustarlas
interpBasicaSinColor :: Output BasicaSinColor
interpBasicaSinColor Rectangulo x y w = line [x, x V.+ y, x V.+ y V.+ w, x V.+ w, x]

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
    [figura (Rectangulo, Azul)]
    ]

cuadConf :: Int -> Conf
cuadConf _ = Conf {
    name = "Cuadrados"
    , pic = testAll
    , bas = interpBas
}
