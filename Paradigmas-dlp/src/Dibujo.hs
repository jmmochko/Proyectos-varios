module Dibujo (Dibujo, 
    comp,
    encimar, figura, apilar, juntar, rot45, rotar, espejar,
    (^^^), (.-.), (///),
    r90, r180, r270,
    encimar4, cuarteto, ciclar,
    mapDib, foldDib,
    change,
    ) where


-- nuestro lenguaje 
data Dibujo a = Figura a
              | Rotar (Dibujo a)
              | Espejar (Dibujo a)
              | Rot45 (Dibujo a)
              | Apilar Float Float (Dibujo a) (Dibujo a)
              | Juntar Float Float (Dibujo a) (Dibujo a)
              | Encimar (Dibujo a) (Dibujo a)
              deriving (Eq, Show)

-- combinadores
infixr 6 ^^^

infixr 7 .-.

infixr 8 ///

comp :: Int -> (a -> a) -> a -> a
comp n f a
  | n < 0 = error "" --Componer negativamente es un error!
  | n == 0 = a
  | n > 0 = f (comp (n-1) f a) --componer 1 vez es aplicar la función 1 vez


-- Funciones constructoras
figura :: a -> Dibujo a
figura = Figura

encimar :: Dibujo a -> Dibujo a -> Dibujo a
encimar = Encimar

apilar :: Float -> Float -> Dibujo a -> Dibujo a -> Dibujo a
apilar = Apilar 

juntar  :: Float -> Float -> Dibujo a -> Dibujo a -> Dibujo a
juntar = Juntar

rot45 :: Dibujo a -> Dibujo a
rot45  = Rot45

rotar :: Dibujo a -> Dibujo a
rotar  = Rotar

espejar :: Dibujo a -> Dibujo a
espejar = Espejar

--superpone un dibujo con otro
(^^^) :: Dibujo a -> Dibujo a -> Dibujo a
(^^^) = encimar

--pone el primer dibujo arriba del segundo, ambos ocupan el mismo espacio
(.-.) :: Dibujo a -> Dibujo a -> Dibujo a
(.-.) = apilar 1.0 1.0  

--pone un dibujo al lado del otro, ambos ocupan el mismo espacio
(///) :: Dibujo a -> Dibujo a -> Dibujo a
(///) = juntar 1.0 1.0

-- rotaciones
r90 :: Dibujo a -> Dibujo a
r90 = rotar 

r180 :: Dibujo a -> Dibujo a
r180 d = r90 (r90 d)

r270 :: Dibujo a -> Dibujo a
r270 d = r180 (r90 d)

-- una figura repetida con las cuatro rotaciones, superimpuestas.
encimar4 :: Dibujo a -> Dibujo a
encimar4 a = (r270 a ^^^ a) ^^^ (r180 a ^^^ r90 a)

-- cuatro figuras en un cuadrante.
cuarteto :: Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a -> Dibujo a
cuarteto a b c d = (a /// b) .-. (c /// d) 

-- un cuarteto donde se repite la imagen, rotada (¡No confundir con encimar4!)
ciclar :: Dibujo a -> Dibujo a
ciclar a = cuarteto a (r90 a) (r180 a) (r270 a)

-- map para nuestro lenguaje
mapDib :: (a -> b) -> Dibujo a -> Dibujo b
mapDib fun dibujo =
      case dibujo of 
        Figura a -> Figura (fun a)
        Rotar d -> Rotar (mapDib fun d)
        Espejar d -> Espejar (mapDib fun d)
        Rot45 d -> Rot45 (mapDib fun d)
        Apilar a1 a2 d1 d2 -> Apilar a1 a2 (mapDib fun d1) (mapDib fun d2)
        Juntar a1 a2 d1 d2 ->Juntar a1 a2 (mapDib fun d1) (mapDib fun d2)
        Encimar d1 d2 -> Encimar (mapDib fun d1) (mapDib fun d2 )

-- verificar que las operaciones satisfagan
-- 1. map figura = id
-- 2. map (g . f) = mapDib g . mapDib f

-- Cambiar todas las básicas de acuerdo a la función.
--transforma cada figura básica dentro del dibujo aplicando la función f, 
--y devuelve un nuevo dibujo con las figuras básicas transformadas en el tipo b
change :: (a -> Dibujo b) -> Dibujo a -> Dibujo b
change f dibujo =
  case dibujo of
    Figura a      -> f a
    Rotar d       -> Rotar (change f d)
    Espejar d     -> Espejar (change f d)
    Rot45 d       -> Rot45 (change f d)
    Apilar a b d1 d2 -> Apilar a b (change f d1) (change f d2)
    Juntar a b d1 d2 -> Juntar a b (change f d1) (change f d2)
    Encimar d1 d2 -> Encimar (change f d1) (change f d2)

-- Principio de recursión para Dibujos.
foldDib ::
  (a -> b) ->
  (b -> b) ->
  (b -> b) ->
  (b -> b) ->
  (Float -> Float -> b -> b -> b) ->
  (Float -> Float -> b -> b -> b) ->
  (b -> b -> b) ->
  Dibujo a ->
  b

foldDib fFig fRot fEsp fRot45 fAp fJun fEnc dibujo =
  case dibujo of
    Figura a      -> fFig a
    Rotar d       -> fRot (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d)
    Espejar d     -> fEsp (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d)
    Rot45 d       -> fRot45 (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d)
    Apilar a b d1 d2 -> fAp a b (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d1) (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d2)
    Juntar a b d1 d2 -> fJun a b (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d1) (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d2)
    Encimar d1 d2 -> fEnc (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d1) (foldDib fFig fRot fEsp fRot45 fAp fJun fEnc d2)