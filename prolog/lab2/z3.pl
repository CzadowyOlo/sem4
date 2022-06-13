arc(a,b).
arc(b,a).
arc(b,c).
arc(c,d).

conn(X,Y,L):-
    arc(X,Z),
    not(member(Z,L)), % pomijam te polaczenia, gdzie juz bylem
    (
        Y = Z;
        conn(Z, Y, [Z|L]) % wpisuje do listy wezly, ktore juz przerobilem, zeby sei nie dublowac
    ).
osiogalny(X,X):-true.
osiogalny(X,Y):-conn(X,Y,[X]).
