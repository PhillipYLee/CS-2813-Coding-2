# CS-2813-Coding-2
## Instructions on how to run your program (the command to execute it)
- Go into directory with the coding2.cpp and coding2.exe file.
- Add input.txt file 
- run coding2.exe


## Input.txt
``
6 5 \
0 1 \
1 2 \
2 3 \
3 4 \
4 5
``
## Expected Output
Reflexive = False
Symmetric = False
Transitive = False
|R+| = 15


## A brief note (2–3 sentences) confirming your program produces the expected output and describing which method you used (Warshall or DFS/BFS)
I used Warshall for this lab to compute the transitive closure. 
I verified the program produces the expected output for the sample input (Reflexive = False, Symmetric = False, Transitive = False, |R+| = 15),
which showed that the chain relation from the input gives all 15 reachable pairs in its closure.
