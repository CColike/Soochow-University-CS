package test2;

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
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

import javax.swing.Box;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;


public class FrmProduct extends JFrame{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	JRadioButton id;
	JRadioButton num;
	ButtonGroup bg;
	Box box1;
//	JPanel bg;
	JComboBox<String> typebox;
	String[] types={"全部","电脑","手机","书籍"};
	JScrollPane jsp;
	List<Product> strs;
	List<Product> show;
	JButton bt;
	JTextArea jta;  // 文本域
	
	public FrmProduct(File in,File out) 
	{
		setTitle("查看产品");

		Container content=getContentPane();
		bg=new ButtonGroup();
		id=new JRadioButton();
		num=new JRadioButton();
		jta = new JTextArea();
		box1=Box.createHorizontalBox();//水平   Horizontal
		//box1=Box.createVerticalBox()//竖直    Vertical
		//createVerticalStrut(int height)
		id.setText("产品编号");
		num.setText("产品库存");
		id.setSelected(true);
		num.setSelected(false);
		bg.add(id);
		bg.add(num);
		
		JLabel jl1=new JLabel("排序方式：");
		JLabel jl2=new JLabel("选择类型：");
//		JPanel jp1=new JPanel();
		box1.add(Box.createHorizontalStrut(10));//间隔
		box1.add(jl1);
		box1.add(Box.createHorizontalStrut(10));
		box1.add(id);
		box1.add(Box.createHorizontalStrut(10));
		box1.add(num);
		box1.add(Box.createHorizontalGlue());//空白塞满中间
		box1.add(jl2);
		box1.add(Box.createHorizontalStrut(10));
		typebox=new JComboBox<>(types);
		box1.add(typebox);
		box1.add(Box.createHorizontalStrut(10));
		
		content.add(box1,BorderLayout.NORTH);
		
		//文本
		
		//需要时显示
		jsp=new JScrollPane(jta);
		jsp.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		content.add(jsp,BorderLayout.CENTER);
		
		
		//确认按钮
		Box box2=Box.createHorizontalBox();
		box2.add(Box.createHorizontalGlue());
		bt=new JButton();
		bt.setText("保存");
		box2.add(bt);
		box2.add(Box.createHorizontalGlue());
		
		content.add(box2,BorderLayout.SOUTH);
		
		
		
		
		
//		content.add(bg);
		setSize(500,400);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);//有理没理要加上的
		
		
		//加载数据
		strs=new ArrayList<Product>();
		show=new ArrayList<Product>();
		loadData(in);
		
		
		//初始化监听器
		initListener();
		id.setSelected(true);
		typebox.setSelectedIndex(0);
		sortShown();
		setToShow();
	}
	
	
	void loadData(File file)
	{
		try 
		{
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));
			String s=br.readLine();
			while(s!=null)
			{
				strs.add(new Product(s));
				show.add(new Product(s));
				System.out.println(s);
				s=br.readLine();
			}
				
			//关闭文件
			br.close();
		}catch (Exception e) {
			// TODO: handle exception
		}
		
		
	}
	
	
	
	void sortShown()
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
			show.sort((a1,a2)->
			{
				return a1.getNum()-a2.getNum();
			}
					);
		}
	}
	
	
	void setToShow()
	{
		String s = "";
		for (int i=0;i<show.size();i++) {
			s=s+show.get(i);
			s+="\n";
		}
		jta.setText(s);
	}
	
	void initListener()
	{
		ItemListener i1=new SortListener();
		id.addItemListener(i1);
		num.addItemListener(i1);
		ItemListener i2=new FilterListener();
		typebox.addItemListener(i2);
		bt.addActionListener(new ClickListener());
	}
	
	class SortListener implements ItemListener
	{
		@Override
		public void itemStateChanged(ItemEvent e) {
			// TODO Auto-generated method stub
			sortShown();
			setToShow();
		}
	}
	
	
	class FilterListener implements ItemListener
	{
		@Override
		public void itemStateChanged(ItemEvent e) {
			// TODO Auto-generated method stub
			show.clear();
			String target=(String) typebox.getSelectedItem();
			System.out.println(target);
			for(Product i:strs)
			{
				if (target.equals("全部")||i.getType().equals(target))
				{
					show.add(i);
				}
			}
			
			
			sortShown();
			setToShow();
		}
	}
	
	
	class ClickListener implements ActionListener
	{
		public void actionPerformed(ActionEvent arg0) {
			
		}
	}
	
	
}
