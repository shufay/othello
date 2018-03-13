Link Dismissal
Shu Fay and Kenyon

Strategies:
Minimax
Heuristic function using:
        Simple point values for various spaces:
        +300 points for a corner
        -30 points for spaces adjacent to a corner
        +5 points for an edge
        +1 point for other spaces
    Very heavy priority on mobility:
        +3 points for each reachable space on the outer ring (two thick).
        +18 points for each reachable space in the 4x4 interior.
        -9 points for each reachable space in the outer ring for opponent.
        -36 points for each reachable space in 4x4 interior for opponent.
    When a victory or loss is detected, it is valued more highly than any
        normal heuristic value, but the bot tries to find the victory that
        gives the highest score overall as well.
Alpha beta pruning
Iterative deepening:
    8 seconds allotted per turn (or until a minimum search depth of 8)

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
