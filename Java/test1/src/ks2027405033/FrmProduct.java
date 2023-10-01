package ks2027405033;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.*;
import java.util.*;

import javax.swing.*;

public class FrmProduct extends JFrame {
	
	private JRadioButton pidBtn; // 产品编号
	private JRadioButton numBtn; // 产品库存
	private ButtonGroup select; // 产品编号 or 产品库存
	private JComboBox<String> typeBox; // 类型
	private JTextArea jta;  // 文本域
	private JButton saveBtn;  // 保存
	
	private ArrayList<Product> list, show;  // 数据
	private File saveTo;

	public FrmProduct(File from, File to) {
		pidBtn = new JRadioButton("产品编号");
		numBtn = new JRadioButton("产品库存");
		select = new ButtonGroup();
		select.add(pidBtn);
		select.add(numBtn);
		typeBox = new JComboBox<>(Product.TYPES);
		jta = new JTextArea();
		saveBtn = new JButton("保存");
		
		saveTo = to;		
		list = new ArrayList<>();
		show = new ArrayList<>();
		
		Container content = getContentPane();
		
		// 顶部
		Box topLine = Box.createHorizontalBox();
		topLine.add(Box.createHorizontalStrut(10));
		JLabel label1 = new JLabel("排序方式:");
		topLine.add(label1);
		topLine.add(Box.createHorizontalStrut(10));
		topLine.add(pidBtn);
		topLine.add(Box.createHorizontalStrut(10));
		topLine.add(numBtn);
		topLine.add(Box.createHorizontalGlue());
		JLabel label2 = new JLabel("选择类型:");
		topLine.add(label2);
		topLine.add(Box.createHorizontalStrut(10));
		topLine.add(typeBox);
		topLine.add(Box.createHorizontalStrut(10));
		content.add(topLine, BorderLayout.NORTH);
		
		// 显示滚动条的文本域
		JScrollPane jsp = new JScrollPane(jta);
		jsp.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		content.add(jsp, BorderLayout.CENTER);
		
		// 确认按钮
		Box buttomLine = Box.createHorizontalBox();
		buttomLine.add(Box.createHorizontalGlue());
		buttomLine.add(saveBtn);
		buttomLine.add(Box.createHorizontalGlue());
		content.add(buttomLine, BorderLayout.SOUTH);
		
		setSize(500, 400);
		setTitle("查看产品");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		loadData(from);  // 加载数据
		initListener();  // 初始化监听器
		
		pidBtn.setSelected(true);
		typeBox.setSelectedIndex(0);
		
		// 显示数据
		sortShown();
		setToShow();
		
		setVisible(true);
	}

	// 加载数据
	private void loadData(File file) {
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));
			String aline = null;
			while (null != (aline = br.readLine())) {
				if (aline.trim().isEmpty()) {
					continue;
				}
				System.out.println(aline);
				Product p = new Product(aline);
				list.add(p);
				show.add(p);
			}
			br.close();
		} catch(IOException e) {
			System.err.println(e.getMessage());
		}
	}

	// 初始化监听器
	private void initListener() {
		ItemListener litener1 = new SortListener();
		pidBtn.addItemListener(litener1);
		numBtn.addItemListener(litener1);
		ItemListener listener2 = new FilterListener();
		typeBox.addItemListener(listener2);
		saveBtn.addActionListener(new ClickListener());
	}
	
	// 显示
	private void setToShow() {
		StringBuilder str = new StringBuilder();
		for (Product p : show) {
			str.append(p.toString());
			str.append("\n");
		}
		jta.setText(str.toString());
	}
	
	// 显示数据
	private void sortShown() {
		if (pidBtn.isSelected()) {
			Collections.sort(show, new ProductIdComparator());// 按照id排序的比较器
		} else if (numBtn.isSelected()) {
			Collections.sort(show, new ProductNumberComparator());// 按照库存排序的比较器
		}
	}
	
	// 排序选项监听器
	class SortListener implements ItemListener {
		@Override
		public void itemStateChanged(ItemEvent e) {
			if (e.getSource() == pidBtn) {
				sortShown();
			} else if (e.getSource() == numBtn) {
				sortShown();
			}
			setToShow();
		}
	}
	
	// 类型监听
	class FilterListener implements ItemListener {
		@Override
		public void itemStateChanged(ItemEvent e) {
			String selected = (String) typeBox.getSelectedItem();
			show.clear();
			for (Product p : list) {
				if (selected.equals("全部") || p.getType().equals(selected)) {
					show.add(p);
				}
			}
			sortShown();
			setToShow();			
		} 
	}
	
	// 点击监听
	class ClickListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent arg0) {
			try {
				BufferedWriter br = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(saveTo), "UTF-8"));
				for (Product p : show) {
					br.write(p.toString());
					br.newLine();
				}
				br.close();
			} catch(IOException e) {
				System.err.println(e.getMessage());
			}
			JOptionPane.showMessageDialog(null, "文件成功保存");
		}
	}
	
	
}