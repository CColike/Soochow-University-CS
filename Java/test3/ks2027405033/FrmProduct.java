import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

import javax.swing.Box;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JRadioButton;
import javax.swing.JTextArea;

public class FrmProduct extends JFrame
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	static String infile=System.getProperty("user.dir")+File.separator+"product.txt";
	static String outfile=System.getProperty("user.dir")+File.separator+"result.txt";
	static File in;
	static File out;
	JLabel jl1,jl2;
	JRadioButton id,num;
	ButtonGroup bg;
	JComboBox<String> typebox;
	String []n= {"全部","电脑","手机","书籍"};
	JTextArea jta;
	ArrayList<Product> data,show;
	String res="";
	JButton bt;

	FrmProduct()
	{
		
		Container content=getContentPane();
		//1
		Box b1=Box.createHorizontalBox();
		jl1=new JLabel("排序方式：");
		jl2=new JLabel("选择类型：");
		id=new JRadioButton("产品编号");
		num=new JRadioButton("产品库存");
		bg=new ButtonGroup();
		bg.add(id);bg.add(num);
		typebox=new JComboBox<String>(n);
		id.setSelected(true);
		typebox.setSelectedIndex(0);
		b1.add(Box.createHorizontalStrut(10));
		b1.add(jl1);
		b1.add(Box.createHorizontalStrut(10));
		b1.add(id);
		b1.add(Box.createHorizontalStrut(10));
		b1.add(num);
		b1.add(Box.createHorizontalGlue());
		b1.add(jl2);
		b1.add(Box.createHorizontalStrut(10));
		b1.add(typebox);
		b1.add(Box.createHorizontalStrut(10));
		content.add(b1,BorderLayout.NORTH);
		
		//2
		jta=new JTextArea(res);
		content.add(jta,BorderLayout.CENTER);
		
		//3
		bt=new JButton("保存");
		
		Box b2=Box.createHorizontalBox();
		b2.add(Box.createHorizontalGlue());
		b2.add(bt);
		b2.add(Box.createHorizontalGlue());
		content.add(b2,BorderLayout.SOUTH);
		
		//data
		data=new ArrayList<Product>();
		show=new ArrayList<Product>();
		load();
		initListener();
		
		getshow();
		sortshow();
		showshow();

		setTitle("查看产品");
		setSize(500,400);
		setVisible(true);//放最后
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	
	void load()
	{
		try {
			BufferedReader br = new BufferedReader(new FileReader(in));
			String line=br.readLine();
			while(line!=null)
			{
				data.add(new Product(line));
				show.add(new Product(line));
				System.out.println(line);
				line=br.readLine();
			}
			br.close();//非常重要
		
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	
	
	void initListener()//
	{
		ItemListener i1=new sortListener();
		id.addItemListener(i1);
		num.addItemListener(i1);
		ItemListener i2=new filterListener();
		typebox.addItemListener(i2);
		bt.addActionListener(new clickListener());
	}
	
	class sortListener implements ItemListener
	{
		@Override
		public void itemStateChanged(ItemEvent e) {
			// TODO Auto-generated method stub
			sortshow();
			showshow();
		}
	}
	
	class filterListener implements ItemListener
	{
		@Override
		public void itemStateChanged(ItemEvent e) {
			// TODO Auto-generated method stub
			getshow();
			sortshow();
			showshow();
		}
	}
	
	class clickListener implements ActionListener
	{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			try {
				BufferedWriter br = new BufferedWriter(new FileWriter(out));
				for(Product i:show)
				{
					br.write(i.getS());
					br.newLine();
				}
				br.close();
			}catch (Exception e1) {
				// TODO: handle exception
			}
		}
	}
	
	
	void getshow()
	{
		String target=(String) typebox.getSelectedItem();
		show.clear();
		for(Product i:data)
		{
			if(target.equals("全部")||target.equals(i.getType()))
			{
				show.add(i);
			}
		}
	}
	
	
	void sortshow()//compare群里的需要掌握
	{
		if(id.isSelected())
		{
			show.sort((a1,a2)->
			{
				return a1.getId().compareTo(a2.getId());
			}
					);
		}
		else
		{
			show.sort((a1,a2)->{
				return a1.getNum()-a2.getNum();
			});
		}
	}
	
	
	void showshow()
	{
		res="";
		for(Product i:show)
		{
			res=res+i.getS()+'\n';
		}
		jta.setText(res);//原来在这里更新数据！
		
	}
	
	public static void main(String args[])
	{
		in=new File(infile);
		out=new File(outfile);
		new FrmProduct();
	}


}
