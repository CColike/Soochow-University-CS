import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;

import javax.swing.Box;
import javax.swing.ButtonGroup;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class demo2  extends JFrame{

	private JRadioButton id,name,money;
	private ButtonGroup bg;
	private JScrollPane jsp;
	private JTextArea jta;
	
	private String res;
	private ArrayList<person> show; 
	private static String infile=System.getProperty("user.dir")+File.separator+"staff.txt";
	static private File in;
	
	demo2()
	{
		//选择三个组件
		id=new JRadioButton("员工编号");
		name=new JRadioButton("姓名");
		money=new JRadioButton("工资");
		bg=new ButtonGroup();
		bg.add(id);
		bg.add(name);
		bg.add(money);
		id.setSelected(true);
		Container content=getContentPane();
		
		Box b1=Box.createHorizontalBox();
		b1.add(Box.createHorizontalGlue());
		b1.add(id);
		b1.add(Box.createHorizontalStrut(10));
		b1.add(name);
		b1.add(Box.createHorizontalStrut(10));
		b1.add(money);
		b1.add(Box.createHorizontalGlue());
		content.add(b1,BorderLayout.NORTH);
		
		
		//文本框
		res="";
		jta=new JTextArea(res);
		jsp=new JScrollPane(jta);
		content.add(jsp);
		
		
		
		show=new ArrayList<person>();
		//加载数据
		load();
		
		//初始化监听器
		initl();
		//初始化文本框
			//排序
		sortshow();
			//展示到文本框
		showshow();

		setTitle("查看员工");
		setSize(500,400);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
	}
	//初始化监听器
	void initl()
	{
		ItemListener i=new listener();
		id.addItemListener(i);
		name.addItemListener(i);
		money.addItemListener(i);
	}
	
	
	class listener implements ItemListener
	{

		@Override
		public void itemStateChanged(ItemEvent e) {
			// TODO Auto-generated method stub
			sortshow();
			showshow();
		}
		
	}
	
	void sortshow()
	{
		//根据选择不同进行排序
		if(id.isSelected())
		{
			show.sort((a1,a2)->
			{
				return a1.getid()-a2.getid();
			});
		}
		else if(name.isSelected())
		{
			show.sort((a1,a2)->
			{
				return a1.getname().compareTo(a2.getname());
			});
		}
		else
		{
			show.sort((a1,a2)->
			{
				if(a1.getmoney()-a2.getmoney()>0)return 1;
				else if(a1.getmoney()-a2.getmoney()==0)return 0;
				else return -1;
			});
		}
	}
	//展示到文本框
	void showshow()
	{
		res="";
		for(person i:show)
		{
			res=res+i.gets()+"\n";
		}
		jta.setText(res);
	}
	//加载数据
	void load()
	{
		try {
			BufferedReader br=new BufferedReader(new FileReader(in));
			String line=br.readLine();
			while(line!=null)
			{
				show.add(new person(line));
				line=br.readLine();
//				System.out.println(line);
			}
			br.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
	static public void main(String args[])
	{
		in=new File(infile);
		new demo2();
		
	}
}
