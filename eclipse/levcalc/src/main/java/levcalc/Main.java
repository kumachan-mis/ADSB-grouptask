package levcalc;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

import org.apache.lucene.search.spell.LevensteinDistance;

public class Main
{

	public static void main(String[] args) throws IOException
	{
		File[] files =  new File(".").listFiles();
		for(int i = 0; i < files.length; i++)
		{
			System.out.println(i + ") " + files[i].getName());
		}

		int index1, index2;
		try(Scanner sc = new Scanner(System.in))
		{
			System.out.print("Select first file > ");
			index1 = sc.nextInt();
			System.out.print("Select second file > ");
			index2 = sc.nextInt();
		}

		String str1, str2;
		try( BufferedReader br = new BufferedReader(new FileReader(files[index1])))
		{
			str1 = br.readLine();
		}
		try( BufferedReader br = new BufferedReader(new FileReader(files[index2])))
		{
			str2 = br.readLine();
		}


		System.out.println(new LevensteinDistance().getDistance(str1, str2));
	}

}
