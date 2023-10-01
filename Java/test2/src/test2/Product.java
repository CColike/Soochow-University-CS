package test2;

public class Product {
	String id;
	String name;
	 String type;
	double price;
	int number;
	
	 Product(String s)
	{
		String [] spt=s.split(";");
		id=spt[0];
		name=spt[1];
		type=spt[2];
		price=Double.parseDouble(spt[3]);
		number=Integer.parseInt(spt[4]);
	}
	 
	public String toString()
	{
		return id+';'+name+';'+type+';'+price+';'+number;
	}

	public String getType() {
		// TODO Auto-generated method stub
		return type;
	}
	public String getId()
	{
		return id;
	}
	public int getNum()
	{
		return number;
	}
}
