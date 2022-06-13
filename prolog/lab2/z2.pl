remover( _, [], []).
remover(R, [R|T], T).
remover(R, [H|T], [H|T2]) :- H \= R, remover( R, T, T2). % usuwam z listy L pojedyncze wystopieni elementu X i zapisuje w liscie W


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


