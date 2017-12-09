import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main
{

	public static void main(String[] args) throws IOException
	{
		String T, tmp;
		List<String> S = new ArrayList<>();

		for(int i = 0; i < 5; i++)
		{
			String name = "dat" + i + "_in";
			try (BufferedReader br = new BufferedReader(new FileReader(new File("C:\\Users\\Shira\\Documents\\ADSB-grouptask\\gw_files2017\\dat\\" + name))))
			{
				T = br.readLine();
				while ((tmp = br.readLine()) != null)
				{
					S.add(tmp);
				}
			}

			int cnt = 0;
			for(String v : S)
			{
				if(T.indexOf(v) >= 0)
				{
					cnt++;
				}
			}
			System.out.println(name + ":" + cnt);
		}

	}

}
