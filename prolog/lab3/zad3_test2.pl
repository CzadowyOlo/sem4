even_permutation([],[]).
% posiadajac parzysta permutacje dodajemy nowy element na
% nieparzyste miejsce
even_permutation([H|R],X) :-
    even_permutation(R,Z),
    add_to_odd(Z,H,X).
% albo posiadajac nieparzysta permutacje dodajemy element na parzyste
% miejsce
even_permutation([H|R],X) :-
    odd_permutation(R,Z),
    add_to_even(Z,H,X).



% pierwszy element wpisalem recznie by przyspieszyc algorytm ( mozna go
% uzyskac od parzystej permutacji)
odd_permutation([A,B],[B,A]) :- !.
% posiadajac nieparzysta permutacje dodajemy element na nieparzyste
% miejsce
odd_permutation([H|R],X) :-
    odd_permutation(R,Z),
    add_to_odd(Z,H,X).
% albo posiadajac parzysta permutacje dodajemy element na parzyste
% miejsce
odd_permutation([H|R],X) :-
    even_permutation(R,Z),
    add_to_even(Z,H,X).
% lista poczatkowa,X - wkładany element, R - wynik
add_to_odd(L,X,[X|L]).
add_to_odd([A,B|L],X,[A,B|Y]) :-
    add_to_odd(L,X,Y).
add_to_even([H|R],X,[H|Y]) :-
    add_to_odd(R,X,Y).