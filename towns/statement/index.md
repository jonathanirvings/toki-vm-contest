# Connected Towns

Pak Dengklek lives in Indonesia, a country consisting of $N$ towns numbered from $0$ to $N - 1$.
For every pair of towns, there is a one-way road going from one town to the other.
Pak Dengklek has no information on the direction of the roads, but Pak Chanek has offered to help him.

Pak Dengklek is allowed to ask Pak Chanek at most $40\,000$ questions.
For each question in turn, Pak Dengklek chooses a pair of towns and Pak Chanek tells him the direction of the road connecting those two towns.

Pak Dengklek wants to return the index of a town with at most one outgoing road.
If there is more than one such town, Pak Dengklek can return the index of any such town.
If there is no such town, return $-1$.


## Implementation Details

You should implement the following procedure:

```
void find_town(int N)
```

* $N$: the number of towns in Indonesia.
* This procedure should return the index of a town with at most one outgoing road, or $-1$ if there is no such town.

The above procedure can make calls to the following procedure:

```
bool check_road(int A, int B)
```

* $A, B$: indices of a pair of towns to be asked to Pak Chanek.
* $A$ and $B$ must be **distinct** integers from $0$ to $N - 1$ inclusive.
* The procedure returns `true` if there is a road going from town $A$ to town $B$ and returns `false` if there is a road going from town $B$ to town $A$.
* This procedure can be called at most $40\,000$ times.


## Example

### Example 1

Consider a scenario in which there are $3$ towns and the roads connecting the towns are illustrated by the following image:

![](towns-1.png)

The procedure `find_town` is called in the following way:

```
find_town(3)
```

This procedure may call `check_road(0, 1)`, which (in this scenario) returns `true`.

At this point, there is sufficient information to conclude that town $1$ has at most one outgoing road.
Therefore, the procedure may return $1$.

### Example 2

Consider a scenario in which there are $5$ towns and the roads connecting the towns are illustrated by the following image:

![](towns-2.png)

The procedure `find_town` is called in the following way:

```
find_town(5)
```

In this scenario, there is no town with at most one outgoing road.
Therefore, the procedure should return $-1$.


## Constraints

* $3 \le N \le 2000$


## Subtasks and scoring

In some test cases the behaviour of the grader is adaptive.
This means that in these test cases the grader does not have a fixed configuration of road directions.
Instead, the answers given by the grader may depend on the questions asked by your solution.
It is guaranteed that the grader answers in such a way that after each answer there is at least one configuration of road directions consistent with all the answers given so far.

1. (10 points) $N \le 250$
2. (90 points) No additional constraints.

In subtask 2 you can obtain a partial score.
Let $Q$ be the maximum number of calls to the procedure `check_road` among all test cases in this subtask.
Then, your score for this subtask is calculated according to the following table:

| Questions                 | Score                                                                |
| ------------------------- | -------------------------------------------------------------------- |
| $20\,000 < Q \le 40\,000$ | $20$                                                                 |
| $8\,000 < Q \le 20\,000$  | $\left \lfloor 90 - 70 \sqrt{\frac{Q - 8000}{12000}} \right \rfloor$ |
| $Q \le 8\,000$            | $90$                                                                 |

## Sample Grader

The sample grader reads a 2D array $R$ of integers representing the roads in Indonesia.
For all $0 \le i, j \le N - 1$ ($i \ne j$), $R[i][j] = 1$ means there is a road going from town $i$ to town $j$ and $R[i][j] = 0$ means there is a road going from town $j$ to town $i$.
For all $0 \le i \le N - 1$, $R[i][i]$ should be $0$.

The sample grader reads input in the following format:

* line $1$: $N$
* line $2 + i$ ($0 \le i \le N - 1$): $R[i][0] \; R[i][1] \; \ldots \; R[i][N - 1]$

The output of sample grader is in the following format:

* line $1$: the return value of `find_town`.
* line $2$: the number of calls to `check_road`.

Note that the sample grader is not adaptive.
