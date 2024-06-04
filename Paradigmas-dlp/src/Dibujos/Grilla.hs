module Dibujos.Grilla (
    grillaConf,
    grilla
) where

import Dibujo (Dibujo, juntar, apilar, figura)
import Graphics.Gloss ( Picture, translate, scale, text, color, blue)
import FloatingPic (Output, Conf (..))

--show i show j convierte el int en cadena de texto 
coordenada :: Int -> Int -> String
coordenada i j = "(" ++ show i ++ "," ++ show j ++ ")"

--defino tipo color
data Color = Azul
    deriving (Show, Eq)

type Basica = (Float, Float, String, Color)

--defino 
pintar :: Color -> Picture -> Picture
pintar Azul = color blue

interpFigura :: Output Basica
interpFigura (fila, columna, par_ord, col) _ _ _ = pintar col $ translate fila columna $ scale 0.2 0.2 (text par_ord)


row :: [Dibujo a] -> Dibujo a
row [] = error "row: no puede ser vacío"
row [d] = d
row (d:ds) = juntar (fromIntegral $ length ds) 1 d (row ds)

column :: [Dibujo a] -> Dibujo a
column [] = error "column: no puede ser vacío"
column [d] = d
column (d:ds) = apilar (fromIntegral $ length ds) 1 d (column ds)
                                     --primero se calcula la longitud de ds
                        --luego al valor lo convierte en float
                                                        --se aplica recursividad sobre la columna
--
grilla :: [[Dibujo a]] -> Dibujo a
grilla = column . map row

testAll :: Dibujo Basica
testAll = grilla [[figura (800*(fromIntegral j/10) , 800*(fromIntegral i/10), coordenada (7-i) j , Azul) | i <- [0..7]] | j <- [0..7]]
--                                                                                                      lista bidimensional
--800 tamaño de la ventana y/10 indica como se van a didivir cada una de las coordenadas en toda la ventana
grillaConf :: Conf
grillaConf = Conf {
    name = "Grilla",
    pic = testAll,
    bas = interpFigura 
}
