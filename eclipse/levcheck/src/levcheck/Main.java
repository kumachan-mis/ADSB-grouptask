package levcheck;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.stream.Collectors;

public class Main
{
	public static void main(String[] args) throws IOException
	{
		String path = "/Users/atsushi/Documents/ADSB-grouptask/gw_files2017/dat/";

		for(int  i = 0; i < 5; i++)
		{
			List<String> list = Files.lines(Paths.get(path + "dat" + i + "_in")).collect(Collectors.toList());
			String Tdash = list.get(0);
			list.remove(0);
			List<String> S = list;
			String T = Files.lines(Paths.get(path + "dat" + i + "_org")).findFirst().get();

			MyLevenshtein mylev = new MyLevenshtein();
			int cnt = 0;
			int t = 0;
			for(String s : S)
			{
				for(int j = 0; j < T.length() - 25; j++)
				{
					if(mylev.checkDistance(T.substring(j, j + 25), s, 3))
					{
						cnt++;
						break;
					}
				}
				//if(++t % 100 == 0) System.out.println(t);
			}
			System.out.print("dat" + i + ": ");
			System.out.println(cnt);
		}

	}

}
