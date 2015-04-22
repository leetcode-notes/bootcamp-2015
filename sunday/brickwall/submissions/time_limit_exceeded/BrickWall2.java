import java.util.*;
import java.io.*;

public class BrickWall2 {

    static int c1, c2, c3;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        int k = Integer.parseInt(in.readLine());
        for (int test = 0; test < k; test++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            int N = Integer.parseInt(st.nextToken());
            c1 = Integer.parseInt(st.nextToken());
            c2 = Integer.parseInt(st.nextToken());
            c3 = Integer.parseInt(st.nextToken());
            int[] b = new int[N];
            int len = 0;
            st = new StringTokenizer(in.readLine());
            for (int i = 0; i < N; i++) {
                b[i] = Integer.parseInt(st.nextToken());
                len += b[i];
            }
            boolean[] good = new boolean[len+1];
            Arrays.fill(good, true);
            int pos = 0;
            for (int i = 0; i < N-1; i++) {
                pos += b[i];
                good[pos] = false;
            }
            boolean[][][][] vis = new boolean[len+1][c1+1][c2+1][c3+1];
            out.println(dfs(0, 0, 0, 0, good, vis) ? "YES" : "NO");
        }

        in.close();
        out.close();
    }

    public static boolean dfs(int pos, int u1, int u2, int u3, boolean[] good, boolean[][][][] vis) {
        if (vis[pos][u1][u2][u3]) return false;
        vis[pos][u1][u2][u3] = true;
        if (pos == good.length - 1) return true;
        if (u1 < c1 && pos + 1 < good.length && good[pos + 1]) {
            if (dfs(pos+1, u1+1, u2, u3, good, vis)) return true;
        }
        if (u2 < c2 && pos + 2 < good.length && good[pos + 2]) {
            if (dfs(pos+2, u1, u2+1, u3, good, vis)) return true;
        }
        if (u3 < c3 && pos + 3 < good.length && good[pos + 3]) {
            if (dfs(pos+3, u1, u2, u3+1, good, vis)) return true;
        }
        return false;
    }
}
