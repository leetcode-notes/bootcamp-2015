import java.util.*;
import java.io.*;

public class Coverup2 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

            StringTokenizer st = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(st.nextToken());
            long[][] points = new long[n][2];
            for (int i = 0; i < n; i++) {
                points[i][0] = Integer.parseInt(st.nextToken());
                points[i][1] = Integer.parseInt(st.nextToken());
            }
            Arrays.sort(points, new Comparator<long[]>() {
                public int compare(long[] a, long[] b) {
                    if (a[0] < b[0]) return -1;
                    if (a[0] > b[0]) return 1;
                    if (a[1] < b[1]) return -1;
                    if (a[1] > b[1]) return 1;
                    return 0;
                }
            });
            int res = 0;
            int left = n;
            boolean[] used = new boolean[n];
            for (int i = 0; i < n; i++) {
                if (used[i]) continue;
                HashMap<Fraction, Integer> lines = new HashMap<Fraction, Integer>();
                for (int j = i+1; j < n; j++) {
                    if (used[j]) continue;
                    long dx = points[j][0] - points[i][0];
                    long dy = points[j][1] - points[i][1];
                    Fraction f = new Fraction(dx, dy);
                    if (!lines.containsKey(f)) {
                        lines.put(f, j);
                    } else {
                        int v = lines.get(f);
                        if (v >= 0) {
                            res++;
                            left -= 3;
                            used[v] = true;
                            used[j] = true;
                            lines.put(f, -1);
                        } else {
                            left--;
                            used[j] = true;
                        }
                    }
                }
            }
            res += (left + 1)/2;
            out.println(res);

        in.close();
        out.close();
    }

    public static long gcd(long a, long b) {
        return b == 0 ? a : gcd(b, a%b);
    }

    static class Fraction {
        public long n, d;
        public Fraction(long n, long d) {
            long g = gcd(n, d);
            n /= g;
            d /= g;
            if (d < 0) {
                n *= -1;
                d *= -1;
            }
            this.n = n;
            this.d = d;
        }

        public int hashCode() {
            return (int)(17*n+31*d);
        }

        public boolean equals(Object o) {
            if (!(o instanceof Fraction)) return false;
            Fraction f = (Fraction) o;
            return f.n == n && f.d == d;
        }
    }
}
