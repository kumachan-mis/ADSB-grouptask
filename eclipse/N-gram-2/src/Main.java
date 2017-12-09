
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Main
{

	public static void main(String[] args) throws IOException
	{
		String T, tmp;
		List<String> S = new ArrayList<>();

		for(int i = 0; i < 5; i++)
		{
			String name = "dat" + i + "_org";
			try (BufferedReader br = new BufferedReader(new FileReader(new File("C:\\Users\\Shira\\Documents\\ADSB-grouptask\\gw_files2017\\dat\\" + name))))
			{
				T = br.readLine();
				while ((tmp = br.readLine()) != null)
				{
					S.add(tmp);
				}
			}
			System.out.println(name);
			Ngram ngram = new Ngram();
			int n = 5;
			Map<String, List<Integer>> map = ngram.createNgram(n, T);

			map.forEach((key, value) ->
			{
				System.out.println(key + ": " + value.size());
//				for(int index : value)
//				{
//
//				}
			});
		}
	}
}