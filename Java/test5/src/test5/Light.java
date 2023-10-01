package test5;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;


public class Light  extends JFrame{
	private jp j;
	private int stat;
	private JTextArea jta;
	
	Light()
	{
		setTitle("红绿灯");
		setVisible(true);
		setSize(480,280);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		j=new jp();
		add(j, BorderLayout.CENTER);
		j.setBackground(Color.white);
		jta=new JTextArea();
		jta.setEditable(false);
		Font font = new Font("微软雅黑", Font.BOLD, 70);
		jta.setFont(font);
		add(jta,BorderLayout.EAST);
		
		while(true)
		{
			stat=1;
			j.repaint();
			for(int i=15;i>10;i--)
			{
				jta.setText(i+"");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
				}
			}
			stat=2;j.repaint();
			for(int i=10;i>5;i--)
			{
				jta.setText(i+"");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
				}
			}
			for(int i=5;i>0;i--)
			{
				try {
					jta.setText("");
					stat=-2;j.repaint();
					Thread.sleep(500);
					jta.setText(i+"");
					stat=2;j.repaint();
					Thread.sleep(500);
				} catch (InterruptedException e) {
				}
			}
			stat=22;j.repaint();
			for(int i=3;i>0;i--)
			{
				jta.setText(i+"");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
				}
			}
			stat=3;j.repaint();
			for(int i=10;i>5;i--)
			{
				jta.setText(i+"");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
				}
			}
			for(int i=5;i>0;i--)
			{
				try {
					jta.setText("");
					stat=-3;j.repaint();
					Thread.sleep(500);
					jta.setText(i+"");
					stat=3;j.repaint();
					Thread.sleep(500);
				} catch (InterruptedException e) {
				}
			}
			stat=33;j.repaint();
			for(int i=3;i>0;i--)
			{
				jta.setText(i+"");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
				}
			}
			stat=4;j.repaint();
			for(int i=10;i>5;i--)
			{
				jta.setText(i+"");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
				}
			}
			for(int i=5;i>0;i--)
			{
				try {
					jta.setText("");
					stat=-4;j.repaint();
					Thread.sleep(500);
					jta.setText(i+"");
					stat=4;j.repaint();
					Thread.sleep(500);
				} catch (InterruptedException e) {
				}
			}
			stat=44;j.repaint();
			for(int i=3;i>0;i--)
			{
				jta.setText(i+"");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
				}
			}
		}	
	}
	
	class jp extends JPanel {  
		protected void paintComponent(Graphics g) { 
			super.paintComponent(g);
	        g.drawOval(50, 20, 50, 50);
	        g.drawOval(150, 20, 50, 50);
	        g.drawOval(250, 20, 50, 50);
	        
	        g.drawOval(50, 80, 50, 50);
	        g.drawOval(150, 80, 50, 50);
	        g.drawOval(250, 80, 50, 50);
	        
	        g.drawOval(50, 140, 50, 50);
	        g.drawOval(150, 140, 50, 50);
	        g.drawOval(250, 140, 50, 50);
	        g.drawString("红灯",63,220);
	        g.drawString("绿灯",163,220);
	        g.drawString("黄灯",263,220);
	        g.drawString("左转",320,50);
	        g.drawString("直行",320,110);
	        g.drawString("公交车",320,170);
	        if(stat==1)
	        {
	        	g.setColor(Color.RED);  
	        	g.fillOval(50, 20, 50, 50);
		        g.fillOval(50, 80, 50, 50);
		        g.fillOval(50, 140, 50, 50);
	        }
	        if(stat==2)
	        {
	        	g.setColor(Color.RED);  
	        	g.fillOval(50, 20, 50, 50);
		        g.fillOval(50, 80, 50, 50);
	        	g.setColor(Color.GREEN); 
		        g.fillOval(150, 140, 50, 50);
	        }
	        if(stat==-2)
	        {
	        	g.setColor(Color.RED);  
	        	g.fillOval(50, 20, 50, 50);
		        g.fillOval(50, 80, 50, 50);
	        }
	        if(stat==22)
	        {
	        	g.setColor(Color.RED);  
	        	g.fillOval(50, 20, 50, 50);
		        g.fillOval(50, 80, 50, 50);
	        	g.setColor(Color.YELLOW); 
		        g.fillOval(250, 140, 50, 50);
	        } 
	        if(stat==3)
	        {
	        	g.setColor(Color.RED);  
	        	g.fillOval(50, 20, 50, 50);
	        	g.setColor(Color.GREEN);
		        g.fillOval(150, 80, 50, 50); 
		        g.fillOval(150, 140, 50, 50);
	        }
	        if(stat==-3)
	        {
	        	g.setColor(Color.RED);  
	        	g.fillOval(50, 20, 50, 50);
	        }
	        if(stat==33)
	        {
	        	g.setColor(Color.RED);  
	        	g.fillOval(50, 20, 50, 50);
	        	g.setColor(Color.YELLOW);
		        g.fillOval(250, 80, 50, 50); 
		        g.fillOval(250, 140, 50, 50);
	        }
	        if(stat==4)
	        {
	        	g.setColor(Color.GREEN);  
	        	g.fillOval(150, 20, 50, 50);
	        	g.setColor(Color.RED);
		        g.fillOval(50, 80, 50, 50); 
		        g.fillOval(50, 140, 50, 50);
	        }
	        if(stat==-4)
	        {
	        	g.setColor(Color.RED);
		        g.fillOval(50, 80, 50, 50); 
		        g.fillOval(50, 140, 50, 50);
	        }
	        if(stat==44)
	        {
	        	g.setColor(Color.YELLOW);  
	        	g.fillOval(250, 20, 50, 50);
	        	g.setColor(Color.RED);
		        g.fillOval(50, 80, 50, 50); 
		        g.fillOval(50, 140, 50, 50);
	        }
	    }  }
	static public void main(String args[])
	{
		new Light();
	}
}
