I started off writing the heuristic "doMove" function, then implemented
the alpha-beta pruning and tuned the heuristic functions. Kenyon worked 
on the minimax algorithm, set up the heuristic functions and wrote
tests. We cleaned up each other's code along the way.

Improvements
-------------
We took into account coin parity according to weights assigned to
positions on the board, e.g. the corners have greatest weight, followed
by the edges; the cells adjacent to corners had negative weight. 

We also looked at mobility, especially inward mobility, in deciding the 
next move. We aimed to maximize our mobility while minimizing the 
opponent's mobility. We prioritized minimizing opponent mobility: moves
where the opponent gained mobility were weighted more heavily than
moves where we gained mobility.

We implemented alpha-beta pruning together with iterative deepening. A 
maximum time of 4s is allocated for each to move to search to the 
highest depth possible. 

 