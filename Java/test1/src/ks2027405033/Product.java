package ks2027405033;
public class Product {
	public static String[] TYPES = { "全部", "电脑", "手机", "书籍" }; // 所有类型

	private String id;  //产品编号
	private String name; // 名称
	private String type; // 类型
	private double price; // 价格
	private int number; // 库存

	public Product(String line) {
		String[] args = line.split(";");
		id = args[0];
		name = args[1];
		type = args[2];
		price = Double.parseDouble(args[3]);
		number = Integer.parseInt(args[4]);
	}

	public String toString() {
		return id + ";" + name + ";" + type + ";" + price + ";" + number;
	}
	
	public String getType() {
		return type;
	}
	
	public String getId() {
		return id;
	}
	
	public int getNumber() {
		return number;
	}
	
}