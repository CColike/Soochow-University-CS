
public class person {
	private int id;
	private String name,str;//str是完整员工数据
	private Double money;
	person(String s)
	{
		str=s;
		String[] spt=s.split(";");
		id=Integer.parseInt(spt[0]);
		name=spt[1];
		money=Double.parseDouble(spt[2]);
	}
	
	public String gets()
	{
		return str;
	}
	
	public int getid()
	{
		return id;
	}
	
	public String getname()
	{
		return name;
	}
	
	public Double getmoney()
	{
		return money;
	}
}
