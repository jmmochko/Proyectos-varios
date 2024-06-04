---
title: Laboratorio de Funcional
author: José Mochkofsky, Juana Balduini, Franco Bustos
---
La consigna del laboratorio está en https://tinyurl.com/funcional-2024-famaf

# Uso (En linux)
-- Compilación
$ cabal configure
$ cabal build

-- Pedir lista de dibujos
$ cabal run dibujos -- lista

-- Para correr dibujos, especificamente Escher como ejemplo
$ cabal run dibujos Escher
-- por default hace un Escher de nivel 3, de querer modificarse ir a Main.hs y cambiar el valor de nivelEscher
-- si nivelEscher <= 0 se rompe

-- Correr tests
-- Test del modulo Pred
$ cabal test predicados
-- Test del modulo Dibujo
$ cabal test TestDibujo
-- No usamos "dibujo" ya que el modulo se llama igual y los nombres duplicados generan problemas de compilación

# 1. Tareas
Pueden usar esta checklist para indicar el avance.

## Verificación de que pueden hacer las cosas.
- [✓] Haskell instalado y testeos provistos funcionando. (En Install.md están las instrucciones para instalar.)

## 1.1. Lenguaje
- [✓] Módulo `Dibujo.hs` con el tipo `Dibujo` y combinadores. Puntos 1 a 3 de la consigna.
- [✓] Definición de funciones (esquemas) para la manipulación de dibujos.
- [✓] Módulo `Pred.hs`. Punto extra si definen predicados para transformaciones innecesarias (por ejemplo, espejar dos veces es la identidad).

## 1.2. Interpretación geométrica
- [✓] Módulo `Interp.hs`.

## 1.3. Expresión artística (Utilizar el lenguaje)
- [ ] El dibujo de `Dibujos/Feo.hs` se ve lindo.
- [✓] Módulo `Dibujos/Grilla.hs`.
- [✓] Módulo `Dibujos/Escher.hs`.
- [✓] Listado de dibujos en `Main.hs`.

## 1.4 Tests
- [✓] Tests para `Dibujo.hs`.
- [✓] Tests para `Pred.hs`.

# 2. Experiencia
Completar

# 3. Preguntas
Al responder tranformar cada pregunta en una subsección para que sea más fácil de leer.

1. ¿Por qué están separadas las funcionalidades en los módulos indicados? Explicar detalladamente la responsabilidad de cada módulo.
        Separar las funcionalidades en modulos ayuda a navegar el codigo de manera mas eficiente. 
        Ademas facicilta el proceso de debuggeo ya que los bugs o errores serán propios de algún modulo en particular.
        El modulo Dibujo contiene la definicion del tipo Dibujo y las funciones requeridas para trabajar con este.
        El modulo Interp contiene las funciones necesarias para pasar de un Dibujo a Input/Output.
        El modulo Pred contiene definiciones de predicados para dibujos que ayudan a razonar sobre los mismos.

2. ¿Por qué las figuras básicas no están incluidas en la definición del lenguaje, y en vez de eso, es un parámetro del tipo?
        Al hacer que las figuras básicas sean un parámetro del tipo en lugar de estar directamente definidas en el lenguaje, se hace posible crear un tipo de datos Dibujo que pueda contener cualquier tipo de figura, ej: círculo, rectángulo, cuadrado, etc, puedan ser definidas luego.
        
3. ¿Qué ventaja tiene utilizar una función de `fold` sobre hacer pattern-matching directo?
        Hacer pattern matching directo sobre el tipo Dibujo requiere el uso directo de los constructores del mismo, cosa que es preferible evitar en todo modulo distinto al que tiene la definicion de los mismos. Si se quisiera realizar un cambio en la estructura de Dibujo, adaptar 'fold' a ese cambio es mucho más fácil que hacerlo con todas las funciones que utilizan fold en otros modulos.
        Ademas, como el tipo tiene muchos constructores, el pattern-macthing se hace extenso. Usar fold nos permite escribir codigo mas compacto y facilmente entendible.

4. ¿Cuál es la diferencia entre los predicados definidos en Pred.hs y los tests?
        La función de los tests es comprobar que cada modulo testeado funciona correctamente

# 4. Extras
Completar si hacen algo.