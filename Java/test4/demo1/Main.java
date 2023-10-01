//Main.java
package demo1;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;


public class Main {
 
	static private String infile=System.getProperty("user.dir")+File.separator+"in.txt";
	static private String outfile=System.getProperty("user.dir")+File.separator+"out.txt";
	
	static private int num1;
	static private int num2;
	static private int num3;
	static private String data;
	
	static void loadData()
	{
		try 
		{
			BufferedReader br=new BufferedReader(new FileReader(new File(infile)));
			String s=br.readLine();
			while(s!=null)
			{
				num1=Integer.parseInt(s);s=br.readLine();
				num2=Integer.parseInt(s);s=br.readLine();
				num3=Integer.parseInt(s);s=br.readLine();
				data=s;
			}
			br.close();
		}
		catch (Exception e) {
		}
	}
	
	static void writeData(String s)
	{
		try {
			BufferedWriter br = new BufferedWriter(new FileWriter(outfile));
			br.write(s);
			br.close();
		}catch (Exception e1) {
		}
	}
	
	public static void main(String args[])
	{
		loadData();
		Encode e=new Encode(num1,num2,num3,data);
		writeData(e.get_res());
	}
}
