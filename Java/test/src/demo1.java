import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;

public class demo1 {
	static String infile=System.getProperty("user.dir")+File.separator+"stack.txt";
	static File in;
	static ArrayList<String> data;
	static mystack s;
	static String[] spt;
	
	static public void main(String args[])
	{
		in=new File(infile);
		data=new ArrayList<String>();
		
		
		s=new mystack();
		//判空
		if(s.is_empty())System.out.println("correct!the stack is empty");
		else System.out.println("error!");
		
		System.out.println();
		//读入数据并测试入栈
		try {
			BufferedReader br=new BufferedReader(new FileReader(in));
			String line=br.readLine();
			spt=line.split(" ");
			for(String i:spt)
			{
				s.push(i);
				System.out.println("push "+i+" to the stack");
			}
			br.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//判满
		if(s.is_full())System.out.println("correct!the stack is full");
		else System.out.println("error!");
		//异常测试
		System.out.println("if i continue to push:");
		s.push("abc");
		System.out.println();
		
		//弹出栈测试
		while(!s.is_empty())
		{
			System.out.println("pop "+s.pop());
		}
		//异常测试
		System.out.println("if i continue to pop:");
		String temp=s.pop();
		System.out.println();
		//输出测试
		System.out.println("push all the string to the stack and then print:");
		for(String i:spt)
		{
			s.push(i);
			System.out.println("push "+i+" to the stack");
		}
		s.show();
		//判定打印没有删除数据
		if(s.is_full())System.out.println("correct!the stack is full");
		else System.out.println("error!");
		
		//判定打印后栈的顺序是否正确
		if(s.pop().equals("考试"))System.out.println("Correct!");
		else System.out.println("error!");
	}
	
}
