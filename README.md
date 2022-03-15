# PhilosoperAlg
Solution to the Philosofer Problem using multy prossesing

# What is the Philosofer problem?
Five philosophers, numbered from 0 through 4, live in a house where the table is laid for them; each philosopher has their own place at the table. Their only problem – besides those of philosophy – is that the dish served is a very difficult kind of spaghetti, that has to be eaten with two forks. There are two forks next to each plate, so that presents no difficulty: as a consequence, however, no two neighbours may be eating simultaneously.

#My solution 
each process represent one philosofor and each fork is var wich have lock on it when someone use it 
the real problem in this case is "dead lock" or "starving" which are 2 situations we don't want to happend
