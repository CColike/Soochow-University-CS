//MyComparator.java
//排序方式：奖牌数从多到少；国家名字按照字典序从前到后/从小到大
package demo2;

import java.util.Comparator;

public class MyComparator implements Comparator<Item> {
	public int compare(Item a, Item b) {
		if(a.getGold()==b.getGold())
		{
			if(a.getSilver()==b.getSilver())
			{
				if(a.getCopper()==b.getCopper())
				{
					return a.getCountry().compareTo(b.getCountry());
				}
				else return b.getCopper()-a.getCopper();
			}
			else return b.getSilver()-a.getSilver();
		}
		else return b.getGold()-a.getGold();
	}
}