//Main.java
package demo2;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.nio.CharBuffer;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Main extends JFrame{
	static String infile=System.getProperty("user.dir")+File.separator+"in.txt";
	static String outfile=System.getProperty("user.dir")+File.separator+"result.txt";
	
	static ArrayList<Book> data,show;
	static JTextArea jta;
	static String res;
	static public String target;
	static JButton left;
	static JButton right;
	static int show_idx;
	static int view_type=0;
	static JPanel jp;

    Main(){
    	
        JMenuBar jMenuBar = new JMenuBar();
        JMenu jMenu = new JMenu("菜单");
        JMenu jMenu1 = new JMenu("文件");
        JMenu jMenu2 = new JMenu("编辑");
        JMenu jMenu3 = new JMenu("显示");
 
        JMenuItem jMenuItem = new JMenuItem("打开");
        JMenuItem jMenuItem1 = new JMenuItem("保存");
        JMenuItem jMenuItem2 = new JMenuItem("打印");
        JMenuItem jMenuItem3 = new JMenuItem("显示全部");
        JMenuItem jMenuItem4 = new JMenuItem("按页显示");
        JMenuItem jMenu5 = new JMenu("改变字体大小");
        JMenuItem jMenuItem6 = new JMenuItem("查找");
        JMenuItem jMenuItem7 = new JMenuItem("修改");
        JMenuItem jMenuItem8 = new JMenuItem("删除");
        JMenuItem jMenu9 = new JMenu("排序");
        JMenuItem jMenuItem10 = new JMenuItem("帮助");
        JMenuItem jMenuItem11 = new JMenuItem("退出");
        JMenuItem jMenuItem12 = new JMenuItem("10");
        JMenuItem jMenuItem13 = new JMenuItem("13");
        JMenuItem jMenuItem14 = new JMenuItem("15");
        
        JMenuItem jMenuItem15 = new JMenuItem("编号");
        JMenuItem jMenuItem16 = new JMenuItem("书名");
        JMenuItem jMenuItem17 = new JMenuItem("作者");
        JMenuItem jMenuItem18 = new JMenuItem("出版社");
        JMenuItem jMenuItem19 = new JMenuItem("入库日期");
        JMenuItem jMenuItem20 = new JMenuItem("借出日期");
        JMenuItem jMenuItem21 = new JMenuItem("限还日期");
        JMenuItem jMenuItem22 = new JMenuItem("归还日期");
        JMenuItem jMenuItem23 = new JMenuItem("是否借出");
        JMenuItem jMenuItem24 = new JMenuItem("是否在库");
        
 
        jMenu1.add(jMenuItem);
        jMenu1.add(jMenuItem1);
        jMenu1.add(jMenuItem2);
 
        jMenu3.add(jMenuItem3);
        jMenu3.add(jMenuItem4);
        jMenu3.add(jMenu5);
        
        jMenu5.add(jMenuItem12);
        jMenu5.add(jMenuItem13);
        jMenu5.add(jMenuItem14);
        
        jMenu9.add(jMenuItem15);
        jMenu9.add(jMenuItem16);
        jMenu9.add(jMenuItem17);
        jMenu9.add(jMenuItem18);
        jMenu9.add(jMenuItem19);
        jMenu9.add(jMenuItem20);
        jMenu9.add(jMenuItem21);
        jMenu9.add(jMenuItem22);
        jMenu9.add(jMenuItem23);
        jMenu9.add(jMenuItem24);
        
        jMenu2.add(jMenuItem6);
        jMenu2.add(jMenuItem7);
        jMenu2.add(jMenuItem8);
        jMenu2.add(jMenu9);
        
        jMenu.add(jMenu1);
        jMenu.add(jMenu2);
        jMenu.add(jMenu3);
        jMenu.add(jMenuItem10);
        jMenu.add(jMenuItem11);
 
        jMenuBar.add(jMenu);
 
        setJMenuBar(jMenuBar);

    	left=new JButton("上一页");
    	right=new JButton("下一页");
    	jp=new JPanel();
        jp.add(left);
        jp.add(right);
    	add(jp,BorderLayout.SOUTH);
    	jp.setVisible(false);
    	view_type=0;
    	
    	left.addActionListener(new ActionListener() {
    		@Override
    		public void actionPerformed(ActionEvent e) {
    			if(show_idx!=10)
    			{
    				show_idx-=10;
    				res="";
    				for(int i=show_idx-10;i<=show_idx-1;i++)
    				{
    					res=res+show.get(i)+"\n";
    				}
    				jta.setText(res);
    			}
    		}
    	});
    	right.addActionListener(new ActionListener() {
    		@Override
    		public void actionPerformed(ActionEvent e) {
    			if(show.size()>show_idx)
    			{
    				res="";
    				for(int i=show_idx;i<=Math.min(show_idx+9,show.size()-1);i++)
    				{
    					res=res+show.get(i)+"\n";
    				}
    				jta.setText(res);
    				show_idx+=10;
    			}
    		}
    	});

        jta=new JTextArea("");
        JScrollPane scroll = new JScrollPane (jta, 
        JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER );
        scroll.setHorizontalScrollBarPolicy( 
        JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED); 
        scroll.setVerticalScrollBarPolicy( 
        JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED); 

        
        add(scroll,BorderLayout.CENTER);
        
        jMenuItem.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
        	JFileChooser chooser = new JFileChooser("请选择文件");
        	FileNameExtensionFilter filter = new FileNameExtensionFilter("文本文件(*.txt)", "txt");
        	chooser.setFileFilter(filter);
        	int res = chooser.showOpenDialog(null);
        	if(res == JFileChooser.APPROVE_OPTION){
        		File file = chooser.getSelectedFile();
        		String path = file.getAbsolutePath();
        		try {
        			InputStreamReader reader = new InputStreamReader(new FileInputStream(path), "utf-8");
        			char[] buf = new char[1024]; 
        		int len = 0;
        		CharBuffer cb = CharBuffer.allocate((int) file.length());
        		while((len = reader.read(buf)) > -1){
        			cb.put(buf, 0, len);
        		}
        		reader.close();
        		String str = new String(cb.array());
        		jta.setEditable(false);
        		initData(str);
        		jta.setText(str);
        		} catch (Exception e1) {
        			e1.printStackTrace();
        		}
        	}
        }
        });
        
        jMenuItem1.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
        	String path;
        	String content =getShow();
        	JFileChooser chooser = new JFileChooser();
        	FileNameExtensionFilter filter = new FileNameExtensionFilter("文本文件(*.txt)", "txt");
        	chooser.setFileFilter(filter);
        	int res =chooser.showSaveDialog(null);
        	if(res == JFileChooser.APPROVE_OPTION){
        		path = chooser.getSelectedFile().getAbsolutePath() + ".txt";
        		try {
        			OutputStreamWriter writer = new OutputStreamWriter(new FileOutputStream(path), "gbk");
        			writer.write(content);
        			writer.close();
        		} catch (IOException e1) {
        			e1.printStackTrace();
        		}
        	}
        }
        });
        
        jMenuItem2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	getShow();
                PrinterJob job = PrinterJob.getPrinterJob();
                job.setPrintable(new Printer(res));
                if (job.printDialog())
                { 
                    try {
                        job.print();
                    }
                    catch (PrinterException e2){
                    }
                }
            }
            });
        
        
        jMenuItem3.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
        	view_type=0;
        	showData();
        	scroll.setHorizontalScrollBarPolicy( 
        	        JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED); 
        	        scroll.setVerticalScrollBarPolicy( 
        	        JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED); 
        	jp.setVisible(false);
        }
        });
        
        jMenuItem4.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	view_type=1;
            	jp.setVisible(true);
            	show_idx=10;
            	res="";
            	for(int i=0;i<Math.min(10,show.size());i++)
            	{
            		res=res+show.get(i)+"\n";
            	}
            	jta.setText(res);
            	
            }
            });
        
        jMenuItem12.addActionListener(new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
        	jta.setFont(new Font("", Font.BOLD, 10));
        }
        });
        
        jMenuItem13.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	jta.setFont(new Font("", Font.BOLD, 13));
            }
            });
        
        jMenuItem14.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	jta.setFont(new Font("", Font.BOLD, 15));
            }
            });
        jMenuItem7.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	jta.setEditable(true);
            }
            });
        
        jMenuItem6.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	JFrame jf=new JFrame();
            	jf.setTitle("输入查找内容");
            	jf.setVisible(true);
            	jf.setSize(400,100);
            	JTextArea jt=new JTextArea();
            	jt.setEditable(true);
            	jf.add(jt,BorderLayout.CENTER);
            	JButton jb=new JButton("确定");
            	jf.add(jb,BorderLayout.SOUTH);
            	jb.addActionListener(new ActionListener() {
            		@Override
            		public void actionPerformed(ActionEvent e) {
            			target=jt.getText();
            			jf.dispose();
                  		show.clear();
                		for(Book i:data)
                		{
                			if( i.toString().contains(target))
                			{
                				show.add(i);
                			}
                		}
                		showData();
            		}
            	});
            	}
            });
        jMenuItem8.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	JFrame jf=new JFrame();
            	jf.setTitle("输入删除内容");
            	jf.setVisible(true);
            	jf.setSize(400,100);
            	JTextArea jt=new JTextArea();
            	jt.setEditable(true);
            	jf.add(jt,BorderLayout.CENTER);
            	JButton jb=new JButton("确定");
            	jf.add(jb,BorderLayout.SOUTH);
            	jb.addActionListener(new ActionListener() {
            		@Override
            		public void actionPerformed(ActionEvent e) {
            			target=jt.getText();
            			jf.dispose();
                  		show.clear();
                		for(Book i:data)
                		{
                			if( !(i.toString().contains(target)))
                			{
                				show.add(i);
                			}
                		}
                		showData();
            		}
            	});
            	}
            });
        jMenuItem15.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getNum().compareTo(a2.getNum());
    			}
    					);
                showData();
            }
            });
        jMenuItem16.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getName().compareTo(a2.getName());
    			}
    					);
                showData();
            }
            });
        jMenuItem17.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getAuthor().compareTo(a2.getAuthor());
    			}
    					);
                showData();
            }
            });
        jMenuItem18.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getPress().compareTo(a2.getPress());
    			}
    					);
                showData();
            }
            });
        jMenuItem19.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getInTime().compareTo(a2.getInTime());
    			}
    					);
                showData();
            }
            });
        jMenuItem20.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getOutTime().compareTo(a2.getOutTime());
    			}
    					);
                showData();
            }
            });
        jMenuItem21.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getDeadline().compareTo(a2.getDeadline());
    			}
    					);
                showData();
            }
            });
        jMenuItem22.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getReturnTime().compareTo(a2.getReturnTime());
    			}
    					);
                showData();
            }
            });
        jMenuItem23.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getIsBorrow().compareTo(a2.getIsBorrow());
    			}
    					);
                showData();
            }
            });
        jMenuItem24.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	show.sort((a1,a2)->
    			{
    				return a1.getIsStore().compareTo(a2.getIsStore());
    			}
    					);
                showData();
            }
            });
        
        jMenuItem10.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	JFrame jf=new JFrame();
            	jf.setSize(550,220);
            	jf.setVisible(true);
            	jf.setTitle("帮助");
            	JTextArea jt=new JTextArea("这是帮助：\n你可以在打开中选择符合格式的txt文件\n在编辑完成后你可以选择保存到指定路径\n您可以选择打印选项来进行打印\n在编辑菜单中，您可以进行例如：查找，修改，删除，排序等操作来处理您的数据\n在显示菜单中，您可以选择显示方式（显示全部或按页显示（默认每页10条数据））和字体大小\n若果您想退出，可以选择退出选项");
            	jf.add(jt,BorderLayout.CENTER);
            	JButton jb=new JButton("确定");
            	jf.add(jb,BorderLayout.SOUTH);
            	jb.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                    	jf.dispose();
                    }
                    });
            }
            });
        
        jMenuItem11.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	dispose();
            }
            });
 
		setTitle("图书管理系统");
		setSize(600,400);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
    
    static void initData(String s)
    {
    	data=new ArrayList<Book>();
    	show=new ArrayList<Book>();
    	
    	String []a=s.split("\n");
    	for(String i:a)
    	{
    		data.add(new Book(i));
    		show.add(new Book(i));
    	}
    }
    
    static String getShow()
    {
    	String ans="";
    	for(Book i:show)
    	{
    		ans=ans+i.toString()+"\n";
    	}
    	return ans;
    }
    
    static void showData()
    {
    	
    	if(view_type==1)
    	{
    		jp.setVisible(true);
        	show_idx=10;
        	res="";
        	for(int i=0;i<Math.min(10,show.size());i++)
        	{
        		res=res+show.get(i)+"\n";
        	}
    	}
    	else
    	{
    		String s="";
        	for(Book i:show)
        	{
        		s=s+i.toString()+"\n";
        	}
        	jta.setText(s);
    	}
    }

    public static void main(String[] args)
    {
    	new Main();
    }
}
