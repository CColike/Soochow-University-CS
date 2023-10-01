//Ratator.java
package demo1;

public class Ratator {
	private int [] a;
	Ratator(int [] l)
	{
		a=l;
	}
	public int get(int i)
	{
		return a[i];
	}
	public int back(int target)
	{
		int idx=0;
		while(a[idx]!=target)
			idx++;
		return idx;
	}
	public void ratate()
	{
		int temp=a[0];
		for(int i=0;i<25;i++)
			a[i]=a[i+1];
		a[25]=temp;
	}
}
