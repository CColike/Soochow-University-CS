//Book.java
package demo2;

public class Book {
	private String num,name,author,press,inTime,outTime,deadline,returnTime,is_borrow,is_store;

	public Book(String line) {
		String[] args = line.split(";");
		num=args[0];
		name=args[1];
		author=args[2];
		press=args[3];
		inTime=args[4];
		outTime=args[5];
		deadline=args[6];
		returnTime=args[7];
		is_borrow=args[8];
		is_store=args[9];
	}
	
	public String toString()
	{
		return num+";"+name+";"+author+";"+press+";"+inTime+";"+outTime+";"+deadline+";"+returnTime+";"+is_borrow+";"+is_store;
	}
	
	public String getNum()
	{
		return num;
	}
	public String getName()
	{
		return name;
	}
	public String getAuthor()
	{
		return author;
	}
	public String getPress()
	{
		return press;
	}
	public String getInTime()
	{
		return inTime;
	}
	public String getOutTime()
	{
		return outTime;
	}
	public String getDeadline()
	{
		return deadline;
	}
	public String getReturnTime()
	{
		return returnTime;
	}
	public String getIsBorrow()
	{
		return is_borrow;
	}
	public String getIsStore()
	{
		return is_store;
	}
	
}
