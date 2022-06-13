
sum([], 0).
sum([H|T], Sum) :-
   sum(T, Rest),
   Sum is H + Rest.


deviationsquaredsum([],_,0).
deviationsquaredsum([H|T], Avg, Dev2):-
   deviationsquaredsum(T, Avg, R),
   Dev2 is (H - Avg)*(H - Avg) + R.

myvariance(List, V):-
   length(List, L),
   L > 0,
   sum( List, Sum ),
   Avg is (Sum/L),
   deviationsquaredsum(List, Avg, D),
   V is D/L.



