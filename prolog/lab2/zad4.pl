remover( _, [], []).
remover(R, [R|T], T).
remover(R, [H|T], [H|T2]) :- H \= R, remover( R, T, T2).


jedno(X, L):-
    member(X,L),
    remover(X,L,W),
    not(member(X,W)).

dwa(X, L):-
    member(X,L),
    remover(X,L,W),
    member(X,W),
    remover(X,W,Z),
    not(member(X,Z)).

do_list(N, L):-
  findall(Num, between(1, N, Num), L).

insertAtEnd(X,Y,Z) :- append(Y,[X],Z).
% X is elem, Y is old list, Z is new list

% dodaj liste Pom od 1 do N,
% if (dwa(member(X,Pom), L))
% else add(member(X,Pom), L)

/**
lista(N,L):-
    do_list(N,Pom).

lista(N,L):-
    not(dwa(member(X,Pom),L)),
    insertAtEnd(member(X,Pom),L,Temp),
    L is Temp.
**/



