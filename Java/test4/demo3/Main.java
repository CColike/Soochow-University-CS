package demo3;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class Main {
	
	static double Calculate(String ss)
	{
		Stack<String> ops = new Stack<>();
		Stack<Double> number = new Stack<>();
		ArrayList<String> spt = new ArrayList<>();
		String[] s = ss.split(" ");
		for(String i:s)
		{
			if(i.contains("I"))
			{
				spt.add(index(i));
			}
			else if(i.contains("log"))
			{
				spt.add(logg(i));
			}
			else if(i.contains("sin"))
			{
				spt.add(sin(i));
			}
			else if(i.contains("cos"))
			{
				spt.add(cos(i));
			}
			else if(i.contains("tan"))
			{
				spt.add(tan(i));
			}
			else if (i.contains("A"))
			{
				spt.add(A(i));
			}
			else if(i.contains("C"))
			{
				spt.add(C(i));
			}
			else if (i.equals("(")) 
			{
				ops.push(i);
			} 
			else if (i.equals(")")) 
			{
				while (!ops.peek().equals("(")) {
					spt.add(ops.pop());
				}
				ops.pop();
			} 
			else if (i.matches("\\d+(\\.\\d+)?"))
				spt.add(i);
			else
			{
				while (!ops.isEmpty()&&level(ops.peek())>=level(i))
					spt.add(ops.pop());
				ops.push(i);
			}
		}

		while (!ops.isEmpty())spt.add(ops.pop());
	
		for (String i:spt) 
		{
			if (i.equals("+"))      number.push(number.pop() + number.pop());
			else if (i.equals("-")) number.push(-(number.pop() - number.pop()));
		    else if (i.equals("*")) number.push(number.pop() * number.pop());
			else if (i.equals("/")) 
			{
				double num1 = number.pop();
				double num2 = number.pop();
				number.push(num2 / num1);
			} 
			else
			{
				number.push(Double.parseDouble(i));
//				System.out.println(i);
			}
		}
		return number.pop();
	}
	
	private static String C(String ss) {
		String []s=ss.split(";");
		int ans=1,xia=Integer.parseInt(s[1]),shang=Integer.parseInt(s[2]);
		for(int i=xia;i>=xia-shang+1;i--)
			ans*=i;
		for(int i=1;i<=shang;i++)
			ans/=i;
		return ans+"";
	}

	private static String A(String ss) {
		String []s=ss.split(";");
		int ans=1,xia=Integer.parseInt(s[1]),shang=Integer.parseInt(s[2]);
		for(int i=xia;i>=xia-shang+1;i--)
			ans*=i;
		return ans+"";
	}

	private static String tan(String ss) {
		String []s=ss.split(";");
		return Math.tan(Double.parseDouble(s[1]))+"";
	}

	private static String cos(String ss) {
		String []s=ss.split(";");
		return Math.cos(Double.parseDouble(s[1]))+"";
	}

	private static String sin(String ss) {
		String []s=ss.split(";");
		return Math.sin(Double.parseDouble(s[1]))+"";
	}

	private static String logg(String ss) {
		String []s=ss.split(";");
		return Math.log(Integer.parseInt(s[2]))/Math.log(Integer.parseInt(s[1]))+"";
	}

	static String index(String ss)
	{
		String []s=ss.split(";");
		return Math.pow(Integer.parseInt(s[1]), Integer.parseInt(s[2]))+"";
	}
	
	public static int level(String op) 
	{
		if (op.equals("*") || op.equals("/"))
			return 1;
		else if (op.equals("+")||op.equals("-"))
			return 0;
		else
			return -1;
	}
	
	
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		String s =scanner.nextLine();
		System.out.println(Calculate(s));
	}
}
