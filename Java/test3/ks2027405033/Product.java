
public class Product {
	String s;
	String id;
	String name;
	String type;
	double price;
	int num;
	
	Product(String s1)
	{
		String[] ss=s1.split(";");
		s=s1;
		id=ss[0];
		name=ss[1];
		type=ss[2];
		price=Double.parseDouble(ss[3]);
		num=Integer.parseInt(ss[4]);
	}
	
	String getType()
	{
		return type;
	}
	
	String getS()
	{
		return s;
	}
	
	String getId()
	{
		return id;
	}
	
	int getNum()
	{
		return num;
	}
}
