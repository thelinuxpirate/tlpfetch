module Main where

import System.Environment
import System.IO
import Data.List (isPrefixOf)
import Control.Monad

-- Check if a file has a .tlp extension
isTlpFile :: FilePath -> Bool
isTlpFile filePath = ".tlp" `isSuffixOf` filePath

-- Extract the value from a line in the format "KEY=value"
extractValue :: String -> String -> String
extractValue key content =
  case dropWhile (not . isPrefixOf (key ++ "=")) (lines content) of
    [] -> "Unknown"
    (line:_) -> drop (length key + 1) line

main :: IO ()
main = do
  args <- getArgs

  case args of
    [filePath] -> do
      -- Check if the file has a .tlp extension
      if isTlpFile filePath
        then do
          contents <- readFile filePath
          putStrLn "Contents of the .tlp file:"
          putStrLn contents
        else
          putStrLn "The provided file is not a .tlp file."
    _ -> putStrLn "Usage: tlpfetch <filename.tlp>"
  
  contents <- readFile "/etc/os-release"
  let name = extractValue "NAME" contents
  putStrLn $ "Distribution Name: " ++ name
