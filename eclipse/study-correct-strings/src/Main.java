import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Main
{

	public static void main(String[] args) throws IOException
	{
		File[] files = new File("C:\\Users\\Shira\\Documents\\ADSB-grouptask\\gw_files2017\\dat").listFiles();
		for (int i = 0; i < files.length; i++)
		{
			System.out.println(i + ") " + files[i].getName());
		}

		int index;
		try (Scanner sc = new Scanner(System.in))
		{
			System.out.print("Select file > ");
			index = sc.nextInt();
		}

		String str;
		try (BufferedReader br = new BufferedReader(new FileReader(files[index])))
		{
			str = br.readLine();
		}

		long cntA = 0, cntB = 0, cntC = 0;
		for (char c : str.toCharArray())
		{
			if (c == 'a') cntA++;
			else if (c == 'b') cntB++;
			else if (c == 'c') cntC++;
		}

		System.out.println(String.format("A: %d(%f%%)%nB: %d(%f%%)%nC: %d(%f%%)",
				cntA, cntA * 100f / str.length(), cntB, cntB * 100f / str.length(), cntC, cntC * 100f / str.length()));

		long[][] cnts = new long[][]{{0,0,0},{0,0,0},{0,0,0}};
		char[] chars = str.toCharArray();
		char prec = chars[0];
		for (int i = 1; i < chars.length; i++)
		{
			char c = chars[i];
			int p1 = -1, p2 = -1;
			if (prec == 'a') p1 = 0;
			else if (prec == 'b') p1 = 1;
			else if (prec == 'c') p1 = 2;
			if (c == 'a') p2 = 0;
			else if (c == 'b') p2 = 1;
			else if (c == 'c') p2 = 2;
			cnts[p1][p2]++;
			prec = c;
		}

		System.out.println(String.format("AA: %d(%f%%) AB: %d(%f%%) AC: %d(%f%%)",
				cnts[0][0], cnts[0][0] * 100f / cntA, cnts[0][1], cnts[0][1] * 100f / cntA, cnts[0][2], cnts[0][2] * 100f / cntA));

		System.out.println(String.format("BA: %d(%f%%) BB: %d(%f%%) BC: %d(%f%%)",
				cnts[1][0], cnts[1][0] * 100f / cntB, cnts[1][1], cnts[1][1] * 100f / cntB, cnts[1][2], cnts[1][2] * 100f / cntB));

		System.out.println(String.format("CA: %d(%f%%) CB: %d(%f%%) CC: %d(%f%%)",
				cnts[2][0], cnts[2][0] * 100f / cntC, cnts[2][1], cnts[2][1] * 100f / cntC, cnts[2][2], cnts[2][2] * 100f / cntC));

	}

}
