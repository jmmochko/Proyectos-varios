module Interp
  ( interp,
    initial,
  )
where

import Dibujo
import FloatingPic
import Graphics.Gloss (Display (InWindow), color, display, makeColorI, pictures, translate, white, Picture)
import qualified Graphics.Gloss.Data.Point.Arithmetic as V

-- Dada una computación que construye una configuración, mostramos por
-- pantalla la figura de la misma de acuerdo a la interpretación para
-- las figuras básicas. Permitimos una computación para poder leer
-- archivos, tomar argumentos, etc.
initial :: Conf -> Float -> IO ()
initial (Conf n dib intBas) size = display win white $ withGrid fig size
  where
    win = InWindow n (ceiling size, ceiling size) (0, 0)
    fig = interp intBas dib (0, 0) (size, 0) (0, size)
    desp = -(size / 2)
    withGrid p x = translate desp desp $ pictures [p, color grey $ grid (ceiling $ size / 10) (0, 0) x 10]
    grey = makeColorI 100 100 100 100

-- Interpretación de (^^^)
ov :: Picture -> Picture -> Picture
ov f g = pictures [f, g]

-- Rotar 45
r45 :: FloatingPic -> FloatingPic
r45 f d w h = f (d V.+ half (w V.+ h)) (half (w V.+ h)) (half (h V.- w))

-- Rotar 90
rot :: FloatingPic -> FloatingPic
rot f d w h = f (d V.+ w) h (V.negate w)

-- Espejar
esp :: FloatingPic -> FloatingPic
esp f d w = f (d V.+ w) (V.negate w)

-- Encimar
sup :: FloatingPic -> FloatingPic -> FloatingPic
sup f g d w h = pictures [f d w h, g d w h]

-- Juntar
jun :: Float -> Float -> FloatingPic -> FloatingPic -> FloatingPic
jun m n f g d w h = pictures [f d w' h, g (d V.+ w') (r' V.* w) h]
  where
    r' = n/(m+n)
    r = m/(m+n)
    w' = r V.* w

-- Apilar
api :: Float -> Float -> FloatingPic -> FloatingPic -> FloatingPic
api m n f g d w h = pictures [f (d V.+ h') w (r V.* h), g d w h']
  where
    r' = n/(m+n)
    r = m/(m+n)
    h' = r' V.* h

interp :: Output a -> Output (Dibujo a)
interp b = foldDib b rot esp r45 api jun sup