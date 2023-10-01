package demo1;

import java.io.File;

public class Main {
 
	static String infile=System.getProperty("user.dir")+File.separator+"product.txt";//File.separator='/'或者'\'
	static String outfile=System.getProperty("user.dir")+File.separator+"result.txt";
	
	
	public static void main(String args[])
	{
		File in=new File(infile);
		File out = new File(outfile); 
		new FrmProduct(in,out);
		System.out.print('A'-'a'+1);
	}
}
