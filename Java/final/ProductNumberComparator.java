




import java.util.Comparator;

//按照库存排序的比较器
public class ProductNumberComparator implements Comparator<Product> {
	@Override
	public int compare(Product arg0, Product arg1) {
		return arg0.getNumber() - arg1.getNumber();
	}
}
