nparzysta_dlugosc(L):-
    length(L,Y), Z is Y mod 2, Z = 1.

rhead([_|Tail], Tail). % usuwanie glowy
rtail([_], []).
rtail([X|Xs], [X|Rt]):- % usuwanie ogona / ost elemele
    rtail(Xs, Rt).



skrocona(L, X, Y):- % lista Y to L bez glowy i ostatniego elementu
    rhead(L,X),
    rtail(X, Y).


% srodkowy([], _):-!, fail.

srodkowy([X], X):-!. % czekam az X bedzie jedynym elementem listy
srodkowy(L, X):-
    skrocona(L,_,Y),
    srodkowy(Y, X).


