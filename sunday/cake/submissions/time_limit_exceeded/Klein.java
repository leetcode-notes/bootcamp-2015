import java.io.*;
import java.util.*;

public class Klein
{
	static final PrintWriter out = new PrintWriter(System.out);
	static short[][] cum;

	static int sum(int a, int b, int c, int d)
	{
		return cum[c][d] - (b==0 ? 0 : cum[c][b-1]) - (a==0 ? 0 : cum[a-1][d]) + (a==0||b==0 ? 0 : cum[a-1][b-1]);
	}
	static void rek(int a, int b, int c, int d, final int n)
	{
		//if(n<=0) return;
		if(n==1){ out.println(++a + " " + ++b + " " + ++c + " " + ++d); return; }

		int tmp;
		for(int y = a; y<c; y++)
		{
			tmp = sum(a,b,y,d);
			if(tmp>0 && tmp<n)
			{
				rek(a,b,y,d,tmp);
				rek(y+1,b,c,d,n-tmp);
				return;
			}
		}
		for(int x = b; x<d; x++)
		{
			tmp = sum(a,b,c,x);
			if(tmp>0 && tmp<n)
			{
				rek(a,b,c,x,tmp);
				rek(a,x+1,c,d,n-tmp);
				return;
			}
		}
	}

	public static void main(String[] klein)
	{
		final Kattio in = new Kattio(System.in);

		final int p = in.getInt(), q = in.getInt(), n = in.getInt();
		cum = new short[p][q];
		for(int i = 0; i<n; i++) cum[in.getInt()-1][in.getInt()-1]++;

		for(int i = 1; i<q; i++) cum[0][i] += cum[0][i-1];
		for(int i = 1; i<p; i++) cum[i][0] += cum[i-1][0];
		for(int i = 1; i<p; i++)
			for(int j = 1; j<q; j++)
				cum[i][j] += cum[i-1][j] + cum[i][j-1] - cum[i-1][j-1];

		rek(0,0,p-1,q-1,n);
		out.println("0");
		out.close();
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
