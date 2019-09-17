import System.IO
import System.Directory

-- Utilize a função start para executar o programa.

start :: IO()
start = do
    let inFile = "databaseToHaskell.txt"
    fileContent <- readFile inFile -- lê todo o conteúdo do arquivo de entrada e salva em fileContent
    let list = lines fileContent -- list recebe as linhas do arquivo separadamente, gerando uma lista de linhas
    checkFile -- verifica se o arquivo existe
    putStrLn ("\n====================ROTAS====================\n")
    calcTime list 2 -- Informa para a função a lista, e a posição da primeira distância na lista
    putStrLn ("\nArquivo databaseToProlog.txt gerado com sucesso!")
        
calcTime :: [String] -> Int -> IO()
calcTime list posDistancia = do
    let cidOrigem = list !! (posDistancia - 2) -- Lê a cidade de origem, que está 2 posições antes da distância 
    let cidDestino = list !! (posDistancia - 1) -- Lê a cidade de destino, que está a 1 posição antes da distância
    let distancia = list !! posDistancia -- Lê a distancia para mandar para a função de escrita do arquivo
    let tempo = (read (list !! posDistancia) :: Float) * 1.5 -- Lê a distancia na posição informada, converte para float e multiplica por 1.5
    let tempoStr = (show tempo :: String) -- Converte o tempo calculado em String para ser gravado no arquivo
    fileWrite cidOrigem cidDestino distancia tempoStr 
    if (posDistancia + 3) < (length list) -- Caso o tamanho da lista seja menor que posição que distancia está acessando, então para a recursão, senao, continua lendo o arquivo recursivamente 
        then calcTime list (posDistancia + 3) -- posição da próxima distância 
    else return()

-- =================MANIPULAÇÃO DE ARQUIVOS=================
--Verifica se o arquivo de saída existe e apaga o conteúdo dele, senão irá duplicar o conteúdo
checkFile :: IO()
checkFile = do
    let file = "databaseToProlog.txt"
    fileExists <- doesFileExist file --retorna true se o arquivo existe
    if fileExists
        then removeFile file -- remove o arquivo
    else return()

-- Recebe uma origem, destino, distancia e tempo em strings e escreve no arquivo destinado ao prolog 
-- e converte os dados para o formato de um fato do prolog, para que o prolog consiga interpretar 
fileWrite :: String-> String -> String -> String -> IO()
fileWrite origem destino distancia tempo =  do
    let fileName = "databaseToProlog.txt"
    file <- openFile fileName AppendMode
    putStrLn ("rota(" ++ "\"" ++ origem ++ "\"" ++ ", " ++ "\"" ++ destino ++ "\"" ++ ", " ++ tempo ++ ", " ++ distancia ++ ").")

    hPutStrLn file ("rota(" ++ "\"" ++ origem ++ "\"" ++ ", " ++ "\"" ++ destino ++ "\"" ++ ", " ++ tempo ++ ", " ++ distancia ++ ").")
    hClose file