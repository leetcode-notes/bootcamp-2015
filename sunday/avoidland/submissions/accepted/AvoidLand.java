import java.util.*;
import java.io.*;

public class AvoidLand {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        int n = Integer.parseInt(in.readLine());
        int[] a = new int[n];
        int[] b = new int[n];
        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            a[Integer.parseInt(st.nextToken())-1]++;
            b[Integer.parseInt(st.nextToken())-1]++;
        }
        out.println(calcDistances(a) + calcDistances(b));

        in.close();
        out.close();
    }

    public static long calcDistances(int[] a) {
        long res = 0;
        int sum = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
            res += Math.abs(i+1-sum);
        }
        return res;
    }
}
