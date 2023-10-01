//Medal.java
package demo2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

public class Medal {
	private ArrayList<Item> a;
	private String infile,outfile;
	
	Medal(String in,String out)
	{
		a=new ArrayList<Item>();
		infile=in;outfile=out;
		try 
		{
			BufferedReader br=new BufferedReader(new FileReader(new File(infile)));
			String s=br.readLine();
			while(s!=null)
			{
				a.add(new Item(s));
				s=br.readLine();
			}
			br.close();
		}
		catch (Exception e) {
		}
	}
	
	public int search(String s)
	{
		for(int i=0;i<a.size();i++)
		{
			if(a.get(i).toString().equals(s))return i;
		}
		return -1;
	}
	
	public void insert(String s,int idx)
	{
		a.add(idx,new Item(s));
	}
	
	public void delelte(int idx)
	{
		a.remove(idx);
	}
	
	public void reverse()
	{
		Collections.reverse(a);
	}
	//排序方式：奖牌数从多到少；国家名字按照字典序从前到后/从小到大
	public void sortData()
	{
		Collections.sort(a, new MyComparator());
	}
	
	public void write(BufferedWriter br) throws IOException
	{
		for(Item i:a)
		{
			br.write(i.toString()+"\n");
		}
	}
}
