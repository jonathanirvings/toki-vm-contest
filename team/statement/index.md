# Team Contest

ICPC (Inter-Collegiate Programming Contest) is a programming contest for university students.
ICPC is participated by teams of three programmers.

Your university is registering several teams to participate in ICPC this year.
There are $N$ eligible programmers numbered from $0$ to $N - 1$.
The programmer $i$ has a skill level of $L[i]$.
The skill level of a team consisting of programmer $i$, $j$, and $k$ is $\min(L[i], L[j], L[k]) + \max(L[i], L[j], L[k])$.

You want to only register teams with a skill level of strictly more than $K$.
Each programmer may only be assigned to at most one registered team.
You want to know the maximum number of teams you can register.

## Implementation Details

You should implement the following procedure:

```
int maximum_teams(int N, int K, int[] L);
```

* $N$: the number of programmers.
* $K$: the skill level limit of the registered teams.
* $L$: an array of length $L$, where $L[i]$ is the skill level of the programmer $i$.
* This procedure should return the maximum number of teams you can register.
* This procedure is called exactly once.

## Examples

### Example 1

Consider the following call:

```
maximum_teams(8, 6, [5, 4, 6, 2, 3, 2, 1, 1])
```

You can register a team with programmer $0$, $3$, and $5$ (with skill levels $5$, $2$, $2$ respectively) and a team with programmer $1$, $2$, and $4$ (with skill levels $4$, $6$, $3$ respectively).
There is no way to register more than two teams. 
Therefore, the procedure `maximum_teams` should return $2$.

## Constraints

* $1 \le N \le 100\,000$
* $1 \le K \le 10^8$
* $1 \le A[i] \le 10^8$ (for all $0 \le i \le N - 1$)

## Subtasks

1. (14 points) $N \le 8$
2. (39 points) $N \le 1000$
3. (47 points) No additional constraints.

## Sample Grader

The sample grader reads the input in the following format:

* line $1$: $N \; K$
* line $2$: $L[0] \; L[1] \; \ldots \; L[N - 1]$

The output of the sample grader is in the following format:

* line $1$: return value of `maximum_teams`.
