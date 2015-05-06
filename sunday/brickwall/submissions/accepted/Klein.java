import java.io.*;
import java.util.*;

public class Klein
{
	static byte[][][][] dp;
	static int[] b;
	static final boolean[] dame = new boolean[301];
	static boolean rek(final int len, int c1, int c2, int c3)
	{
		if(c1<0 || c2<0 || c3<0 || dame[len]) return false;
		if(len==0) return true;
		if(c1>len) c1 = len;
		if(c2>len/2) c2 = len/2;
		if(c3>len/3) c3 = len/3;
		final byte[] state = dp[len][c3][c2];
		if(state[c1]!=0) return state[c1]<0 ? false : true;
		return (state[c1] = rek(len-3,c1,c2,c3-1) || rek(len-2,c1,c2-1,c3) || rek(len-1,c1-1,c2,c3) ? (byte)1 : (byte)-1) > 0;
	}

	public static void main(String[] klein)
	{
		final Kattio in = new Kattio(System.in);

		final int n = in.getInt(), c1 = in.getInt(), c2 = in.getInt(), c3 = in.getInt();
		b = new int[n];
		int sum = 0;
		for(int i = 0; i<n; i++) sum += b[i] = in.getInt();
		for(int i = 0, pre = 0; i<n; i++, dame[sum-pre]=true) pre+=b[i];
		dame[0] = false;

		dp = new byte[sum+1][][][];
		for(int i = 0; i<=sum; i++)
		{
			final int d1 = Math.min(c1+1, i+1);
			final int d2 = Math.min(c2+1, i/2+1);
			final int d3 = Math.min(c3+1, i/3+1);
			dp[i] = new byte[d3][d2][d1];
		}

		System.out.println(rek(sum,c1,c2,c3) ? "YES" : "NO");
	}

	private static class Kattio
	{
	    public Kattio(final InputStream i)
	    {
			r = new BufferedReader(new InputStreamReader(i));
	    }

	    public boolean hasMoreTokens() {
	    	return peekToken() != null;
	    }

	    public int getInt() {
	    	return Integer.parseInt(nextToken());
	    }

	    public double getDouble() {
	    	return Double.parseDouble(nextToken());
	    }

	    public float getFloat()
	    {
			return Float.parseFloat(nextToken());
		}

	    public long getLong() {
	    	return Long.parseLong(nextToken());
	    }

	    public String getWord() {
	    	return nextToken();
	    }



	    private BufferedReader r;
	    private String line;
	    private StringTokenizer st;
	    private String token;

	    private String peekToken() {
		if (token == null)
		    try {
			while (st == null || !st.hasMoreTokens()) {
			    line = r.readLine();
			    if (line == null) return null;
			    st = new StringTokenizer(line);
			}
			token = st.nextToken();
		    } catch (IOException e) { }
		return token;
	    }

	    private String nextToken() {
		String ans = peekToken();
		token = null;
		return ans;
	    }
	}
}
