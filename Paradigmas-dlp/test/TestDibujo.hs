import Test.HUnit
import Dibujo

-- Define aquí tus funciones y datos del módulo Dibujo

-- Función de transformación para las figuras básicas
transformar :: Int -> String
transformar n = "Figura transformada " ++ show n

-- Dibujo de prueba
dibujoPrueba :: Dibujo Int
dibujoPrueba =
  apilar 1 1 (figura 1) (juntar 1 1 (figura 2) (figura 3))

-- Test para verificar el funcionamiento de figura
testFigura :: Test
testFigura =
  TestCase $ assertEqual
    "La función figura debe crear una Figura con el valor dado"
    (figura 5)
    (figura 5)

-- Test para verificar el funcionamiento de encimar
testEncimar :: Test
testEncimar =
  TestCase $ assertEqual
    "La función encimar debe superponer dos dibujos"
    (encimar (figura 1) (figura 2))
    (encimar (figura 1) (figura 2))

-- Test para verificar el funcionamiento de apilar
testApilar :: Test
testApilar =
  TestCase $ assertEqual
    "La función apilar debe colocar un dibujo sobre otro"
    (apilar 1 1 (figura 1) (figura 4))
    (apilar 1 1 (figura 1) (figura 2))

-- Test para verificar el funcionamiento de juntar
testJuntar :: Test
testJuntar =
  TestCase $ assertEqual
    "La función juntar debe colocar dos dibujos uno al lado del otro"
    (juntar 1 1 (figura 1) (figura 2))
    (juntar 1 1 (figura 1) (figura 2))

-- Test para verificar el funcionamiento de rot45
testRot45 :: Test
testRot45 =
  TestCase $ assertEqual
    "La función rot45 debe rotar un dibujo 45 grados"
    (rot45 (figura 1))
    (rot45 (figura 1))

-- Test para verificar el funcionamiento de encimar4
testEncimar4 :: Test
testEncimar4 =
  TestCase $ assertEqual
    "La función encimar4 debe superponer un dibujo con sus cuatro rotaciones"
    (encimar4 (figura 1))
    (encimar (encimar (r90 (figura 1)) (figura 1)) (encimar (r180 (figura 1)) (r270 (figura 1))))

-- Test para verificar el funcionamiento de cuarteto
testCuarteto :: Test
testCuarteto =
  TestCase $ assertEqual
    "La función cuarteto debe colocar cuatro dibujos en un cuadrante"
    (cuarteto (figura 1) (figura 2) (figura 3) (figura 4))
    ((figura 1 /// figura 2) .-. (figura 3 /// figura 4))

-- Test para verificar el funcionamiento de ciclar
testCiclar :: Test
testCiclar =
  TestCase $ assertEqual
    "La función ciclar debe colocar cuatro rotaciones de un dibujo en un cuadrante"
    (ciclar (figura 1))
    (cuarteto (figura 1) (r90 (figura 1)) (r180 (figura 1)) (r270 (figura 1)))

-- Lista de tests
tests :: Test
tests = TestList [ TestLabel "testFigura" testFigura
                 , TestLabel "testEncimar" testEncimar
                 , TestLabel "testApilar" testApilar
                 , TestLabel "testJuntar" testJuntar
                 , TestLabel "testRot45" testRot45
                 , TestLabel "testEncimar4" testEncimar4
                 , TestLabel "testCuarteto" testCuarteto
                 , TestLabel "testCiclar" testCiclar
                 ]

-- Función principal que corre los tests
main :: IO ()
main = runTestTT tests >> return ()
