% -------------------------------------
% 1. Basic Relationships (Facts)
% -------------------------------------

% parent(Parent, Child)
parent(john, mary).
parent(john, mike).
parent(susan, mary).
parent(susan, mike).

parent(mary, alice).
parent(mary, bob).
parent(david, alice).
parent(david, bob).

parent(mike, tom).
parent(mike, emma).
parent(lisa, tom).
parent(lisa, emma).

% Gender Information
male(john).
male(mike).
male(david).
male(bob).
male(tom).

female(susan).
female(mary).
female(lisa).
female(alice).
female(emma).


% -------------------------------------
% 2. Derived Relationships (Rules)
% -------------------------------------

% (a) Grandparent
% X is grandparent of Y if X is parent of Z and Z is parent of Y
grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

% (b) Sibling
% X and Y are siblings if they share at least one parent and are not the same person
sibling(X, Y) :-
    parent(P, X),
    parent(P, Y),
    X \= Y.

% (c) Cousin
% X and Y are cousins if their parents are siblings
cousin(X, Y) :-
    parent(P1, X),
    parent(P2, Y),
    sibling(P1, P2),
    X \= Y.


% -------------------------------------
% 3. Logical Inference Queries
% -------------------------------------

% (a) children(Parent, Child)
% Lists all children of a given parent
children(Parent, Child) :-
    parent(Parent, Child).

% (b) siblings(Person, Sibling)
% Lists all siblings of a given person
siblings(Person, Sibling) :-
    sibling(Person, Sibling).

% (c) is_cousin(Person1, Person2)
% Checks if two people are cousins
is_cousin(Person1, Person2) :-
    cousin(Person1, Person2).


% -------------------------------------
% 4. Recursive Logic
% -------------------------------------

% descendant(Ancestor, Descendant)
% A descendant is a child or recursively a child of a descendant
descendant(Ancestor, Descendant) :-
    parent(Ancestor, Descendant).

descendant(Ancestor, Descendant) :-
    parent(Ancestor, Intermediate),
    descendant(Intermediate, Descendant).