prime(LO, HO, X) :-  between(LO, HO, X), isprime(X).

isprime(X) :- X > 1, not(hasdivisor(X, 2)).

hasdivisor(X, Y) :- (Y-1<X/2),(divisible(X,Y);(Z is Y+1, hasdivisor(X, Z))).

divisible(X,Y) :- 0 is X mod Y.
/* koniec */
