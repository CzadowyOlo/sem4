above(B1,B2) :-
    on(B1,B2).
above(B1,B2) :-
    on(B1,B0), above(B0,B2).

on(a,b).
on(b,c).
on(c,d).
on(d,e).
/*koniec*/
