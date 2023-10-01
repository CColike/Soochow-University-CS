import java.util.ArrayList;

public class mystack {
	private String[] a;
	private int len=0;
	private int Maxn=5;
	
	
	mystack()
	{
		a=new String[Maxn];
	}
	
	void push(String s) 
	{
		if(len==Maxn)
		{
			System.out.println("error!out of range!");
			return;
		}
		a[len]=s;
		len++;
	}
	
	String pop()
	{
		if(len==0)
		{
			System.out.println("error!there is no String in stack!");
			return null;
		}
		len--;
		return a[len];
	}
	
	Boolean is_empty()
	{
		if(len==0)return true;
		else return false;
	}
	
	Boolean is_full()
	{
		if(len==Maxn)return true;
		else return false;
	}
	
	void show()
	{
		ArrayList<String> temp=new ArrayList<String>();
		while(!(is_empty()))
		{
			String t=pop();
			System.out.println(t);
			temp.add(t);
		}
		for(int i=temp.size()-1;i>=0;i--)
		{
			push(temp.get(i));
		}
	}
}
