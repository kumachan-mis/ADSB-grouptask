import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.stream.Collectors;

public class Ngram
{
	private void rec(List<String> list, int n, String str)
	{
		if (str.length() >= n)
		{
			list.add(str);
			return;
		}
		rec(list, n, str + 'a');
		rec(list, n, str + 'b');
		rec(list, n, str + 'c');
	}

	private List<String> generateKeys(int n)
	{
		List<String> keys = new ArrayList<>();
		rec(keys, n, "");
		return keys;
	}

	public Map<String, List<Integer>> createNgram(int n, final String str)
	{
		Map<String, List<Integer>> map = generateKeys(n).stream().collect(Collectors.toMap(s -> s, s -> new ArrayList<>(), (s1, s2) -> s1, TreeMap::new));
		map.forEach((key, list) ->
		{
			for (int index = str.indexOf(key); index >= 0; index = str.indexOf(key, index + 1))
			{
				//if (index + 25 < str.length())
					list.add(index);
			}
		});
		return map;
	}

	public static int distance(String s1, String s2)
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
				edits[i][j] = Math.min(
						edits[i - 1][j] + 1,
						Math.min(
								edits[i][j - 1] + 1,
								edits[i - 1][j - 1] + u));
			}
		}
		return edits[s1.length()][s2.length()];
	}

}
