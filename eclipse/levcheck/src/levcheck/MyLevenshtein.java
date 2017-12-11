package levcheck;

import java.util.Map;
import java.util.TreeMap;

public class MyLevenshtein
{
	public int getDistance(String s1, String s2)
	{
		int edits[][] = new int[s1.length() + 1][s2.length() + 1];
		for (int i = 0; i <= s1.length(); i++)
			edits[i][0] = i;
		for (int j = 1; j <= s2.length(); j++)
			edits[0][j] = j;
		for (int i = 1; i <= s1.length(); i++)
		{
			for (int j = 1; j <= s2.length(); j++)
			{
				int u = (s1.charAt(i - 1) == s2.charAt(j - 1) ? 0 : 1);
				edits[i][j] = Math.min(edits[i - 1][j] + 1, Math.min(edits[i][j - 1] + 1, edits[i - 1][j - 1] + u));
			}
		}
		return edits[s1.length()][s2.length()];
	}

	private boolean check(char[] a , char[] b, int x, int y, int n)
	{
		if(n == 0 || n - Math.abs(x - y) <= 0) return false;
		while(x > 0 && y > 0 && a[x - 1] == b[y - 1]) { x--; y--; }
		if(x == 0 || y == 0 || check(a, b, x - 1, y - 1, n - 1) || check(a, b, x, y - 1, n - 1) || check(a, b, x - 1, y, n - 1)) return true;
		else return false;
	}

	//編集距離がn未満ならtrue
	public boolean checkDistance(String s1, String s2, int n)
	{
		return check(s1.toCharArray(), s2.toCharArray(), s1.length(), s2.length(), n);
	}

	public boolean checkDistance(char[] a, char[] b, int n)
	{
		return check(a, b, a.length, b.length, n);
	}

	private Map<String, Integer> map = new TreeMap<>();
	public boolean hogeFunc(String s1, String s2)
	{
		char a[] = s1.toCharArray();
		char b[] = s2.toCharArray();
		int pos = 0, cnt = 0;
		for(int i = 0; i < s1.length(); i++)
		{
			if(a[i] != b[i])
			{
				pos = i;
				if(++cnt >= 2) return false;
			}
		}
		if(cnt == 0) return false;
		String key = a[pos] + "" + b[pos];
		map.put(key, map.containsKey(key) ? map.get(key) + 1 : 1);
		return true;
	}

	public void hogePrint()
	{
		map.forEach((key, value) ->
		{
			System.out.println(key + ": " + value);
		});
		map  = new TreeMap<>();
	}




}
