//Item.java
package demo2;

public class Item {
	
	private String country;
	private int gold,silver,copper;
	
	Item(String s)
	{
		String[] args = s.split(";");
		country=args[0];
		gold=Integer.parseInt(args[1]);
		silver=Integer.parseInt(args[2]);
		copper=Integer.parseInt(args[3]);
	}
	
	public String getCountry()
	{
		return country;
	}
	public int getGold()
	{
		return gold;
	}
	public int getSilver()
	{
		return silver;
	}
	public int getCopper()
	{
		return copper;
	}
	public String toString()
	{
		return country+";"+gold+";"+silver+";"+copper;
	}
}
