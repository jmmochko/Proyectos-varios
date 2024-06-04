module Main (main) where
import System.Exit (exitFailure, exitSuccess)
import Pred
import Dibujo 

oneandtwo :: Pred Integer
oneandtwo = andP (==1) (==2)

oneortwo :: Pred Integer
oneortwo = orP (==1) (==2)

fig :: Dibujo Integer
fig = encimar (figura 1) (figura 2)

fig2 :: Dibujo Integer
fig2 = cambiar (/=1) (\x -> figura (x - 1)) fig


main :: IO ()
main = do
    if anyDib (==1) fig
                then putStrLn "True, Have 1s"
                else exitFailure
    if anyDib (==2) fig
                then putStrLn "True, Have 2s"
                else exitFailure
    if allDib (==1) fig
                then exitFailure
                else putStrLn "False, Not All 1s"
    if allDib (==2) fig
                then exitFailure
                else putStrLn "False, Not All 2s"
    if allDib oneandtwo fig
                then exitFailure
                else putStrLn "False, Imposible for an int to be both 1 and 2"
    if allDib oneortwo fig
                then putStrLn "True, Have both 1 or 2 on every figure"
                else exitFailure
    if anyDib (/=1) fig2
                then exitFailure
                else putStrLn "False, Have no 2s"
    exitSuccess
    