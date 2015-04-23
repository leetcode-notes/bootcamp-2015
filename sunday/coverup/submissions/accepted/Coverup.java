import java.util.*;
import java.io.*;

public class Coverup {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        int k = Integer.parseInt(in.readLine());
        for (int test = 0; test < k; test++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(st.nextToken());
            long[][] points = new long[n][2];
            int start = 0;
            for (int i = 0; i < n; i++) {
                points[i][0] = Integer.parseInt(st.nextToken());
                points[i][1] = Integer.parseInt(st.nextToken());
                if (points[i][0] < points[start][0] || points[i][0] == points[start][0] && points[i][1] < points[start][1]) {
                    start = i;
                }
            }

            Fraction prev = null;
            int[] sidelen = new int[n];
            int sides = 0;
            int curr = start;
            while (true) {
                int next = curr == 0 ? 1 : 0;
                for (int i = 0; i < n; i++) {
                    if (i == curr) continue;
                    long[] p1 = subtract(points[next], points[curr]);
                    long[] p2 = subtract(points[i], points[curr]);
                    long cr = cross(p1, p2);
                    if (cr > 0 || cr == 0 && norm2(p2) < norm2(p1)) {
                        next = i;
                    }
                }
                Fraction f = new Fraction(subtract(points[next], points[curr]));
                if (f.equals(prev)) {
                    sidelen[sides-1]++;
                } else {
                    sides++;
                }
                if (next == start) {
                    break;
                }
                prev = f;
                curr = next;
            }
            out.println(coverSides(Arrays.copyOfRange(sidelen, 0, sides)));
        }

        in.close();
        out.close();
    }
    
    public static int coverSides(int[] len) {
        int n = len.length;
        boolean[] used = new boolean[n];
        int res = 0;
        int left = n;
        // Use long sides
        for (int i = 0; i < n; i++) {
            left += len[i];
            if (len[i] > 1) {
                res++;
                left -= len[i];
                if (!used[i]) {
                    used[i] = true;
                    left--;
                }
                if (!used[(i+1)%n]) {
                    used[(i+1)%n] = true;
                    left--;
                }
            }
        }
        int pos = 0;
        for (int i = 0; i < n; i++) {
            if (used[i] || len[i] == 0) {
                pos = i;
                break;
            }
        }
        // Use 3-sides
        for (int i = 0; i < n; i++) {
            if (!used[pos] && !used[(pos+1)%n] && len[pos] == 1) {
                left -= 3;
                res++;
                used[pos] = true;
                used[(pos+1)%n] = true;
            }
            pos = (pos+1)%n;
        }
        res += (left+1)/2;
        return res;
    }

    public static long[] subtract(long[] p1, long[] p2) {
        return new long[] {p1[0] - p2[0], p1[1] - p2[1]};
    }

    public static long norm2(long[] p) {
        return p[0]*p[0] + p[1]*p[1];
    }

    public static long cross(long[] p1, long[] p2) {
        return p1[0]*p2[1] - p1[1]*p2[0];
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

        public Fraction(long[] p) {
            this(p[0], p[1]);
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
