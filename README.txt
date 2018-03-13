Link Dismissal
Shu Fay and Kenyon

Strategies:
Minimax
Heuristic function using:
        Simple point values for various spaces:
        +300 points for a corner
        -30 points for spaces adjacent to a corner
        +20 points for an edge
        +1 point for other spaces
    Very heavy priority on mobility:
        +3 points for each reachable space on cells with 1 < x, y < 7.
        +18 points for each reachable space on other cells.
        -45 points for each reachable space on cells with 1 < x, y < 7.
        -15 points for each reachable space on other cells.
    When a victory or loss is detected, it is valued more highly than any
        normal heuristic value, but the bot tries to find the victory that
        gives the highest score overall as well.
Alpha beta pruning
Iterative deepening:
    4 seconds allotted per turn, starting with a depth of 3 until time runs out.

Work split:
Shu Fay:
    Wrote initial no-minimax heuristic bot
    Implemented alpha-beta
    Implemented iterative deepening
    Improved heuristic with tuned values for mobility.
Kenyon:
    Write initial minimax function
    Wrote space-dependent & mobility heuristic
    Test and debug functions
    Makefile restructuring
