:- dynamic rota/4.

% Utilize a função loadFile. para carregar os fatos do arquivo.
% Utilize a fução maps(Origem,Destino) para executar o programa.

maps(X,Y):-
     setof(_,caminho(X,Y,T,D,R),_),
     write("\nCaminho da viagem: "),
     imprimir(R),
     write("\nTempo total de viagem: "), write(T), write(" minutos."),
     write("\nDistancia total de viagem: "), write(D), write(" km").

caminho(X,Y,T,D,[X,Y|[]]):-
     rota(X,Y,T,D).

caminho(X,Y,T,D,[X|AUX]):-
     rota(X,Z,T1,D1),
     caminho(Z,Y,T2,D2,AUX),
     T is (T1 + T2),
     D is (D1 + D2).

imprimir([X]):-
      write(X), !.
imprimir([X|Y]):-
     write(X),
     write(" => "),
     imprimir(Y).

%============== Manipulacao do arquivo ==============
loadFile:-
     open("databaseToProlog.txt", read, File),
     lerArquivo(File,_),
     close(File).

lerArquivo(File,[]):-
     at_end_of_stream(File),
     write("Arquivo carregado!"), !.

lerArquivo(F,[H|T]):-
     \+ at_end_of_stream(F),
     read(F,H),
     lerArquivo(F,T),
     assertz(H).
