package ks2027405033;

import java.util.Comparator;

//按照id排序的比较器
public class ProductIdComparator implements Comparator<Product> {
	@Override
	public int compare(Product arg0, Product arg1) {
		return arg0.getId().compareTo(arg1.getId());
	}
}