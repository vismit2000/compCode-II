// https://leetcode.com/discuss/interview-question/1009035/Eightfold.ai-or-OA-or-Terminator-X/

/*
Terminator X
You are the engineering head at Robotica, a military robotics company, and you have the following samples of robots:

N denoting the number of Robots.
A[i] denoting the Weapon power of Robot i.
B[i] denoting the Shield Power of Robot i.
Q queries in which each query contains two integers X and Y.
For each query your task is to find the number of Robots that have weapon power greater than X and shield power greater than Y.
Input Format

The first line contains an integer N denoting the number of Robots.
The second line contains N space separated integers A[i] denoting the weapon power of the ith Robot.
The third line contains N space separated integers B[i] denoting the shield power of the ith Robot.
The next line contains an integer Q denoting the number of queries.
Each of the next Q lines contains two space separated integers X and Y.
Output Format
For each query, print the number of Robots that have both weapon power greater than X and shield power greater than Y.

Constraints
1 <= N, Q <= 2 * (10^5)
-(10^9) <= A[i], B[i] <= (10^9)

Sample Input 1
5
16 11 10 20 18
11 9 2 2 4
5
3 20
4 5
9 1
4 6
8 4

Sample Output 1
0 2 5 2 2


Approach: I created a merge sort segment tree. Sorted the array based on X, and stored it in segment tree. Each node contains the segment of array 
sorted on basis of Y. Each query takes (logN)^2.

*/

public static void main(String[] args) {
	// TODO Auto-generated method stub
	Scanner scn = new Scanner(System.in);
	int n = scn.nextInt();
	int[] a = new int[n];
	for (int i = 0; i < n; ++i) {
		a[i] = scn.nextInt();
	}
	int[] b = new int[n];
	for (int i = 0; i < n; ++i) {
		b[i] = scn.nextInt();
	}

	Pair[] arr = new Pair[n];
	for (int i = 0; i < n; ++i) {
		arr[i] = new Pair(a[i], b[i]);
	}
	Arrays.sort(arr);
	segmentTree = new ArrayList[4 * n];
	build(0, 0, n - 1, arr);
	int q = scn.nextInt();
	for (int i = 0; i < q; ++i) {
		int x = scn.nextInt();
		int y = scn.nextInt();

		int pos = firstPos(x, arr);
		int ans = query(0, 0, n - 1, pos, n - 1, y);
		System.out.print(ans+" ");
	}
}

public static int query(int si, int ss, int se, int qs, int qe, int x) {
	if (qe < ss || qs > se) {
		return 0;
	}

	if (qs <= ss && qe >= se) {
		return find(si, x);
	}

	int mid = (ss + se) / 2;
	int left = query(2 * si + 1, ss, mid, qs, qe, x);
	int right = query(2 * si + 2, mid + 1, se, qs, qe, x);
	return left + right;
}

public static int find(int si, int x) {
	List<Integer> a = segmentTree[si];
	int lo = 0;
	int hi = a.size() - 1;
	int ans = hi + 1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		int b = a.get(mid);
		if (b > x) {
			ans = mid;
			hi = mid - 1;
		} else if (b <= x) {
			lo = mid + 1;
		}
	}
	return a.size() - ans;
}

public static void build(int si, int ss, int se, Pair[] arr) {
	if (ss == se) {
		segmentTree[si] = new ArrayList<>();
		segmentTree[si].add(arr[ss].b);
		return;
	}

	int mid = (ss + se) / 2;
	build(2 * si + 1, ss, mid, arr);
	build(2 * si + 2, mid + 1, se, arr);
	segmentTree[si] = new ArrayList<>();
	merge(si);
}

public static void merge(int si) {
	int i = 0;
	int j = 0;

	List<Integer> a = segmentTree[2 * si + 1];
	List<Integer> b = segmentTree[2 * si + 2];
	List<Integer> c = segmentTree[si];

	while (i < a.size() && j < b.size()) {
		if (a.get(i) <= b.get(j)) {
			c.add(a.get(i));
			i++;
		} else {
			c.add(b.get(j));
			j++;
		}
	}

	while (i < a.size()) {
		c.add(a.get(i));
		i++;
	}

	while (j < b.size()) {
		c.add(b.get(j));
		j++;
	}
}

static List<Integer>[] segmentTree;

public static int firstPos(int x, Pair[] arr) {
	int lo = 0;
	int hi = arr.length - 1;
	int ans = hi + 1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		Pair m = arr[mid];
		if (m.a > x) {
			ans = mid;
			hi = mid - 1;
		} else if (m.a <= x) {
			lo = mid + 1;
		}
	}
	return ans;
}

public static class Pair implements Comparable<Pair> {
	int a;
	int b;

	Pair(int a, int b) {
		this.a = a;
		this.b = b;
	}

	@Override
	public int compareTo(Pair arg0) {
		return this.a - arg0.a;
	}
}
