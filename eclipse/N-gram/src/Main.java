
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.apache.lucene.search.spell.LevensteinDistance;

public class Main
{

	public static void main(String[] args) throws IOException
	{

		for(int i = 0; i < 5; i++)
		{
			String T, tmp;
			List<String> S = new ArrayList<>();
			String name = "dat" + i + "_in";
			try (BufferedReader br = new BufferedReader(new FileReader(new File("C:\\Users\\Shira\\Documents\\ADSB-grouptask\\gw_files2017\\dat\\" + name))))
			{
				T = br.readLine();
				while ((tmp = br.readLine()) != null)
				{
					S.add(tmp);
				}
			}
			//System.out.println(name);
			Ngram ngram = new Ngram();
			int n = 11;
			Map<String, List<Integer>> map = ngram.createNgram(n, T);


			char[] arr = T.toCharArray();
			for (String v : S)
			{
				String key = v.substring(0, n);
				List<Integer> indices = map.get(key);
				if (indices.size() == 0) continue;

				int mIndex = -1;
				int minD = Integer.MAX_VALUE;
				for (int index : map.get(key))
				{
					int d = ngram.distance(v, T.substring(index, index + 25));
					if (d < minD)
					{
						mIndex = index;
						minD = d;
					}
				}
				for(int x = 0; x < 25; x++)
				{
					if(minD <= 3)
						arr[mIndex + x] = v.charAt(x);
				}
			}
			String newT = new String(arr);


			String origT;
			String name2 = "dat" + i + "_org";
			try (BufferedReader br = new BufferedReader(new FileReader(new File("C:\\Users\\Shira\\Documents\\ADSB-grouptask\\gw_files2017\\dat\\" + name2))))
			{
				origT = br.readLine();
			}

			System.out.println(name + " " + name2);
			System.out.println(new LevensteinDistance().getDistance(T, origT));
			System.out.println(new LevensteinDistance().getDistance(T, newT));
			System.out.println(new LevensteinDistance().getDistance(origT, newT));
		}
	}
}