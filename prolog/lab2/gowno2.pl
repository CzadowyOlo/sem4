suma_listy([], 0).
suma_listy([H|T], Sum) :- sum_list(T, Rest),  Sum is H + Rest.


counter(X, [X|T], A, Acc) :- Anew is A+1, counter(X, T, Anew, Acc).
counter(X, [H|T], A, Acc) :- counter(X, T, A, Acc), X \= H.
counter(_, [], Acc, Acc).
jednokrotnie(X, L) :- counter(X, L, 0, Acc), Acc is 1.
dwukrotnie(X, L) :- counter(X, L, 0, Acc), Acc is 2.

pisz_liste([]).
pisz_liste([H|T]) :- print(H), nl, pisz_liste(T).


lista_pom(N, L) :-
    findall(Num1, between(1, N, Num1), L1),
    findall(Num2, between(1, N, Num2), L2),
    append(L1,L2,L).

odl(X,[X|_], 0).
odl(X, [_ | L], Ile) :- odl(X,L,IleNew), Ile is IleNew+1.


odl2([H|T],Ile) :- odl(H,T,Ile).

odlall([],0).
odlall([H|T],Ile) :-
    odl(H,T,Ile),
    odlall(T,IleNew).


lista(N,X) :- lista_pom(N,L), permutation(L,X).
