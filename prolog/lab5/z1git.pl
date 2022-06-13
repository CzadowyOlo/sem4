%open('ex1.prog', read, X), scanner(X, Y), close(X), write(Y).
%GRAMMAR:


%key words:
key(read).
key(write).
key(if).
key(then).
key(else).
key(fi).
key(while).
key(do).
key(od).
key(and).
key(or).
key(mod).
%----------------------------------------------------%

%int:
int([H|T]) :- char_type(H,digit), int(T).
int([]) :- !.
%-----------------------------------------------------%

%identifiers by upper letter
id([H|T]) :-
	char_type(H,upper), id(T).
id([]) :-!.

%white signs:
ws(' ').
ws('\t').
ws('\n').
%--------------------------------------------------------%

% sep(SEPARATOR) where SEPARATOR is one of seperators in language Imperator:
% ’;’, ’+’, ’-’, ’*’, ’/’ ’(’, ’)’, ’<’, ’>’, ’=<’, ’>=’, ’:=’, ’=’, ’/=’

sep(';'). 
sep('+'). 
sep('-').
sep('*').
sep('/').
sep('(').
sep(')').
sep('<').
sep('>').
sep('=<').
sep('>=').
sep(':=').
sep('=').
sep('/=').

%sep(SEPARATOR) :- member(SEPARATOR,[';','+','-','*','/','(',')','<','>','=<','>=',':=','=','/=']).

readInput('end_of_file',_,[],[]):-
		!.

readInput(C1,C2,L,OUT) :- %when white sign
		ws(C2),
		get_char(C3),readInput(C2,C3,T,OUT2), %skip
		reduce_right(T,OUT2,OUT),L=[C1]. %deleting prev char

readInput(C1,C2,L,[OUTH|OUTT]) :- %when separator
		sep(C2),
		get_char(C3),readInput(C2,C3,T,OUT2),
		(	
			(atom_chars(S,[C1,C2]),sep(S),reduce_right(T,OUT2,OUTT),OUTH=sep(S),L=[]);
			(reduce_right(T,OUT2,OUTT),OUTH=sep(C2),L=[C1])
		).
readInput(C1,C2,[C1|T],OUT) :-
		get_char(C3),readInput(C2,C3,T,OUT).

%deleting readed char from current stream
reduce_right([_|[]],X,X).
reduce_right([_|T],IN,OUT) :- 
		atom_token(T,TOKEN),OUT=[TOKEN|IN].	

atom_token(L,Y) :-
			(id(L),atom_chars(T,L),Y=id(T));
			(int(L),atom_chars(T,L),Y=int(T));
			(atom_chars(T,L),key(T),Y=key(T)).

scanner(STR,Y) :-
		set_input(STR), % seeing file - Set the current input stream to become Stream.
		get_char(C), % get character from stream input
		readInput(' ',C,L,P),!,
		reduce_right(L,P,Y),!.
 