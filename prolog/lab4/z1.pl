% zadanie 1

equasion([X],X,X). % stops when  singleton list and element = our given result

equasion(Lista,H, X * Y):- % here we have variance with multiplying
    helper(Lista,X,Y,H1,H2),
    H is H1 * H2.


equasion(Lista,H, X / Y):- % and there with dividing
    helper(Lista,X,Y,H1,H2),
    H2 =\= 0, % to avoid illegal operand dividing by zero
    H is H1 / H2.


equasion(Lista,H, X + Y):- % like above, for adding
    helper(Lista,X,Y,H1,H2),
    H is H1 + H2.


equasion(Lista,H, X - Y):- %variance for list editing with substraction
    helper(Lista,X,Y,H1,H2),
    H is H1 - H2.


    % function for spliting our list where we can do arithmetics, 
    %like this permutation on hetmany example
helper(Lista,R1,R2,H1,H2):-
    append([X1|X2], [Y1|Y2], Lista),
    equasion([X1|X2],H1, R1),
    equasion([Y1|Y2],H2, R2).

