
max_sum(L,X) :-
    max_sum_finder(L,0,0,X).


% lista, Ost - ostatni max ciag,A - aktualny ciag, T - reszta

max_sum_finder([],Ost,_,Ost). % dla pustej zwraca 0
max_sum_finder([H|T],Ost,A,X) :-
    A1 is H + A,
    ( A1 > 0 ->(A2 is A1, % jesli a1 > 0, to przepisuje je do a2 i jesli a2 jest wieksze niz ost
               (A2 > Ost -> Ost1 is A2 ; Ost1 is Ost)) % to przepisuje a2 do ost1, a jak nie to ost do ost1
               ; (A2 is 0, Ost1 is Ost )), % jesli a1 <= 0, to a2 jest 0, ost przepisuje do ost1
    max_sum_finder(T,Ost1,A2,X).

    %czyli licze najwieksza sume od glowy do pewnego momentu, ktory zapisuje, A2>Ost, tak eliminuje niepotrzebne ogony
    %potem robie to samo od glowa+1, tak eliminuje niepotzrebne glowy