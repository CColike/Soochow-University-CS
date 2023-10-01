//Main.java
package demo2;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

public class Main {
 
	static private String infile=System.getProperty("user.dir")+File.separator+"in.txt";
	static private String outfile=System.getProperty("user.dir")+File.separator+"out.txt";
	static Medal m;
	public static void main(String args[])
	{
		m=new Medal(infile,outfile);
		try {
			BufferedWriter br = new BufferedWriter(new FileWriter(outfile));
			m.write(br);
			br.write("\n");
			br.write("search C;10;8;7 :"+m.search("C;10;8;7")+'\n');
			br.write("search C;10;8;6 :"+m.search("C;10;8;6")+'\n');
			br.write("\n");
			br.write("insert F;12;7;2 At 0:\n");
			m.insert("F;12;7;2",0);
			m.write(br);
			br.write("delete F;12;7;2 :\n");
			m.delelte((int)0);
			m.write(br);
			br.write("\nreverse :\n");
			m.reverse();
			m.write(br);

			br.write("\nsort :\n");
			br.write("国家名由小到大\n");
			m.sortData();
			m.write(br);
			br.close();
		}catch (Exception e1) {
		}	
	}
}