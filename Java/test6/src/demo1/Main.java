//Main.java
package demo1;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;


public class Main extends JFrame{
	private JPanel p1,p2,p3,p4,p5,p6,p7,sp1,sp2;
    private JButton last,next;
    private JTextField yearText,monthText;
    private JLabel yy,mm;
    private JLabel weekdayText,TimeText,dayText;

    private Calendar nowDate = new GregorianCalendar();
    private int nowYear = nowDate.get(Calendar.YEAR);
    private int nowMonth = nowDate.get(Calendar.MONTH);
    private int nowDay = nowDate.get(Calendar.DAY_OF_MONTH);
    private int nowWeekDay = nowDate.get(Calendar.DAY_OF_WEEK);
    
    private String[] week = {"日","一","二","三","四","五","六"};
    private JLabel[] weekLable = new JLabel[7];
    private JButton[] dayBtn = new JButton[42];
    
    Clock c;
 
    Main()
    {
        sp1=new JPanel();
        sp2=new JPanel();
        sp1.setLayout(new BorderLayout());
        sp2.setLayout(new BorderLayout());
        add(sp1,BorderLayout.WEST);
        add(sp2,BorderLayout.EAST);
        
        //p1
        p1=new JPanel();
        dayText=new JLabel();
        dayText.setText(nowYear+"年"+(nowMonth+1)+"月"+nowDay+"日");
        p1.add(dayText);
        add(p1,BorderLayout.NORTH);
        
    	//p2
        last= new JButton("<");
        next= new JButton(">");
        yy=new JLabel("年");
        mm=new JLabel("月");
        yearText = new JTextField(3);
        monthText = new JTextField(2);
        yearText.setText(nowYear+"");
        monthText.setText(nowMonth+1+"");
        yearText.setEditable(false);
        monthText.setEditable(false);
        p2=new JPanel();
        p2.add(last);
        p2.add(yearText);
        p2.add(yy);
        p2.add(monthText);
        p2.add(mm);
        p2.add(next);
        sp1.add(p2,BorderLayout.NORTH);
        
        last.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	nowMonth--;
            	if(nowMonth==-1)
            	{
            		nowMonth=11;
            		nowYear--;
            	}
            	reset();
            }
            });
        
        next.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	nowMonth++;
            	if(nowMonth==12)
            	{
            		nowMonth=0;
            		nowYear++;
            	}
            	reset();
            }
            });
        
        //p3
        p3=new JPanel();
        p3.setLayout(new GridLayout(1,7));
        for (int i=0;i<7;i++)
        {
            weekLable[i] = new JLabel(week[i]);
            weekLable[i].setHorizontalAlignment(SwingConstants.CENTER);
            p3.add(weekLable[i]);
        }
        sp1.add(p3,BorderLayout.CENTER);
        
        
        //p4
        p4=new JPanel();
        p4.setLayout(new GridLayout(6,7,2,2));
        for (int i=0;i<42;i++){
            dayBtn[i]=new JButton(); 
            p4.add(dayBtn[i]);
        }
        sp1.add(p4,BorderLayout.SOUTH);
        reset();
        
        //p5
        c=new Clock();
        sp2.add(c,BorderLayout.NORTH);
       
        //p6
        p6=new JPanel();
        TimeText = new JLabel();
        new Thread(){     
            public void run(){
                while(true) 
                {
                    LocalDateTime dateTime = LocalDateTime.now();
                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm:ss");
                    String nowTime = dateTime.format(formatter);
                    TimeText.setText(nowTime);
                    c.setCurrentTime();  
                    c.repaint(); 
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                    }
                }
            }
        }.start();
        p6.add(TimeText);
        sp2.add(p6,BorderLayout.CENTER);
     
        //p7
        p7=new JPanel();
        weekdayText=new JLabel("星期"+week[(nowWeekDay-1)%7]);
        p7.add(weekdayText);
        sp2.add(p7,BorderLayout.SOUTH);
        
        setTitle("图书管理系统");
		setSize(560,310);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
    
    
    void reset()
    {
    	int year=nowYear,month=nowMonth+1;
    	GregorianCalendar gc=new GregorianCalendar(year,month-1,1);
    	int weekidx = gc.get(Calendar.DAY_OF_WEEK);
    	int daynum=getdaynum(gc.isLeapYear(year),month);
    	int leftday=getdaynum(gc.isLeapYear(year),month-1);
    	for(int i=weekidx-2;i>=0;i--)
    	{
            dayBtn[i].setText(leftday+"");
            dayBtn[i].setBackground(Color.white);
            dayBtn[i].setEnabled(false);
            leftday--;
    	}
    	for(int i=weekidx-1;i<=weekidx-2+daynum;i++)
    	{
    		dayBtn[i].setText(i-weekidx+2+"");
            dayBtn[i].setBackground(null);
            dayBtn[i].setEnabled(true);
    	}
    	for(int i=weekidx+daynum-1;i<=41;i++)
    	{
    		dayBtn[i].setText(i-weekidx-daynum+2+"");;
            dayBtn[i].setBackground(Color.white);
            dayBtn[i].setEnabled(false);
    	}
        yearText.setText(year+"");
        monthText.setText(month+"");
    }
    
    int getdaynum(boolean r,int month)
    {
    	if(r&&month==2)return 29;
    	else if(!r&&month==2)return 28;
    	else if(month==4||month==6||month==9||month==11)return 30;
    	else return 31;
    }
    
    public static void main(String[] args) {
        new Main();
    }
	
}
