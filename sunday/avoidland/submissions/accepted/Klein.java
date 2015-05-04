import java.io.*;
import java.util.*;

public class Klein
{
	public static void main(String[] klein)
	{
		final Kattio in = new Kattio(System.in);

		final int n = in.getInt();
		final int[] x = new int[n], y = new int[n];
		for(int i = 0; i<n; i++){ x[in.getInt()-1]++; y[in.getInt()-1]++; }

		long sum = 0, dif = 0;
		for(int i = 0; i<n; i++, sum+=Math.abs(dif)) dif += x[i]-1;
		dif = 0;
		for(int i = 0; i<n; i++, sum+=Math.abs(dif)) dif += y[i]-1;
		System.out.println(sum);
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
