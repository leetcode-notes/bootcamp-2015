import java.io.*;
import java.util.*;

public class Klein
{
	static int m, n;
	static int[][] map;
	static final int[] die = new int[6];
	static HashSet<Integer>[][] set;
	static boolean add(final int y, final int x)
	{
		int hash = 0;
		for(int i = 0; i<6; i++) hash = (hash<<5) + die[i]+1;
		return set[y][x].add(hash);
	}
	static void roll(final int dir)
	{
		final int tmp = die[0];
		if(dir==0)
		{
			die[0] = die[1]; die[1] = die[3]; die[3] = die[5]; die[5] = tmp;
		}
		else if(dir==1)
		{
			die[0] = die[2]; die[2] = die[3]; die[3] = die[4]; die[4] = tmp;
		}
		else if(dir==2)
		{
			die[0] = die[5]; die[5] = die[3]; die[3] = die[1]; die[1] = tmp;
		}
		else if(dir==3)
		{
			die[0] = die[4]; die[4] = die[3]; die[3] = die[2]; die[2] = tmp;
		}
	}
	static boolean rek(final int y, final int x)
	{
		if(y<0 || y>=m || x<0 || x>=n) return false;
		if(die[0]<0)
		{
			die[0] = map[y][x];
			if(rek(y,x)) return true;
			die[0] = -1;
			return false;
		}//System.err.println(y+" "+x+": "+Arrays.toString(die));new Scanner(System.in).next();
		if(die[0]!=map[y][x] || !add(y,x)) return false;
		if(y+1==m && x+1==n) return true;

		for(int i = 0, dy= - 1, dx = 0, tmp; i<4; i++, tmp = dy, dy = dx, dx = -tmp)
		{
			roll(i);//System.err.println("Roll "+i+" "+dy+" "+dx);
			if(rek(y+dy,x+dx)) return true;
			roll(i+2&3);//System.err.println("Unroll "+(i+2&3)+" "+dy+" "+dx);
		}
		return false;
	}
	public static void main(String[] klein)
	{
		final Scanner in = new Scanner(new BufferedInputStream(System.in));

		m = in.nextInt(); n = in.nextInt();
		map = new int[m][n];
		for(int i = 0; i<m; i++)
			for(int j = 0; j<n; j++)
				map[i][j] = in.nextInt();
		Arrays.fill(die,-1);
		set = new HashSet[m][n];
		for(int i = 0; i<m; i++)
			for(int j = 0; j<n; j++)
				set[i][j] = new HashSet<Integer>();

		System.out.println(rek(0,0) ? "YES" : "NO");
	}
}

/*
0 -> 1, 2, 5, 4
1 -> 3, 2, 0, 4
2 -> 5, 0, 1, 3
3 -> 5, 2, 1, 4
4 -> 5, 3, 1, 0
5 -> 0, 2, 3, 4
*0*
*1*
234
*5*

*/
